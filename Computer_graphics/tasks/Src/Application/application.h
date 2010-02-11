// application.h
// Main application class declaration.
// Vladimir Rutsky, 4057/2
// 09.02.2010

#ifndef APPLICATION_H
#define APPLICATION_H

#include <vector>

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>

#include <d3d9.h>

#include "Library/cglApp.h"

#include "xobject.h"
#include "scene.h"

class Application : public cglApp
{
public:
  Application( int windowWidth, int windowHeight, void* hInstance, int nCmdShow );
  ~Application();

public:
  bool processInput( unsigned int message, int wParam, long lParam );

protected:
  char const * getWindowText();
  void renderInternal();
  void update();

private:
  IDirect3DDevice9 *m_device;

  scene::ISceneNodePtr m_rootSceneNode;

  boost::shared_ptr<xobject::XMesh> m_mesh;
  boost::shared_ptr<xobject::XTriangle> m_triangle;
};

#endif // APPLICATION_H
