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
#include "camera.h"
#include "camera_projection.h"

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
  int m_windowWidth, m_windowHeight;

  IDirect3DDevice9 *m_device;

  scene::ISceneNodePtr m_rootSceneNode;
  boost::shared_ptr<projection::IProjectionMatrix> m_projectionMatrix;
  boost::shared_ptr<camera::SphericCamera> m_sphericCamera;

  boost::shared_ptr<xobject::XMesh> m_mesh;
  boost::shared_ptr<xobject::XTriangle> m_triangle;
  boost::shared_ptr<xobject::XCoordinateSystem> m_coordinateSystem;
  boost::shared_ptr<xobject::xsurface::XSurface> m_surface;
};

#endif // APPLICATION_H
