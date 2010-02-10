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

  xobject::XTriangle *triangle = xobject::XTriangle::create(m_device);
  if (triangle)
    m_triangle = std::auto_ptr<xobject::XTriangle>(triangle);
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
  m_triangle->draw();
}
