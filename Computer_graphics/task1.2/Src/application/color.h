// color.h
// Color class definition.
// Vladimir Rutsky <altsysrq@gmail.com>
// 09.09.2009

#ifndef COLOR_H
#define COLOR_H

#include "color_fwd.h"

namespace cg
{
  struct color_4b
  {
    unsigned char r, g, b, a;
    
    color_4b()
      : r(0), g(0), b(0), a(255)
    {}
    
    color_4b( unsigned char newR, unsigned char newG, unsigned char newB, unsigned char newA = 255 )
      : r(newR), g(newG), b(newB), a(newA)
    {}
  };
  
  static color_4b color_4b_white() { return color_4b(255, 255, 255); };
  static color_4b color_4b_black() { return color_4b(  0,   0,   0); };
  static color_4b color_4b_red  () { return color_4b(255,   0,   0); };
  static color_4b color_4b_green() { return color_4b(  0, 255,   0); };
  static color_4b color_4b_blue () { return color_4b(  0,   0, 255); };
} // End of namespace 'cg'

#endif // COLOR_H
