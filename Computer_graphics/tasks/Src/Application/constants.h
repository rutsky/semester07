// constants.h
// Useful constants.
// Vladimir Rutsky, 4057/2
// 10.02.2010

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <windows.h>

namespace constants
{
  double const pi = 3.14159265358979323846;

  DWORD const dword_black = RGB(  0,   0,   0);
  DWORD const dword_white = RGB(255, 255, 255);
  DWORD const dword_red   = RGB(255,   0,   0);
  DWORD const dword_green = RGB(0,   255,   0);
  DWORD const dword_blue  = RGB(0,     0, 255);
} // End of namespace 'constants'

#endif // CONSTANTS_H
