// application.h
// Main application class definition.
// Vladimir Rutsky, 4057/2
// 09.02.2010

#include "application.h"

#include <windows.h>

Application::Application( int windowWidth, int windowHeight, void* hInstance, int nCmdShow )
  : cglApp(windowWidth, windowHeight, hInstance, nCmdShow)  
{
  // Updating caption.
  SetWindowText(HWND(m_hWnd), Application::getWindowText());
}

Application::~Application()
{
}

char const * Application::getWindowText()
{
  return "CG labs. Vladimir Rutsky, 4057/2, 09.02.2010";
}
