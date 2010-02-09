// camera.h
// Camera description classes declaration.
// Vladimir Rutsky, 4057/2
// 09.02.2010

#include <d3dx9math.h>

#include "cs.h"

namespace camera
{
  class ICamera
  {
    virtual D3DXMATRIX viewMatrix() const = 0;
  };

  class IWritableCamera
    : public virtual ICamera
  {
    virtual void setViewMatrix( D3DXMATRIX const *newViewMatrix ) const = 0;
  };

  // Camera with separate view and position matrices.
  class BaseCamera
    : public virtual IWritableCamera
    , public cs::BaseCoordinateSystem
  {
    // ICamera
  public:
    D3DXMATRIX viewMatrix() const
    {
      return matrix() * m_viewMatrix;
    }

    // IWritableCamera
  public:
    void setViewMatrix( D3DXMATRIX const *newViewMatrix ) const
    {
      m_viewMatrix = *newViewMatrix;
    }

  protected:
    D3DXMatrix m_viewMatrix;
  };

  // Camera with single view/position matrix.
  class BaseCSCamera
    : public virtual IWritableCamera
    , public cs::BaseCoordinateSystem
  {
    // ICamera
  public:
    D3DXMATRIX viewMatrix() const
    {
      return matrix();
    }

    // IWritableCamera
  public:
    void setViewMatrix( D3DXMATRIX const *newViewMatrix ) const
    {
      setMatrix(newViewMatrix);
    }
  };

  class ILookAtCamera
    : public virtual IWritableCamera
  {
  public:
    virtual void lookAt( D3DXVECTOR3 const *lookAtPoint, D3DXVECTOR3 const *upVector = 0 ) = 0;
  };

  class LookAtCamera
    : public virtual BaseCamera
  {
    // ICameraLookAt
  public:
    void lookAt( D3DXVECTOR3 const *lookAtPoint, D3DXVECTOR3 const *upVector = 0 )
    {
      static D3DXVECTOR3 eyePoint(0, 0, 0);

      if (upVector)
        D3DXMatrixLookAtLH(&m_viewMatrix, &eyePoint, &lookAtPoint, &upVector);
      else
      {
        D3DXVECTOR3 up(0, 0, 1);
        D3DXMatrixLookAtLH(&viewMatrix, &eyePoint, &lookAtPoint, &up);
      }

      m_lookAtPoint = *lookAtPoint;
    }

  protected:
    D3DXVECTOR3 m_lookAtPoint;
  };

  class ISphericCamera
    : public virtual IWritableCamera
  {
  public:
    virtual void setCoordinates( double r, double theta, double phi ) = 0;
    virtual void moveOnSphere( double dr, double dtheta, double dphi ) = 0;
  }

  class SphericCamera
    : public ISphericCamera
    , public BaseCamera
  {
  public:
    SphericCamera()
      : m_r(1.0)
      , m_theta(0.0)
      , m_phi(0.0)
      , m_upVector(0, 0, 1)
    {
    }

    // ISphericCamera
  public:
    void setCoordinates( double r, double theta, double phi )
    {
      m_r = r;
      m_theta = theta;
      m_phi = phi;
    }

    void moveOnSphere( double dr, double dtheta, double dphi ) = 0;

  protected:
    void calculateViewMatrix()
    {
      
    }

  protected:
    double m_r;     // r >= 0
    double m_theta; // latitude:  -pi/2 <= theta <= pi/2
    double m_phi;   // longitude:   0   <=  phi  <= 2pi

    D3DXVECTOR3 m_upVector;
  };
} // End of namespace 'camera'
