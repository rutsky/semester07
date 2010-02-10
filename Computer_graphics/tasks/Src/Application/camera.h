// camera.h
// Camera description.
// Vladimir Rutsky, 4057/2
// 09.02.2010

#ifndef CAMERA_H
#define CAMERA_H

#include <d3dx9math.h>

#include "constants.h"
#include "cs.h"

namespace camera
{
  namespace lcs
  {
    class ICamera
    {
      // Returns matrix in local CS.
      virtual D3DXMATRIX viewMatrix() const = 0;
    };

    class IWritableCamera
      : public virtual ICamera
    {
      // Sets local CS matrix
      virtual void setViewMatrix( D3DXMATRIX const *newViewMatrix ) = 0;
    };

    class BaseCamera
      : public virtual ICamera
    {
      // ICamera
    public:
      D3DXMATRIX viewMatrix() const
      {
        return m_viewMatrix;
      }

    protected:
      D3DXMATRIX m_viewMatrix;
    };

    class BaseWritableCamera
      : public BaseCamera
      , public virtual IWritableCamera
    {
      // IWritableCamera
    public:
      void setViewMatrix( D3DXMATRIX const *newViewMatrix )
      {
        m_viewMatrix = *newViewMatrix;
      }
    };

    class IFreeViewCamera
      : public virtual ICamera
    {
    public:
      // longitude:   0   <=  phi  <= 2pi
      // latitude:  -pi/2 <= theta <= pi/2
      virtual void setSphericCoordinates( double phi, double theta ) = 0;
      virtual void moveInSphericCoordinates( double dphi, double dtheta ) = 0;
    };

    class FreeViewCamera
      : public virtual BaseCamera
    {
    public:
      FreeViewCamera()
        : m_phi(0)
        , m_theta(0)
      {
      }

      // IFreeViewCamera
    public:
      void setSphericCoordinates( double phi, double theta )
      {
        m_phi = constrainedPhi(phi);
        m_theta = constrainedTheta(theta);
        updateViewMatrix();
      }

      void moveInSphericCoordinates( double dphi, double dtheta )
      {
        m_phi = constrainedPhi(m_phi + dphi);
        m_theta = constrainedTheta(m_theta + dtheta);
        updateViewMatrix();
      }

    protected:
      static D3DXMATRIX evalViewMatrix( double phi, double theta )
      {
        D3DXMATRIX yRot;
        D3DXMatrixRotationY(&yRot, (float)theta);

        D3DXMATRIX zRot;
        D3DXMatrixRotationZ(&zRot, (float)phi);

        D3DXMATRIX axis(
           0,  0,  1,  0,
          -1,  0,  0,  0,
           0,  1,  0,  0,
           0,  0,  0,  1);

        return axis * yRot * zRot;
      }
      
      static double constrainedPhi( double phi )
      {
        phi = fmod(phi, 2 * constants::pi);
        if (phi < 0)
          phi += 2 * constants::pi;
        return phi;
      }

      static double constrainedTheta( double theta )
      {
        if (theta < -constants::pi / 2.0)
          return -constants::pi / 2.0;
        else if (theta > constants::pi / 2.0)
          return constants::pi / 2.0;
        else
          return theta;
      }

      void updateViewMatrix()
      {
        m_viewMatrix = evalViewMatrix(m_phi, m_theta);
      }

    protected:
      double m_phi;   // longitude:   0   <=  phi  <= 2pi
      double m_theta; // latitude:  -pi/2 <= theta <= pi/2
    };

    class ISphericCamera
      : public virtual ICamera
    {
    public:
      virtual void setSphericCoordinates( double r, double phi, double theta ) = 0;
      virtual void moveInSphericCoordinates( double dr, double dphi, double dtheta ) = 0;
    };

    class SphericCamera
      : public ISphericCamera
      , public BaseCamera
    {
    public:
      SphericCamera()
        : m_r(1.0)
        , m_phi(0.0)
        , m_theta(0.0)
      {
      }

      // ISphericCamera
    public:
      void setSphericCoordinates( double r, double phi, double theta )
      {
        m_r = constrainedR(r);
        m_phi = constrainedPhi(phi);
        m_theta = constrainedTheta(theta);
        updateViewMatrix();
      }

      void moveInSphericCoordinates( double dr, double dphi, double dtheta )
      {
        m_r = constrainedR(m_r + dr);
        m_phi = constrainedPhi(m_phi + dphi);
        m_theta = constrainedTheta(m_theta + dphi);
        updateViewMatrix();
      }

    protected:
      static D3DXMATRIX evalViewMatrix( double r, double phi, double theta )
      {
        D3DXMATRIX translate;
        D3DXMatrixTranslation(&translate, (float)-r, 0, 0);

        D3DXMATRIX yRot;
        D3DXMatrixRotationY(&yRot, (float)theta);

        D3DXMATRIX zRot;
        D3DXMatrixRotationZ(&zRot, (float)phi);

        D3DXMATRIX axis(
           0,  0,  1,  0,
          -1,  0,  0,  0,
           0,  1,  0,  0,
           0,  0,  0,  1);

        return axis * translate * yRot * zRot;
      }
      
      static double constrainedR( double r )
      {
        if (r < 0)
          return 0.0;
        else
          return r;
      }

      static double constrainedPhi( double phi )
      {
        phi = fmod(phi, 2 * constants::pi);
        if (phi < 0)
          phi += 2 * constants::pi;
        return phi;
      }

      static double constrainedTheta( double theta )
      {
        if (theta < -constants::pi / 2.0)
          return -constants::pi / 2.0;
        else if (theta > constants::pi / 2.0)
          return constants::pi / 2.0;
        else
          return theta;
      }

      void updateViewMatrix()
      {
        m_viewMatrix = evalViewMatrix(m_r, m_phi, m_theta);
      }

    protected:
      double m_r;     // r >= 0
      double m_phi;   // longitude:   0   <=  phi  <= 2pi
      double m_theta; // latitude:  -pi/2 <= theta <= pi/2
    };
  } // End of namespace 'lcs'
} // End of namespace 'camera'

#endif // CAMERA_H
