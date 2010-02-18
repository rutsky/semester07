// static_matrices.cpp
// Static matrices.
// Vladimir Rutsky, 4057/2
// 17.02.2010

#include "precompiled.h"

#include "static_matrices.h"

namespace constants
{
  namespace matrix
  {
    D3DXMATRIX const identity(
         1,  0,  0,  0,
         0,  1,  0,  0,
         0,  0,  1,  0,
         0,  0,  0,  1);
    
    D3DXMATRIX const naturalCS(
         1,  0,  0,  0,
         0,  0,  1,  0,
         0,  1,  0,  0,
         0,  0,  0,  1);
  } // End of namespace 'matrix'
} // End of namespace 'constants'
