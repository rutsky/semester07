// texture.h
// Textures stuff.
// Vladimir Rutsky, 4057/2
// 18.02.2010

#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>
#include <string>

#include <d3d9.h>

namespace texture
{
  template< class FileNameIterator >
  inline IDirect3DTexture9 * loadTextureWithMipmaps( IDirect3DDevice9 *device,
    size_t width, size_t height, D3DFORMAT format,
    char const *dataDirectory, 
    FileNameIterator textureFirst, FileNameIterator textureBeyond )
  {
    assert(textureFirst != textureBeyond);

    std::vector<std::string> textureNames;
    while (textureFirst != textureBeyond)
    {
      textureNames.push_back(std::string(dataDirectory) + "/" + std::string(*textureFirst));
      ++textureFirst;
    }

    IDirect3DTexture9 *texture;
    device->CreateTexture(width, height, textureNames.size(), 0, format, D3DPOOL_DEFAULT, &texture, NULL);
    if (!texture)
      return NULL;

    for (size_t i = 0; i < textureNames.size(); ++i)
    {
      IDirect3DSurface9 *surface;
      texture->GetSurfaceLevel(i, &surface);
      if (FAILED(D3DXLoadSurfaceFromFile(surface, NULL, NULL, textureNames[i].c_str(), NULL, D3DX_DEFAULT, 0, NULL)))
      {
        texture->Release();
        return NULL;
      }
      surface->Release();
    }

    return texture;
  }
} // End of namespace 'texture'

#endif // TEXTURE_H
