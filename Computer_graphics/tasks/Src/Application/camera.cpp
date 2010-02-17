// camera.cpp
// Camera description.
// Vladimir Rutsky, 4057/2
// 10.02.2010

#include "precompiled.h"

#include "camera.h"

#include "static_matrices.h"

namespace camera
{
  namespace lcs
  {
    D3DXMATRIX SphericCamera::evalCameraMatrix( double r, double phi, double theta )
    {
      D3DXVECTOR3 const eyePosition = SphericCamera::eyePosition(r, phi, theta);

      D3DXMATRIX translate;
      D3DXMatrixTranslation(&translate, eyePosition[0], eyePosition[1], eyePosition[2]);

      D3DXMATRIX zRot;
      D3DXMatrixRotationZ(&zRot, (float)(phi + constants::pi / 2.0));

      D3DXMATRIX xRot;
      D3DXMatrixRotationX(&xRot, (float)(-theta));

      return constants::matrix::naturalCS * xRot * zRot * translate;
    }

    D3DXMATRIX FreeViewCamera::evalCameraMatrix( double phi, double theta )
    {
      D3DXMATRIX zRot;
      D3DXMatrixRotationZ(&zRot, (float)phi);

      D3DXMATRIX xRot;
      D3DXMatrixRotationX(&xRot, (float)theta);

      return constants::matrix::naturalCS * xRot * zRot;
    }
  } // End of namespace 'lcs'
} // End of namespace 'camera'
