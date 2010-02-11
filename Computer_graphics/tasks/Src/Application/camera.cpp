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
      D3DXMatrixTranslation(&translate, (float)-r, 0, 0);

      D3DXMATRIX yRot;
      D3DXMatrixRotationY(&yRot, (float)theta);

      D3DXMATRIX zRot;
      D3DXMatrixRotationZ(&zRot, (float)phi);

      /*
      D3DXMATRIX axis(
         0,  0,  1,  0,
        -1,  0,  0,  0,
         0,  1,  0,  0,
         0,  0,  0,  1);*/

      D3DXMATRIX axis(
         1,  0,  0,  0,
         0,  1,  0,  0,
         0,  0,  1,  0,
         0,  0,  0,  1);

      //return axis * translate * yRot * zRot;
      //return zRot * yRot * translate * axis;
      return axis;
    }
  } // End of namespace 'lcs'
} // End of namespace 'camera'
