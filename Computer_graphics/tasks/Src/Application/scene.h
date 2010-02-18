// scene.h
// Scene.
// Vladimir Rutsky, 4057/2
// 11.02.2010

#ifndef SCENE_H
#define SCENE_H

#include <map>

#include <boost/shared_ptr.hpp>

#include <d3d9.h>

#include "hierarchy.h"
#include "static_matrices.h"

namespace scene
{
  class IChildRenderWrapper
  {
  public:
    virtual void beginChildsDrawing( IDirect3DDevice9 *device ) = 0;
    virtual void endChildsDrawing( IDirect3DDevice9 *device ) = 0;
    ~IChildRenderWrapper() {}
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

    SimpleSceneNode( D3DXMATRIX const &transform )
    {
      m_matrix = transform;
    }
  };

  class XMeshNode
    : public SimpleSceneNode
  {
  public:
    XMeshNode()
    {
      m_matrix = constants::matrix::naturalCS;
    }
  };

  class RotatingSceneNode
    : public SimpleSceneNode
  {
  public:
    RotatingSceneNode( D3DXVECTOR3 axis, double speed )
      : m_axis(axis)
      , m_speed(speed)
      , m_paused(false)
    {
    }

    // IDynamicObject 
  public:
    void update( double time )
    {
      BaseDynamicObject::update(time);

      // FIXME: Not precise.
      D3DXMATRIX rotationMatrix = constants::matrix::identity;

      if (!m_paused)
        D3DXMatrixRotationAxis(&rotationMatrix, &m_axis, (float)(m_speed * dtime()));

      m_matrix *= rotationMatrix;
    }

  public:
    bool isPaused() const
    {
      return m_paused;
    }

    void pause( bool p )
    {
      m_paused = p;
    }

  protected:
    D3DXVECTOR3 m_axis;
    double m_speed;

    bool m_paused;
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

  class MagFilterSwitch
    : public virtual DummyChildRenderWrapper
  {
  public:
    MagFilterSwitch()
      : m_magFilter(D3DTEXF_LINEAR)
    {
    }

    // IChildRenderWrapper
  public:
    void beginChildsDrawing( IDirect3DDevice9 *device )
    {
      device->GetSamplerState(0, D3DSAMP_MAGFILTER, (DWORD *)&m_prevMagFilter);
      device->SetSamplerState(0, D3DSAMP_MAGFILTER, m_magFilter);
    }

    void endChildsDrawing( IDirect3DDevice9 *device )
    {
      device->SetSamplerState(0, D3DSAMP_MAGFILTER, m_prevMagFilter);
    }

  protected:
    D3DTEXTUREFILTERTYPE m_magFilter;

  private:
    D3DTEXTUREFILTERTYPE m_prevMagFilter;
  };

  class MinFilterSwitch
    : public virtual DummyChildRenderWrapper
  {
  public:
    MinFilterSwitch()
      : m_minFilter(D3DTEXF_LINEAR)
    {
    }

    // IChildRenderWrapper
  public:
    void beginChildsDrawing( IDirect3DDevice9 *device )
    {
      device->GetSamplerState(0, D3DSAMP_MINFILTER, (DWORD *)&m_prevMinFilter);
      device->SetSamplerState(0, D3DSAMP_MINFILTER, m_minFilter);
    }

    void endChildsDrawing( IDirect3DDevice9 *device )
    {
      device->SetSamplerState(0, D3DSAMP_MINFILTER, m_prevMinFilter);
    }

  protected:
    D3DTEXTUREFILTERTYPE m_minFilter;

  private:
    D3DTEXTUREFILTERTYPE m_prevMinFilter;
  };

  class LightsNode
    : public virtual BaseSceneNode 
    , public virtual cs::BaseCoordinateSystem
    , public virtual DummyChildRenderWrapper
    , public virtual object::BaseWorldMatrixDependentObject
  {
  protected:
    struct LightDescr
    {
      LightDescr()
        : enabled(true)
      {
      }

      D3DLIGHT9 light;
      bool enabled;
    };

    typedef std::map<size_t, LightDescr> lights_map_type;

  public:
    void addLight( size_t index, D3DLIGHT9 light )
    {
      m_lights[index].light = light;
    }

    void removeLight( size_t index )
    {
      lights_map_type::iterator it = m_lights.find(index);
      if (it != m_lights.end())
        m_lights.erase(it);
      else
      {
        assert(0);
      }
    }

    void enableLight( size_t index, bool enabled )
    {
      lights_map_type::iterator it = m_lights.find(index);
      if (it != m_lights.end())
      {
        it->second.enabled = enabled;
      }
      else
      {
        assert(0);
      }
    }

    // IChildRenderWrapper
  public:
    void beginChildsDrawing( IDirect3DDevice9 *device )
    {
      for (lights_map_type::const_iterator it = m_lights.begin(); it != m_lights.end(); ++it)
      {
        size_t const index = it->first;
        LightDescr const lightDescr = it->second;

        if (!lightDescr.enabled)
          continue;

        D3DLIGHT9 light = lightDescr.light;
        
        {
          D3DXVECTOR4 pos(lightDescr.light.Position.x, lightDescr.light.Position.y, lightDescr.light.Position.z, 1);
          D3DXVec4Transform(&pos, &pos, &m_worldMatrix);
          light.Position.x = pos.x;
          light.Position.y = pos.y;
          light.Position.z = pos.z;
        }

        {
          D3DXMATRIX transform = m_worldMatrix;
          transform(3, 0) = 0;
          transform(3, 1) = 0;
          transform(3, 2) = 0;

          D3DXVECTOR4 dir(lightDescr.light.Direction.x, lightDescr.light.Direction.y, lightDescr.light.Direction.z, 1);
          D3DXVec4Transform(&dir, &dir, &transform);
          light.Direction.x = dir.x;
          light.Direction.y = dir.y;
          light.Direction.z = dir.z;
        }

        device->SetLight(index, &light);
        device->LightEnable(index, true);
      }
    }

    void endChildsDrawing( IDirect3DDevice9 *device )
    {
      for (lights_map_type::const_iterator it = m_lights.begin(); it != m_lights.end(); ++it)
      {
        size_t const index = it->first;
        LightDescr const lightDescr = it->second;

        /*
        if (!lightDescr.enabled)
          continue;

        device->LightEnable(index, false);
        */
        if (!lightDescr.enabled)
          device->LightEnable(index, false);
      }
    }

  protected:
    lights_map_type m_lights;
  };

  class RootNode
    : public virtual BaseSceneNode
    , public virtual cs::BaseCoordinateSystem
    , public MultipleChildRenderWrapper<
        FillModeSwitch,
        MultipleChildRenderWrapper<
          CullModeSwitch, 
          MultipleChildRenderWrapper<
            LightsNode,
            MultipleChildRenderWrapper<
              MagFilterSwitch,
              MinFilterSwitch>
            >
          >
        >
    , public control::CombineControlHandlers<
        control::SwitchByKey<D3DFILLMODE, VK_F6>,
        control::CombineControlHandlers<
          control::SwitchByKey<D3DCULL, VK_F7>, 
          control::CombineControlHandlers<
            control::SwitchByKey<D3DTEXTUREFILTERTYPE, 'G'>,
            control::SwitchByKey<D3DTEXTUREFILTERTYPE, 'F'>
          >
        >
      >
  {
  public:
    RootNode()
    {
      control::SwitchByKey<D3DFILLMODE, VK_F6>::init(&m_fillMode, D3DFILL_SOLID, D3DFILL_WIREFRAME, D3DFILL_POINT);
      control::SwitchByKey<D3DCULL, VK_F7>::init(&m_cullMode, D3DCULL_NONE, D3DCULL_CW, D3DCULL_CCW);
      control::SwitchByKey<D3DTEXTUREFILTERTYPE, 'G'>::init(&m_magFilter, D3DTEXF_LINEAR, D3DTEXF_POINT);
      control::SwitchByKey<D3DTEXTUREFILTERTYPE, 'F'>::init(&m_minFilter, D3DTEXF_LINEAR, D3DTEXF_POINT);
    }
  };
} // End of namespace 'scene'

#endif // SCENE_H
