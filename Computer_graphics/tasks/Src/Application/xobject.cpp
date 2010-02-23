// xobject.cpp
// Drawable objects.
// Vladimir Rutsky, 4057/2
// 10.02.2010

#include "precompiled.h"

#include "xobject.h"

namespace xobject
{
  XMesh * XMesh::create( IDirect3DDevice9 *device, char const *dataDirectory, char const *fileName, bool loadTextures, bool loadBumps )
  {
    // Based on DirectX Meshes example.

    ID3DXMesh *mesh;
    DWORD materialsNum;
    LPD3DXBUFFER materialsBuffer;


    {
      std::ostringstream ostr;
      ostr << dataDirectory << "/" << fileName;
      std::string fullFileName = ostr.str();

      // Load the mesh from the specified file.
      HRESULT hr;
      if (FAILED(hr = D3DXLoadMeshFromX(fullFileName.c_str(), 0,
                                   device, NULL,
                                   &materialsBuffer, NULL, &materialsNum,
                                   &mesh)))
        return 0;
    }

    // Extracting the material properties and texture names from the materialsBuffer.
    D3DXMATERIAL *xmaterials = (D3DXMATERIAL *)materialsBuffer->GetBufferPointer();
    materials_map_type materials;
    textures_map_type textures;
    textures_map_type bumps;
    
    for (size_t i = 0; i < materialsNum; ++i)
    {
      // Copy the material.
      materials[i] = xmaterials[i].MatD3D;

      // Set the ambient color for the material (D3DX does not do this).
      materials[i].Ambient = materials[i].Diffuse;

      std::string const textureFileName(xmaterials[i].pTextureFilename);
      if (textureFileName.length() > 0)
      {
        if (loadTextures)
        {
          std::ostringstream ostr;
          ostr << dataDirectory << "/" << textureFileName;

          IDirect3DTexture9 *texture = NULL;
          if (FAILED(D3DXCreateTextureFromFileA(device, ostr.str().c_str(), &texture)))
            OutputDebugString("Failed to load some texture.\n");
          else
            textures[i] = texture;
        }
        
        if (loadBumps)
        {
          size_t dotIdx = textureFileName.rfind('.');
          if (dotIdx != std::string::npos)
          {
            std::string bumpTextureFileName = textureFileName;
            bumpTextureFileName.insert(dotIdx, "_bumpmap");
            
            std::ostringstream ostr;
            ostr << dataDirectory << "/" << bumpTextureFileName;

            IDirect3DTexture9 *texture = NULL;
            if (FAILED(D3DXCreateTextureFromFileA(device, ostr.str().c_str(), &texture)))
              OutputDebugString("Failed to load some texture.\n");
            else
              bumps[i] = texture;
          }
        }
      }
    }

    // Done with the material buffer.
    materialsBuffer->Release();

    return new XMesh(device, mesh, materials, textures, bumps);
  }
} // End of namespace 'xobject'
