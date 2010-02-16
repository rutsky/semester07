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
    D3DXMATRIX SphericCamera::evalCameraMatrix( double r, double phi, double theta )
    {
      D3DXMATRIX translate;
      D3DXMatrixTranslation(&translate, (float)(r * cos(phi) * cos(theta)), (float)(r * sin(phi) * cos(theta)), (float)(r * sin(theta)));

      D3DXMATRIX zRot;
      D3DXMatrixRotationZ(&zRot, (float)(phi + constants::pi / 2.0));

      D3DXMATRIX xRot;
      D3DXMatrixRotationX(&xRot, (float)(-theta));

      // Natural CS:
      //   North - Y, East - X, Up - Z.
      D3DXMATRIX axis(
         1,  0,  0,  0,
         0,  0,  1,  0,
         0,  1,  0,  0,
         0,  0,  0,  1);
      
      // DirectX camera CS:
      //   North - Z, East - X, Up - Y.
      /*
      D3DXMATRIX axis(
         1,  0,  0,  0,
         0,  1,  0,  0,
         0,  0,  1,  0,
         0,  0,  0,  1);*/
         
      return axis * xRot * zRot * translate;
    }

    D3DXMATRIX FreeViewCamera::evalCameraMatrix( double phi, double theta )
    {
      D3DXMATRIX zRot;
      D3DXMatrixRotationZ(&zRot, (float)phi);

      D3DXMATRIX xRot;
      D3DXMatrixRotationX(&xRot, (float)theta);

      // Natural CS:
      //   North - Y, East - X, Up - Z.
      D3DXMATRIX axis(
         1,  0,  0,  0,
         0,  0,  1,  0,
         0,  1,  0,  0,
         0,  0,  0,  1);

      return axis * xRot * zRot;
    }
  } // End of namespace 'lcs'
} // End of namespace 'camera'
