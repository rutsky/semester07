// object.h
// Object description.
// Vladimir Rutsky, 4057/2
// 09.02.2010

#ifndef OBJECT_H
#define OBJECT_H

#include <d3d9.h>

namespace object
{
  class IDrawableObject
  {
  public:
    virtual void draw() = 0;
    virtual ~IDrawableObject() {};
  };

  class IDynamicObject
  {
  public:
    virtual void update( double time ) = 0;
    virtual ~IDynamicObject() {};
  };

  class ISceneObject
    : public virtual IDrawableObject
    , public virtual IDynamicObject
  {
    // IDynamicObject
  public:
    void update( double time ) {};

    virtual ~ISceneObject() {};
  };
} // End of namespace 'object'

#endif // OBJECT_H
