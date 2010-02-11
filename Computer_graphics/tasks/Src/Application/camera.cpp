// camera.cpp
// Camera description.
// Vladimir Rutsky, 4057/2
// 10.02.2010

#include "precompiled.h"

#include "camera.h"

namespace camera
{
  namespace lcs
  {
    D3DXMATRIX SphericCamera::evalViewMatrix( double r, double phi, double theta )
    {
      D3DXMATRIX translate;
      D3DXMatrixTranslation(&translate, 0, 0, (float)r);

      D3DXMATRIX yRot;
      D3DXMatrixRotationY(&yRot, (float)phi);

      D3DXMATRIX xRot;
      D3DXMatrixRotationX(&xRot, (float)theta);

      D3DXMATRIX axis(
         1,  0,  0,  0,
         0,  0,  1,  0,
         0,  1,  0,  0,
         0,  0,  0,  1);

      //return axis * translate * yRot * zRot;
      //return zRot * yRot * translate * axis;
      return axis * yRot * xRot * translate;
      //return yRot * xRot;
      //return translate;
    }
  } // End of namespace 'lcs'
} // End of namespace 'camera'
