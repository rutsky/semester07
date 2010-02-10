// application.cpp
// Main application class definition.
// Vladimir Rutsky, 4057/2
// 09.02.2010

#include <cassert>

#include <windows.h>

#include "application.h"

#include "Library/cglD3D.h"

Application::Application( int windowWidth, int windowHeight, void* hInstance, int nCmdShow )
  : cglApp(windowWidth, windowHeight, hInstance, nCmdShow)  
  , m_device(m_pD3D->getDevice())
{
  // Updating caption first time.
  SetWindowText(HWND(m_hWnd), Application::getWindowText());
  m_nClearColor = 0;

  assert(m_device);

  m_triangle = std::auto_ptr<xobject::XTriangle>(xobject::XTriangle::create(m_device));
  m_mesh = std::auto_ptr<xobject::XMesh>(xobject::XMesh::create(m_device, "data", "Tiger.x"));
}

Application::~Application()
{
}

char const * Application::getWindowText()
{
  return "CG labs. Vladimir Rutsky, 4057/2, 09.02.2010    ";
}

void Application::renderInternal()
{
  /*
  D3DXMATRIX identity;
  D3DXMatrixIdentity(&identity);

  D3DXMATRIX world;
  D3DXMatrixTranslation(&world, 0, 0, 0);
  m_device->SetTransform(D3DTS_WORLD, &world);

  D3DXMATRIX view;
  //D3DXMatrixTranslation(&view, 0, 0, 0);
  D3DXMatrixRotationY(&view, 0.01 * m_timer.getTime());
  m_device->SetTransform(D3DTS_VIEW, &view);

  D3DXMATRIX projection;
  D3DXMatrixPerspectiveFovLH(&projection, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
  m_device->SetTransform(D3DTS_PROJECTION, &projection);
  */

  m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
  m_device->SetRenderState(D3DRS_LIGHTING, FALSE);

  /*
  D3DXMatrixTranslation(&world, 5, 5, 5);
  m_device->SetTransform(D3DTS_WORLD, &world);
  m_triangle->draw();

  D3DXMatrixTranslation(&world, -5, -5, -5);
  m_device->SetTransform(D3DTS_WORLD, &world);
  m_triangle->draw();

  D3DXMatrixTranslation(&world, 5, -5, -5);
  m_device->SetTransform(D3DTS_WORLD, &world);
  m_triangle->draw();

  D3DXMatrixTranslation(&world, -5, 5, -5);
  m_device->SetTransform(D3DTS_WORLD, &world);
  m_triangle->draw();

  D3DXMatrixTranslation(&world, -5, -5, 5);
  m_device->SetTransform(D3DTS_WORLD, &world);
  m_triangle->draw();*/

    // Part of DirectX tiger example.
      // Set up world matrix
    D3DXMATRIXA16 matWorld;
    D3DXMatrixRotationY( &matWorld, m_timer.getTime() );
    m_device->SetTransform( D3DTS_WORLD, &matWorld );

    // Set up our view matrix. A view matrix can be defined given an eye point,
    // a point to lookat, and a direction for which way is up. Here, we set the
    // eye five units back along the z-axis and up three units, look at the 
    // origin, and define "up" to be in the y-direction.
    D3DXVECTOR3 vEyePt( 0.0f, 3.0f,-5.0f );
    D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
    D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
    D3DXMATRIXA16 matView;
    D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
    m_device->SetTransform( D3DTS_VIEW, &matView );

    // For the projection matrix, we set up a perspective transform (which
    // transforms geometry from 3D view space to 2D viewport space, with
    // a perspective divide making objects smaller in the distance). To build
    // a perpsective transform, we need the field of view (1/4 pi is common),
    // the aspect ratio, and the near and far clipping planes (which define at
    // what distances geometry should be no longer be rendered).
    D3DXMATRIXA16 matProj;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f );
    m_device->SetTransform( D3DTS_PROJECTION, &matProj );

  m_mesh->draw();
}
