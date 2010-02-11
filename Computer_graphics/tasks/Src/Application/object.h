// object.h
// Object description.
// Vladimir Rutsky, 4057/2
// 09.02.2010

#ifndef OBJECT_H
#define OBJECT_H

#include <d3d9.h>

#include "cs.h"
#include "control.h"

namespace object
{
  class IDrawableObject
  {
  public:
    virtual void draw() = 0;
    virtual ~IDrawableObject() {}
  };

  class IDynamicObject
  {
  public:
    virtual void update( double time ) = 0;
    virtual ~IDynamicObject() {}
  };

  class BaseDynamicObject
    : public IDynamicObject
  {
  public:
    BaseDynamicObject()
      : m_time(-1)
    {
    }

  public:
    // Should be called at begin of successor update()
    virtual void update( double time )
    {
      if (m_time == -1)
        m_time = time;
      m_dtime = time - m_time;
      m_time = time;
    }

  protected:
    double dtime() const
    {
      return m_dtime;
    }

  protected:
    double m_time;
    double m_dtime;
  };

  class IWorldMatrixDependentObject
  {
  public:
    virtual void update( D3DXMATRIX const *worldMatrix ) = 0;
    virtual ~IWorldMatrixDependentObject() {}
  };

  class ISceneObject
    : public virtual IDrawableObject
    , public virtual IWorldMatrixDependentObject
    , public IDynamicObject
    , public control::IControlHandler
  {
    // IDrawableObject
  public:
    virtual void draw() {}

    // IDynamicObject
  public:
    virtual void update( double time ) {}

    // IWorldMatrixDependentObject
  public:
    virtual void update( D3DXMATRIX const *worldMatrix ) {}
  };
} // End of namespace 'object'

#endif // OBJECT_H
