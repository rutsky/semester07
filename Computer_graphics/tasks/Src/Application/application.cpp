// application.h
// Main application class definition.
// Vladimir Rutsky, 4057/2
// 09.02.2010

#include "application.h"

Application::Application( int windowWidth, int windowHeight, void* hInstance, int nCmdShow )
  : cglApp(windowWidth, windowHeight, hInstance, nCmdShow)  
{
}

Application::~Application()
{
}
