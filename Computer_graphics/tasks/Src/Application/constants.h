// constants.h
// Useful constants.
// Vladimir Rutsky, 4057/2
// 10.02.2010

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <windows.h>
#include <d3d9.h>
#include <d3d9types.h>
#include <d3dx9math.h>

namespace constants
{
  double const pi = 3.14159265358979323846;

  namespace color
  {
    inline D3DXCOLOR black() { return D3DCOLOR_ARGB(255,   0,   0,   0); }
    inline D3DXCOLOR white() { return D3DCOLOR_ARGB(255, 255, 255, 255); }
    inline D3DXCOLOR red  () { return D3DCOLOR_ARGB(255, 255,   0,   0); }
    inline D3DXCOLOR green() { return D3DCOLOR_ARGB(255,   0, 255,   0); }
    inline D3DXCOLOR blue () { return D3DCOLOR_ARGB(255,   0,   0, 255); }
  } // End of namespace 'color'
} // End of namespace 'constants'

#endif // CONSTANTS_H
