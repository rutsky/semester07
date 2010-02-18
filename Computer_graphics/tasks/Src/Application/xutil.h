// xutil.h
// DirectX utilities.
// Vladimir Rutsky, 4057/2
// 18.02.2010

#ifndef XUTIL_H
#define XUTIL_H

#include <d3d9.h>
#include <d3dx9math.h>

namespace xutil
{
  inline 
  D3DMATERIAL9 material( 
    D3DCOLORVALUE diffuse, 
    D3DCOLORVALUE ambient, 
    D3DCOLORVALUE specular = D3DXCOLOR((DWORD)0), 
    D3DCOLORVALUE emissive = D3DXCOLOR((DWORD)0), 
    float power = 1.0 )
  {
    D3DMATERIAL9 material;
    
    material.Diffuse = diffuse;
    material.Ambient = ambient;
    material.Specular = specular;
    material.Emissive = emissive;
    material.Power = power;

    return material;
  }
} // End of namespace 'xutil'

#endif // XUTIL_H
