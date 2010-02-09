// application.h
// Main application class declaration.
// Vladimir Rutsky, 4057/2
// 09.02.2010

#ifndef APPLICATION_H
#define APPLICATION_H

#include "Library/cglApp.h"

class Application : public cglApp
{
public:
  Application( int windowWidth, int windowHeight, void* hInstance, int nCmdShow );
  virtual ~Application();

protected:
  char const * getWindowText();
  void renderInternal();
};

#endif // APPLICATION_H
