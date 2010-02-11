// camera_projection.h
// Projection matrix constructing functions.
// Vladimir Rutsky, 4057/2
// 11.02.2010

#ifndef CAMERA_PROJECTION_H
#define CAMERA_PROJECTION_H

#include <d3dx9math.h>

namespace projection
{
  class IProjectionMatrix
  {
  public:
    virtual D3DXMATRIX projectionMatrix() const = 0;
    ~IProjectionMatrix() {}
  };

  class BaseProjectionMatrix
    : public virtual IProjectionMatrix
  {
  public:
    BaseProjectionMatrix()
    {
      D3DXMatrixIdentity(&m_projectionMatrix);
    }

    // IProjectionMatrix
  public:
    D3DXMATRIX projectionMatrix() const
    {
      return m_projectionMatrix;
    }

  protected:
    D3DXMATRIX m_projectionMatrix;
  };

  class PerspectiveProjection
    : public virtual BaseProjectionMatrix
  {
  public:
    PerspectiveProjection()
    {
    }

    PerspectiveProjection( double fovy, double aspectRatio, double zNear, double zFar )
    {
      D3DXMatrixPerspectiveFovLH(&m_projectionMatrix, (float)fovy, (float)aspectRatio, (float)zNear, (float)zFar);
    }
  };
} // End of namespace 'projection'

#endif // CAMERA_PROJECTION_H
