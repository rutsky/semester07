// triangle.h
// Triangle class definition.
// Vladimir Rutsky <altsysrq@gmail.com>
// 09.09.2009

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "point.h"

namespace cg
{
  struct triangle_4f
  {
    point_4f p0, p1, p2;
    
    triangle_4f()
    {}
    
    triangle_4f( point_4f const &newP0, point_4f const &newP1, point_4f const &newP2 )
      : p0(newP0), p1(newP1), p2(newP2)
    {}
  };
} // End of namespace 'cg'

#endif // TRIANGLE_H
