// camera.h
// Camera description.
// Vladimir Rutsky, 4057/2
// 09.02.2010

#ifndef CAMERA_H
#define CAMERA_H

#include <cassert>

#include <d3dx9math.h>

#include "constants.h"
#include "cs.h"
#include "control.h"
#include "common_controls.h"
#include "object.h"
#include "config.h"
#include "util.h"

namespace camera
{
  class IViewMatrix
  {
  public:
    virtual D3DXMATRIX viewMatrix() const = 0;
    ~IViewMatrix() {}
  };

  namespace lcs
  {
    class ICamera
    {
    public:
      // Camera CS to World transform.
      virtual D3DXMATRIX cameraMatrix() const = 0;
      // World CS to Camera transform.
      virtual D3DXMATRIX viewMatrix() const = 0;
      ~ICamera() {}
    };

    class IWritableCamera
      : public virtual ICamera
    {
    public:
      virtual void setCameraMatrix( D3DXMATRIX const *newViewMatrix ) = 0;
      virtual void setViewMatrix( D3DXMATRIX const *newViewMatrix ) = 0;
    };

    class BaseCamera
      : public virtual ICamera
    {
    public:
      BaseCamera()
      {
        D3DXMatrixIdentity(&m_cameraMatrix);
      }

      // ICamera
    public:
      D3DXMATRIX cameraMatrix() const
      {
        return m_cameraMatrix;
      }

      D3DXMATRIX viewMatrix() const
      {
        D3DXMATRIX view;
        D3DXMatrixInverse(&view, 0, &m_cameraMatrix);
        return view;
      }

    protected:
      D3DXMATRIX m_cameraMatrix;
    };

    /*
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
    */

    class IFreeViewCamera
      : public virtual ICamera
    {
    public:
      // longitude:   0   <=  phi  <= 2pi
      // latitude:  -pi/2 <= theta <= pi/2
      virtual void setSphericCoordinates( double phi, double theta ) = 0;
      virtual void moveInSphericCoordinates( double dphi, double dtheta ) = 0;
      virtual void lookAt( D3DXVECTOR3 const &dir ) = 0;
    };

    class FreeViewCamera
      : public virtual IFreeViewCamera
      , public virtual BaseCamera
    {
    public:
      FreeViewCamera()
        : m_phi(0)
        , m_theta(0)
      {
        updateCameraMatrix();
      }

      // IFreeViewCamera
    public:
      void setSphericCoordinates( double phi, double theta )
      {
        m_phi = constrainedPhi(phi);
        m_theta = constrainedTheta(theta);
        updateCameraMatrix();
      }

      void moveInSphericCoordinates( double dphi, double dtheta )
      {
        m_phi = constrainedPhi(m_phi + dphi);
        m_theta = constrainedTheta(m_theta + dtheta);
        updateCameraMatrix();
      }

      void lookAt( D3DXVECTOR3 const &dir )
      {
        if (D3DXVec3LengthSq(&dir) <= 1e-6)
        {
          m_phi = 0;
          m_theta = 0;
        }
        else
        {
          m_phi = constrainedPhi(atan2(dir[1], dir[0]) - constants::pi / 2.0);
          m_theta = constrainedTheta(atan2(dir[2], sqrt(util::sqr(dir[0]) + util::sqr(dir[1]))));
        }
        updateCameraMatrix();
      }

    protected:
      static D3DXMATRIX evalCameraMatrix( double phi, double theta );
      
    protected:
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

      void updateCameraMatrix()
      {
        m_cameraMatrix = evalCameraMatrix(m_phi, m_theta);
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
      virtual void setEyePosition( D3DXVECTOR3 const &eye ) = 0;
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
        updateCameraMatrix();
      }

      // ISphericCamera
    public:
      void setSphericCoordinates( double r, double phi, double theta )
      {
        m_r = constrainedR(r);
        m_phi = constrainedPhi(phi);
        m_theta = constrainedTheta(theta);
        updateCameraMatrix();
      }

      void setEyePosition( D3DXVECTOR3 const &eye )
      {
        m_r = constrainedR(D3DXVec3Length(&eye));
        if (m_r <= 1e-6)
        {
          m_phi = 0;
          m_theta = 0;
        }
        else
        {
          m_phi = constrainedPhi(atan2(eye[1], eye[0]) - constants::pi / 2.0);
          m_theta = constrainedTheta(atan2(eye[2], sqrt(util::sqr(eye[0]) + util::sqr(eye[1]))));
        }
        updateCameraMatrix();
      }

      void moveInSphericCoordinates( double dr, double dphi, double dtheta )
      {
        m_r = constrainedR(m_r + dr);
        m_phi = constrainedPhi(m_phi + dphi);
        m_theta = constrainedTheta(m_theta + dtheta);
        updateCameraMatrix();
      }

    protected:
      static D3DXMATRIX evalCameraMatrix( double r, double phi, double theta );
      static D3DXVECTOR3 eyePosition( double r, double phi, double theta )
      {
        return D3DXVECTOR3(
          (float)(r * cos(phi) * cos(theta)), 
          (float)(r * sin(phi) * cos(theta)), 
          (float)(r * sin(theta)));
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

      void updateCameraMatrix()
      {
        m_cameraMatrix = evalCameraMatrix(m_r, m_phi, m_theta);
      }

    protected:
      double m_r;     // r >= 0
      double m_phi;   // longitude:   0   <=  phi  <= 2pi
      double m_theta; // latitude:  -pi/2 <= theta <= pi/2
    };
  } // End of namespace 'lcs'

  class SphericCamera
    : public IViewMatrix
    , public virtual object::ISceneObject
    , public virtual object::BaseWorldMatrixDependentObject
    , public lcs::SphericCamera
    , public control::BaseMouseControl
  {
    // IViewMatrix
  public:
    D3DXMATRIX viewMatrix() const
    {
      // FIXME: Don't allow to rotate Z-axis - use m_worldMatrix.
      D3DXMATRIX camera = lcs::SphericCamera::cameraMatrix() * m_worldMatrix;
      D3DXMATRIX view;
      D3DXMatrixInverse(&view, 0, &camera);
      return view;
    }

    // IOnMouseMoveHandler
  protected: // TODO: Made protected in parent.
    bool onMouseMove( int dx, int dy, int keys )
    {
      if (keys & MK_LBUTTON)
      {
        moveInSphericCoordinates(0, -dx * config::centerMouseRotationSpeedX, dy * config::centerMouseRotationSpeedY);
        //return true;
        return false; // TODO
      }

      return false;
    }

    // IOnMouseWheelHandler
  protected: // TODO: Made protected in parent.
    virtual bool onMouseWheel( int steps, int keys )
    {
      double const dr = ::pow(config::mouseWheelZoomFactor, steps);
      moveInSphericCoordinates(m_r * (dr - 1.0), 0, 0);

      return true;
    }

  public:
    // In LCS.
    D3DXVECTOR3 eyePosition() const
    {
      return lcs::SphericCamera::eyePosition(m_r, m_phi, m_theta);
    }

    void setEyePosition( D3DXVECTOR3 const &eye )
    {
      lcs::SphericCamera::setEyePosition(eye);
    }
  };

  class FreeViewCamera
    : public IViewMatrix
    , public virtual object::ISceneObject
    , public virtual object::BaseWorldMatrixDependentObject
    , public lcs::FreeViewCamera
    , public control::BaseMouseMoveControl
    , public virtual cs::BaseCoordinateSystem
    , public virtual object::BaseDynamicObject
  {
  public:
    FreeViewCamera()
    {
    }

  public:
    void lookAt( D3DXVECTOR3 const &eye, D3DXVECTOR3 const &lookAt )
    {
      D3DXMatrixTranslation(&m_matrix, eye[0], eye[1], eye[2]);
      lcs::FreeViewCamera::lookAt(lookAt - eye);
    }

    // IViewMatrix
  public:
    D3DXMATRIX viewMatrix() const
    {
      // FIXME: Don't allow to rotate Z-axis -- use m_worldMatrix.
      D3DXMATRIX camera = lcs::FreeViewCamera::cameraMatrix() * m_matrix * m_worldMatrix;
      D3DXMATRIX view;
      D3DXMatrixInverse(&view, 0, &camera);
      return view;
    }

    // IOnMouseMoveHandler
  public:
    bool onMouseMove( int dx, int dy, int keys )
    {
      if (keys & MK_LBUTTON)
      {
        moveInSphericCoordinates(-dx * config::freeViewMouseRotationSpeedX, -dy * config::freeViewMouseRotationSpeedY);
        //return true;
        return true; // TODO
      }

      return false;
    }

    // IDynamicObject
  public:
    void update( double time )
    {
      object::BaseDynamicObject::update(time);

      float const distance = (float)(config::keyboardTranslationSpeed * dtime());
      D3DXVECTOR4 cameraTranslation(0, 0, 0, 1);

      {
        enum {x = 0, y = 1, z = 2};
        if (control::isKeyDown('Q'))
          cameraTranslation[y] += 1;
        if (control::isKeyDown('Z'))
          cameraTranslation[y] -= 1;

        if (control::isKeyDown('A'))
          cameraTranslation[x] -= 1;
        if (control::isKeyDown('D'))
          cameraTranslation[x] += 1;

        if (control::isKeyDown('W'))
          cameraTranslation[z] += 1;
        if (control::isKeyDown('S'))
          cameraTranslation[z] -= 1;
      }
   
      cameraTranslation *= distance;

      D3DXVECTOR4 worldTranslation;
      D3DXVec4Transform(&worldTranslation, &cameraTranslation, &lcs::FreeViewCamera::cameraMatrix());

      D3DXMATRIX worldTranslationMatrix;
      D3DXMatrixTranslation(&worldTranslationMatrix, worldTranslation[0], worldTranslation[1], worldTranslation[2]);

      m_matrix = worldTranslationMatrix * m_matrix;
    }

  public:
    // In LCS.
    D3DXVECTOR3 eyePosition() const
    {
      return D3DXVECTOR3(m_matrix(3, 0), m_matrix(3, 1), m_matrix(3, 2));
    }
  };
} // End of namespace 'camera'

#endif // CAMERA_H
