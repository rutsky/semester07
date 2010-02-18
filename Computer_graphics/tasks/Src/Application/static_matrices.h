// static_matrices.h
// Static matrices.
// Vladimir Rutsky, 4057/2
// 17.02.2010

#ifndef STATIC_MATRICES_H
#define STATIC_MATRICES_H

#include <d3dx9math.h>

namespace constants
{
  namespace matrix
  {
    extern D3DXMATRIX const identity;

    // Natural CS:
    //   North - Y, East - X, Up - Z.
    extern D3DXMATRIX const naturalCS;
  } // End of namespace 'matrix'
} // End of namespace 'constants'

#endif // STATIC_MATRICES_H
