// hierarchy.h
// Objects hierarchy classes declaration.
// Vladimir Rutsky, 4057/2
// 09.02.2010

#ifndef HIERARCHY_H
#define HIERARCHY_H

#include <vector>
#include <cassert>

#include <d3dx9math.h>

#include "Library/cglApp.h"

template< class ChildPtr >
class IChildPtrsManager
{
public:
  typedef ChildPtr child_ptr_type;

  virtual size_t getChildsNum() const = 0;
  virtual child_ptr_type getChild( size_t idx ) const = 0;
  virtual void addChild( child_ptr_type node ) = 0;
  virtual void removeChild( size_t idx ) = 0;

  virtual ~IChildPtrsManager() {};
};

template< class Object >
class IHierarchyNode 
  : public IChildPtrsManager<IHierarchyNode<Object> *>
{
public:
  typedef Object object_type;

  virtual D3DXMATRIX matrix( double time ) const = 0;
  virtual object_type object() = 0;

  virtual ~IHierarchyNode() {};
};

template< class ChildPtr >
class VectorChildsManager
  : IChildPtrsManager<ChildPtr>
{
  size_t getChildsNum() const
  {
    return childs.size();
  }

  ChildPtr getChild( size_t idx ) const
  {
    assert(idx < childs.size());
    return childs[idx];
  }

  void addChild( ChildPtr node )
  {
    childs.push_back(node);
  }

  void removeChild( size_t idx )
  {
    assert(idx < childs.size());
    childs.erase(childs.begin() + idx);
  }

protected:
  std::vector<ChildPtr> childs;
};

#endif // HIERARCHY_H
