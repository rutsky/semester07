// application.h
// Main application class declaration.
// Vladimir Rutsky, 4057/2
// 09.02.2010

#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>
#include <vector>

#include <d3d9.h>

#include "Library/cglApp.h"

#include "xobject.h"
#include "hierarchy.h"

class Application : public cglApp
{
public:
  Application( int windowWidth, int windowHeight, void* hInstance, int nCmdShow );
  ~Application();

protected:
  char const * getWindowText();
  void renderInternal();

private:
  IDirect3DDevice9 *m_device;

  hierarchy::SimpleSceneNode rootSceneNode;
  std::vector<hierarchy::ISceneNode *> sceneNodes;

  std::auto_ptr<xobject::XMesh> m_mesh;
  std::auto_ptr<xobject::XTriangle> m_triangle;
};

#endif // APPLICATION_H
