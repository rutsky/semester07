// scene.h
// Scene.
// Vladimir Rutsky, 4057/2
// 11.02.2010

#ifndef SCENE_H
#define SCENE_H

#include <boost/shared_ptr.hpp>

#include <d3d9.h>

#include "hierarchy.h"

namespace scene
{
  class IChildRenderWrapper
  {
  public:
    virtual void beginChildsDrawing( IDirect3DDevice9 *device ) = 0;
    virtual void endChildsDrawing( IDirect3DDevice9 *device ) = 0;
    ~IChildRenderWrapper() {}
  };

  template< class U, class V >
  class MultipleChildRenderWrapper
    : public U
    , public V
  {
    // IChildRenderWrapper
  public:
    void beginChildsDrawing( IDirect3DDevice9 *device )
    {
      U::beginChildsDrawing(device);
      V::beginChildsDrawing(device);
    }

    void endChildsDrawing( IDirect3DDevice9 *device )
    {
      U::endChildsDrawing(device);
      V::endChildsDrawing(device);
    }
  };

  class DummyChildRenderWrapper
    : public virtual IChildRenderWrapper
  {
  public:
    void beginChildsDrawing( IDirect3DDevice9 *device ) {}
    void endChildsDrawing( IDirect3DDevice9 *device ) {}
  };

  class ISceneNode
    : public virtual hierarchy::IHierarchyNode<ISceneNode, boost::shared_ptr<ISceneNode>, object::ISceneObject *>
    , public virtual object::ISceneObject
    , public virtual cs::ICoordinateSystem
    , public virtual IChildRenderWrapper
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
    , public virtual DummyChildRenderWrapper
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

  class FillModeSwitch
    : public virtual DummyChildRenderWrapper
  {
  public:
    FillModeSwitch()
      : m_fillMode(D3DFILL_SOLID)
    {
    }

    // IChildRenderWrapper
  public:
    void beginChildsDrawing( IDirect3DDevice9 *device )
    {
      device->GetRenderState(D3DRS_FILLMODE, (DWORD *)&m_prevFillMode);
      device->SetRenderState(D3DRS_FILLMODE, m_fillMode);
    }

    void endChildsDrawing( IDirect3DDevice9 *device )
    {
      device->SetRenderState(D3DRS_FILLMODE, m_prevFillMode);
    }

  protected:
    D3DFILLMODE m_fillMode;

  private:
    D3DFILLMODE m_prevFillMode;
  };

  class CullModeSwitch
    : public virtual DummyChildRenderWrapper
  {
  public:
    CullModeSwitch()
      : m_cullMode(D3DCULL_NONE)
    {
    }

    // IChildRenderWrapper
  public:
    void beginChildsDrawing( IDirect3DDevice9 *device )
    {
      device->GetRenderState(D3DRS_CULLMODE, (DWORD *)&m_prevCullMode);
      device->SetRenderState(D3DRS_CULLMODE, m_cullMode);
    }

    void endChildsDrawing( IDirect3DDevice9 *device )
    {
      device->SetRenderState(D3DRS_CULLMODE, m_prevCullMode);
    }

  protected:
    D3DCULL m_cullMode;

  private:
    D3DCULL m_prevCullMode;
  };

  class RootNode
    : public BaseSceneNode
    , public virtual cs::BaseCoordinateSystem
    , public MultipleChildRenderWrapper<FillModeSwitch, CullModeSwitch>
    , public control::CombineControlHandlers<control::SwitchByKey<D3DFILLMODE, VK_F6>, control::SwitchByKey<D3DCULL, VK_F7> >
  {
  public:
    RootNode()
    {
      control::SwitchByKey<D3DFILLMODE, VK_F6>::init(&m_fillMode, D3DFILL_SOLID, D3DFILL_WIREFRAME, D3DFILL_POINT);
      control::SwitchByKey<D3DCULL, VK_F7>::init(&m_cullMode, D3DCULL_NONE, D3DCULL_CW, D3DCULL_CCW);
    }
  };
} // End of namespace 'scene'

#endif // SCENE_H
