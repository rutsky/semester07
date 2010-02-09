// cs.h
// Coordinate system class.
// Vladimir Rutsky, 4057/2
// 09.02.2010

#ifndef CS_H
#define CS_H

#include <d3dx9math.h>

namespace cs
{
  class ICoordinateSystem
  {
  public:
    virtual D3DXMATRIX matrix() const = 0;
    virtual ~ICoordinateSystem() {};
  };

  class IWritableCoordinateSystem
    : public virtual ICoordinateSystem
  {
  public:
    virtual void setMatrix( D3DXMATRIX const *newMatrix ) = 0;
  };

  class BaseCoordinateSystem
    : public virtual IWritableCoordinateSystem
  {
  public:
    BaseCoordinateSystem()
    {
      D3DXMatrixIdentity(&m_matrix);
    }

    // ICoordinateSystem
  public:
    D3DXMATRIX matrix() const
    {
      return m_matrix;
    }

    void setMatrix( D3DXMATRIX const *newMatrix )
    {
      m_matrix = *newMatrix;
    }

  protected:
    D3DXMATRIX m_matrix;
  };
} // End of namespace 'cs'

#endif // CS_H
