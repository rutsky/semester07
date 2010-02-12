// scene.h
// Scene.
// Vladimir Rutsky, 4057/2
// 11.02.2010

#ifndef SCENE_H
#define SCENE_H

#include <boost/shared_ptr.hpp>

#include "hierarchy.h"

namespace scene
{
  class ISceneNode
    : public virtual hierarchy::IHierarchyNode<ISceneNode, boost::shared_ptr<ISceneNode>, object::ISceneObject *>
    , public virtual object::ISceneObject
  {
  };

  typedef boost::shared_ptr<ISceneNode> ISceneNodePtr;

  class BaseSceneNode
    : public virtual ISceneNode
    , public hierarchy::VectorChildNodesManager<ISceneNodePtr>
    , public hierarchy::BaseWritableParentNodeManager<ISceneNode *>
    , public virtual object::BaseDynamicObject
    , public virtual hierarchy::VectorObjectsManager<object::ISceneObject *>
  {
  };

  class SimpleSceneNode
    : public BaseSceneNode
    , public virtual cs::BaseCoordinateSystem
  {
  public:
    SimpleSceneNode()
    {
    }

    SimpleSceneNode( D3DXVECTOR3 const &translation )
    {
      D3DXMatrixTranslation(&m_matrix, translation[0], translation[1], translation[2]);
    }
  };

  class RotatingSceneNode
    : public SimpleSceneNode
  {
  public:
    RotatingSceneNode( D3DXVECTOR3 axis, double speed )
      : m_axis(axis)
      , m_speed(speed)
    {
    }

    // IDynamicObject 
  public:
    void update( double time )
    {
      BaseDynamicObject::update(time);

      D3DXMatrixRotationAxis(&m_matrix, &m_axis, (float)(m_speed * time)); // FIXME: Overflows
    }

  protected:
    D3DXVECTOR3 m_axis;
    double m_speed;
  };

  class LCSArrowPgUpPgDownMoveSceneNode
    : public SimpleSceneNode
    , public control::LCSArrowPgUpPgDownMove
  {
  };

  class LCSArrowPgUpPgDownRotateNode
    : public SimpleSceneNode
    , public control::LCSArrowPgUpPgDownRotate
  {
  };
} // End of namespace 'scene'

#endif // SCENE_H
