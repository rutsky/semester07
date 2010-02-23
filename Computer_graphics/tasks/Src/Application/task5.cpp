// task5.cpp
// Minnaert shading shader.
// Vladimir Rutsky, 4057/2
// 23.02.2010

#include "precompiled.h"

#include "task5.h"

namespace scene
{
  bool Task5Node::init( IDirect3DDevice9 *device )
  {
    if (m_initialized)
      return false;

    m_device = device;

    m_mesh.reset(xobject::XMesh::create(device, "data/dwarf", "dwarf.x", true, true)); 
    if (!m_mesh)
      return false;

    DWORD shaderFlags = D3DXFX_NOT_CLONEABLE;
#ifndef NDEBUG
    shaderFlags |= D3DXSHADER_DEBUG;
    shaderFlags |= D3DXSHADER_NO_PRESHADER;
#endif // NDEBUG

    if (FAILED(D3DXCreateEffectFromFile(device, "effects/minnaert.fx", NULL, NULL, shaderFlags, NULL, &m_effect, NULL)))
      return false;

    D3DXCOLOR materialAmbientColor(0.3f, 0.3f, 0.3f, 1.0f);
    D3DXCOLOR materialDiffuseColor(0.7f, 0.7f, 0.7f, 1.0f);
    D3DXVECTOR3 lightDir(-1.0f, 0.0f, -1.0f);
    D3DXCOLOR lightDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
    D3DXCOLOR lightAmbient(1.0f, 1.0f, 1.0f, 1.0f);

    float minnaertK = (float)m_minnaertK;
    BOOST_VERIFY(m_effect->SetValue("g_MinnaertK", &minnaertK, sizeof(minnaertK)) == D3D_OK);
    BOOST_VERIFY(m_effect->SetValue("g_LightDir", &lightDir, sizeof(lightDir)) == D3D_OK);
    BOOST_VERIFY(m_effect->SetValue("g_LightDiffuse", &lightDiffuse, sizeof(lightDiffuse)) == D3D_OK);
    BOOST_VERIFY(m_effect->SetValue("g_LightAmbient", &lightAmbient, sizeof(lightAmbient)) == D3D_OK);
    
    m_initialized = true;
    return true;
  }

  void Task5Node::draw()
  {
    BOOST_VERIFY(m_effect->SetValue("g_mWorld", &m_worldMatrix, sizeof(m_worldMatrix)) == D3D_OK);
    D3DXMATRIX worldViewProjection = m_worldMatrix * m_viewProjectionMatrix;
    BOOST_VERIFY(m_effect->SetValue("g_mWorldViewProjection", &worldViewProjection, sizeof(worldViewProjection)) == D3D_OK);

    BOOST_VERIFY(m_effect->SetTechnique("RenderSceneWithTexturedDiffuse") == D3D_OK);

    // Apply the technique contained in the effect 
    size_t nPasses;
    BOOST_VERIFY(m_effect->Begin(&nPasses, 0) == D3D_OK);

    for (size_t pass = 0; pass < nPasses; ++pass)
    {
      BOOST_VERIFY(m_effect->BeginPass(pass) == D3D_OK);

      DWORD size;
      //m_mesh->m_mesh->GetAttributeTable(NULL, &size); // TODO: Not sure, not sure...
      size = m_mesh->m_materials.size();
      for (size_t i = 0; i < size; ++i)
      {
        {
          xobject::XMesh::materials_map_type::const_iterator it = m_mesh->m_materials.find(i);
          if (it != m_mesh->m_materials.end())
          {
            BOOST_VERIFY(m_effect->SetValue("g_MaterialAmbientColor", &it->second.Ambient, sizeof(it->second.Ambient)) == D3D_OK);
            BOOST_VERIFY(m_effect->SetValue("g_MaterialDiffuseColor", &it->second.Diffuse, sizeof(it->second.Diffuse)) == D3D_OK);
          }
        }

        {
          xobject::XMesh::textures_map_type::const_iterator it = m_mesh->m_textures.find(i);
          if (it != m_mesh->m_textures.end())
            BOOST_VERIFY(m_effect->SetTexture("g_ColorTexture", it->second) == D3D_OK);
        }

        {
          xobject::XMesh::textures_map_type::const_iterator it = m_mesh->m_bumps.find(i);
          if (it != m_mesh->m_bumps.end())
            BOOST_VERIFY(m_effect->SetTexture("g_NormalTexture", it->second) == D3D_OK);
        }

        BOOST_VERIFY(m_effect->CommitChanges() == D3D_OK);

        m_mesh->m_mesh->DrawSubset(i);
      }

      BOOST_VERIFY(m_effect->EndPass() == D3D_OK);
    }
    BOOST_VERIFY(m_effect->End() == D3D_OK);
  }
} // End of namespace 'scene'
