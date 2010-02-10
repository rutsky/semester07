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

namespace hierarchy
{
  template< class Node >
  class IChildNodePtrsManager
  {
  public:
    typedef Node * node_ptr_type;

    virtual size_t childNodesNum() const = 0;
    virtual node_ptr_type childNode( size_t idx ) const = 0;
    virtual void addChildNode( node_ptr_type node ) = 0;
    virtual void removeChildNode( size_t idx ) = 0;

    virtual ~IChildNodePtrsManager() {}
  };

  template< class Node >
  class IParentNodeManager
  {
  public:
    typedef Node * node_ptr_type;

    virtual node_ptr_type parent() const = 0;

    virtual ~IParentNodeManager() {}
  };

  template< class Node >
  class IWritableParentNodeManager
    : public virtual IParentNodeManager<Node>
  {
  public:
    typedef Node * node_ptr_type;

    virtual void setParent( node_ptr_type node ) = 0;
  };

  template< class Object >
  class IObjectManager
  {
  public:
    typedef Object object_type;

    virtual object_type object() = 0;

    virtual ~IObjectManager() {}
  };

  template< class Object >
  class IWritableObjectManager
    : public virtual IObjectManager<Object>
  {
  public:
    typedef Object object_type;

    virtual void setObject( object_type object ) = 0;
  };

  template< class NodeType, class Object >
  class IHierarchyNode 
    : public virtual IChildNodePtrsManager<NodeType>
    , public virtual IWritableParentNodeManager<NodeType>
    , public virtual cs::ICoordinateSystem
    , public virtual IObjectManager<Object>
  {
  public:
    typedef NodeType node_type;
    typedef node_type * node_ptr_type;
    typedef Object object_type;
  };

  template< class Node >
  class VectorChildNodesManager
    : public virtual IChildNodePtrsManager<Node>
  {
  public:
    typedef Node * node_ptr_type;

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
      node->setParent(dynamic_cast<node_ptr_type>(this));
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

  template< class Node >
  class BaseWritableParentNodeManager
    : public virtual IWritableParentNodeManager<Node>
  {
  public:
    typedef Node * node_ptr_type;

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

  template< class Object >
  class BaseWritableObjectManager
    : public virtual IWritableObjectManager<Object>
  {
  public:
    typedef Object object_type;

    // IObjectManager
  public:
    object_type object()
    {
      return m_object;
    }

  // IWritableObjectManager
  public:
    void setObject( object_type object )
    {
      m_object = object;
    }

  protected:
    object_type m_object;
  };

  template< class Node >
  inline D3DXMATRIX evaluateWorldMatrix( Node *node )
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

  class ISceneNode
    : public virtual IHierarchyNode<ISceneNode, object::ISceneObject *>
  {
  };

  class BaseSceneNode
    : public virtual ISceneNode
    , public VectorChildNodesManager<ISceneNode>
    , public BaseWritableParentNodeManager<ISceneNode>
  {
  };

  class SimpleSceneNode
    : public BaseSceneNode
    , public cs::BaseCoordinateSystem
    , public BaseWritableObjectManager<object::ISceneObject *>
  {
  public:
    SimpleSceneNode()
    {
      setObject(0);
    }

    SimpleSceneNode( object::ISceneObject *sceneObject )
    {
      setObject(sceneObject);
    }
  };
} // End of namespace 'hierarchy'

#endif // HIERARCHY_H
