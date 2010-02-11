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

  class DummyDynamicObject
    : public virtual IDynamicObject
  {
    // IDynamicObject
  public:
    virtual void update( double time ) {}
  };

  class BaseDynamicObject
    : public virtual DummyDynamicObject
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
    virtual void updateWorldMatrix( D3DXMATRIX const *worldMatrix ) = 0;
    virtual ~IWorldMatrixDependentObject() {}
  };

  class DummyWorldMatrixDependentObject
    : public virtual IWorldMatrixDependentObject
  {
  public:
    virtual void updateWorldMatrix( D3DXMATRIX const *worldMatrix ) {}
  };

  class ISceneObject
    : public virtual IDrawableObject
    , public virtual DummyWorldMatrixDependentObject
    , public virtual DummyDynamicObject
    , public control::IControlHandler
  {
    // IDrawableObject
  public:
    virtual void draw() {}
  };
} // End of namespace 'object'

#endif // OBJECT_H
