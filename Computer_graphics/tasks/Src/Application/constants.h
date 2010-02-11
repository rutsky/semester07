// constants.h
// Useful constants.
// Vladimir Rutsky, 4057/2
// 10.02.2010

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <windows.h>
#include <d3d9types.h>

namespace constants
{
  double const pi = 3.14159265358979323846;

  namespace color
  {
    D3DCOLOR const black = D3DCOLOR_ARGB(255,   0,   0,   0);
    D3DCOLOR const white = D3DCOLOR_ARGB(255, 255, 255, 255);
    D3DCOLOR const red   = D3DCOLOR_ARGB(255, 255,   0,   0);
    D3DCOLOR const green = D3DCOLOR_ARGB(255,   0, 255,   0);
    D3DCOLOR const blue  = D3DCOLOR_ARGB(255,   0,   0, 255);
  } // End of namespace 'color'
} // End of namespace 'constants'

#endif // CONSTANTS_H
