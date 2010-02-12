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

  class DummyDrawableObject
    : public virtual IDrawableObject
  {
    // IDrawableObject
  public:
    void draw() {}
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

  class BaseWorldMatrixDependentObject
    : public virtual DummyWorldMatrixDependentObject
  {
    // IWorldMatrixDependentObject
  public:
    void updateWorldMatrix( D3DXMATRIX const *worldMatrix )
    {
      m_worldMatrix = *worldMatrix;
    }

  protected:
    D3DXMATRIX m_worldMatrix;
  };

  class ISceneObject
    : public virtual DummyDrawableObject
    , public virtual DummyWorldMatrixDependentObject
    , public virtual DummyDynamicObject
    , public virtual control::DummyControlHandler
  {
  public:
    bool show()
    {
      return m_show;
    }

    void setShow( bool show )
    {
      m_show = show;
    }

  private:
    bool m_show;
  };
} // End of namespace 'object'

#endif // OBJECT_H
