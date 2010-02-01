// point.h
// Point class definition.
// Vladimir Rutsky <altsysrq@gmail.com>
// 09.09.2009

#ifndef POINT_H
#define POINT_H

#include "point_fwd.h"

namespace cg
{
  struct point_4f
  {
    float x, y, z, w;
    
    point_4f()
      : x(0.0f), y(0.0f), z(0.0f), w(1.0f)
    {}
    
    point_4f( float newX, float newY, float newZ, float newW = 1.0f )
      : x(newX), y(newY), z(newZ), w(newW)
    {}
  };
} // End of namespace 'cg'

#endif // POINT_H
