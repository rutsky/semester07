// hierarchy.h
// Objects hierarchy classes declaration.
// Vladimir Rutsky, 4057/2
// 09.02.2010

#ifndef HIERARCHY_H
#define HIERARCHY_H

#include <vector>
#include <cassert>

#include <d3dx9math.h>

#include "object.h"
#include "cs.h"
#include "control.h"
#include "common_controls.h"

namespace hierarchy
{
  template< class NodePtr >
  class IChildNodePtrsManager
  {
  public:
    typedef NodePtr node_ptr_type;

    virtual size_t childNodesNum() const = 0;
    virtual node_ptr_type childNode( size_t idx ) const = 0;
    virtual void addChildNode( node_ptr_type node ) = 0;
    virtual void removeChildNode( size_t idx ) = 0;

    virtual ~IChildNodePtrsManager() {}
  };

  template< class NodePtr >
  class IParentNodeManager
  {
  public:
    typedef NodePtr node_ptr_type;

    virtual node_ptr_type parent() const = 0;

    virtual ~IParentNodeManager() {}
  };

  template< class NodePtr >
  class IWritableParentNodeManager
    : public virtual IParentNodeManager<NodePtr>
  {
  public:
    typedef NodePtr node_ptr_type;

    virtual void setParent( node_ptr_type node ) = 0;
  };

  template< class Object >
  class IObjectsManager
  {
  public:
    typedef Object object_type;

    virtual size_t objectsNum() const = 0;
    virtual object_type object( size_t idx ) const = 0;
    virtual void addObject( object_type node ) = 0;
    virtual void removeObject( size_t idx ) = 0;

    virtual ~IObjectsManager() {}
  };

  template< class NodeType, class NodePtrType, class ObjectType >
  class IHierarchyNode 
    : public virtual IChildNodePtrsManager<NodePtrType>
    , public virtual IWritableParentNodeManager<NodeType *>
    , public virtual cs::ICoordinateSystem
    , public virtual IObjectsManager<ObjectType>
  {
  public:
    typedef NodeType node_type;
    typedef NodePtrType node_ptr_type;
    typedef ObjectType object_type;
  };

  template< class NodePtr >
  class VectorChildNodesManager
    : public virtual IChildNodePtrsManager<NodePtr>
  {
  public:
    typedef NodePtr node_ptr_type;

    size_t childNodesNum() const
    {
      return childs.size();
    }

    node_ptr_type childNode( size_t idx ) const
    {
      assert(idx < childs.size());
      return childs[idx];
    }

    void addChildNode( node_ptr_type node )
    {
      childs.push_back(node);
      node->setParent(dynamic_cast<node_ptr_type::value_type *>(this));
    }

    void removeChildNode( size_t idx )
    {
      assert(idx < childs.size());
      node_ptr_type child = childs[idx];
      childs.erase(childs.begin() + idx);
      child->setParent(0);
    }

  protected:
    std::vector<node_ptr_type> childs;
  };

  template< class Object >
  class VectorObjectsManager
    : public virtual IObjectsManager<Object>
  {
  public:
    typedef Object object_type;

    size_t objectsNum() const
    {
      return objects.size();
    }

    object_type object( size_t idx ) const
    {
      assert(idx < objects.size());
      return objects[idx];
    }

    void addObject( object_type object )
    {
      objects.push_back(object);
    }

    void removeObject( size_t idx )
    {
      assert(idx < objects.size());
      objects.erase(objects.begin() + idx);
    }

  protected:
    std::vector<object_type> objects;
  };

  template< class NodePtr >
  class BaseWritableParentNodeManager
    : public virtual IWritableParentNodeManager<NodePtr>
  {
  public:
    typedef NodePtr node_ptr_type;

    BaseWritableParentNodeManager()
      : m_parent(0)
    {
    }

    // IParentNodeManager
  public:
    node_ptr_type parent() const
    {
      return m_parent;
    }

    // IWritableParentNodeManager
  protected:
    void setParent( node_ptr_type node )
    {
      m_parent = node;
    }

  protected:
    node_ptr_type m_parent;
  };

  template< class NodePtr >
  inline D3DXMATRIX evaluateWorldMatrix( NodePtr node )
  {
    D3DXMATRIX result;
    D3DXMatrixIdentity(&result);

    if (node)
    {
      node = node->parent();
      while (node)
        result = node->matrix() * result;
    }
    
    return result;
  }

  template< class SceneNode >
  inline SceneNode * newSceneNode( object::ISceneObject *sceneObject )
  {
    SceneNode *newSceneNode = new SceneNode;
    newSceneNode->addObject(sceneObject);
    return newSceneNode;
  }
} // End of namespace 'hierarchy'

#endif // HIERARCHY_H
