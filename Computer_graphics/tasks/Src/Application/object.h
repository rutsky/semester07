// object.h
// Object description classes declaration.
// Vladimir Rutsky, 4057/2
// 09.02.2010

#ifndef OBJECT_H
#define OBJECT_H

class IDrawableObject
{
public:
  virtual void draw( IDirect3DDevice9 *device ) = 0;
  virtual ~IDrawableObject() {};
};

class IDynamicObject
{
public:
  virtual void update( double time ) = 0;
  virtual ~IDynamicObject() {};
};

class ISceneObject
  : public IDrawableObject
  , public IDynamicObject
{
  // IDynamicObject
public:
  void update( double time ) {};

  virtual ~ISceneObject() {};
};

#endif // OBJECT_H
