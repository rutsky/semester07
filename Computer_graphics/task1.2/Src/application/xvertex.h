// xvertex.h
// Common DirectX vertices structures definitions.
// Vladimir Rutsky <altsysrq@gmail.com>
// 09.09.2009

#ifndef XVERTEX_H
#define XVERTEX_H

#include "xvertex_fwd.h"
#include "point_fwd.h"
#include "color_fwd.h"

#include <d3dx9.h>

namespace xcg
{
  // Common vertex with a lot of parameters.
  struct vertex
  {
    float x, y, z, rhw;
    DWORD color;
  };
  
  DWORD const VERTEX_FVF = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
} // End of namespace 'xcg'

// TODO: Move to separate file.
namespace xcg
{
  vertex & set_vertex_position( vertex &v, cg::point_4f const &p )
  {
    v.x   = p.x;
    v.y   = p.y;
    v.z   = p.z;
    v.rhw = p.w;
    return v;
  }
  
  vertex & set_vertex_color( vertex &v, cg::color_4b const &c )
  {
    v.color = D3DCOLOR_ARGB(c.a, c.r, c.g, c.b);
    return v;
  }
} // End of namespace 'xcg'

#endif // XVERTEX_H
