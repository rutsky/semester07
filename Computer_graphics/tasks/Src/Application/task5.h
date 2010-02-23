// task5.h
// Minnaert shading shader.
// Vladimir Rutsky, 4057/2
// 22.02.2010

#ifndef TASK5_H
#define TASK5_H

#include <boost/scoped_ptr.hpp>
#include <boost/assert.hpp>

#include "scene.h"
#include "xobject.h"
#include "constants.h"

namespace scene
{
  class Task5Node
    : public virtual BaseSceneNode 
    , public virtual cs::BaseCoordinateSystem
    , public virtual DummyChildRenderWrapper
    , public virtual object::BaseWorldMatrixDependentObject
  {
  public:
    Task5Node()
      : m_initialized(false)
      , m_minnaertK(0.5)
      , m_device(0)
      , m_useTexture(true)
      , m_technique(0)
    {
      m_viewProjectionMatrix = constants::matrix::identity;
    }

    ~Task5Node()
    {
      if (m_initialized)
      {
        m_effect->Release();
      }
    }

    bool init( IDirect3DDevice9 *device );
    
    void setViewProjectionMatrix( D3DXMATRIX const &viewProjectionMatrix )
    {
      m_viewProjectionMatrix = viewProjectionMatrix;
    }

    double minnaertK() const
    {
      return m_minnaertK;
    }
    void setMinnaertK( double k )
    {
      m_minnaertK = k;
    }

    bool textured() const
    {
      return m_useTexture;
    }
    void useTexture( bool flag )
    {
      m_useTexture = flag;
    }

    size_t technique() const
    {
      return m_technique;
    }

    void setTechnique( size_t technique )
    {
      m_technique = technique;
    }

    // IDrawableObject
  public:
    void draw();

  protected:
    bool m_initialized;

    IDirect3DDevice9 *m_device;
    
    D3DXMATRIX m_viewProjectionMatrix;

    ID3DXEffect *m_effect;
    boost::scoped_ptr<xobject::XMesh> m_mesh;
    
    double m_minnaertK;
    bool m_useTexture;
    size_t m_technique;
  };
} // End of namespace 'scene'

#endif // TASK5_H
