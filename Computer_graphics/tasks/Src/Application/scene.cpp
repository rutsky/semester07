// scene.cpp
// Scene.
// Vladimir Rutsky, 4057/2
// 12.02.2010

#include "precompiled.h"

#include "scene.h"

namespace scene
{
  void TextureTransformNode::beginChildsDrawing( IDirect3DDevice9 *device )
  {
    device->GetTransform(D3DTS_TEXTURE0, &m_oldTransform);
    device->GetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, &m_oldTransformFlags);

    device->SetTransform(D3DTS_TEXTURE0, &m_transform);
    device->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
  }
} // End of namespace 'scene'
