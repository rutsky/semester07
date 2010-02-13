// application.cpp
// Main application class definition.
// Vladimir Rutsky, 4057/2
// 09.02.2010

#include "precompiled.h"

#include <cassert>

#include <windows.h>

#include "application.h"
#include "Library/cglD3D.h"

#include "constants.h"

Application::Application( int windowWidth, int windowHeight, void* hInstance, int nCmdShow )
  : cglApp(windowWidth, windowHeight, hInstance, nCmdShow)  
  , m_windowWidth(windowWidth)
  , m_windowHeight(windowHeight)
  , m_device(m_pD3D->getDevice())
{
  // Updating caption first time.
  SetWindowText(HWND(m_hWnd), Application::getWindowText());
  m_nClearColor = 0;

  assert(m_device);

  // Root node.
  m_rootSceneNode.reset(new scene::RootNode);

  // Projection matrix.
  m_projectionMatrix.reset(new projection::PerspectiveProjection(constants::pi / 2.0, (double)windowWidth / windowHeight, 1.0, 10000.0));

  // Camera (view matrix).
  m_sphericCamera.reset(new camera::SphericCamera);
  m_sphericCamera->setSphericCoordinates(7, util::deg2rad(30), util::deg2rad(45));
  // Attaching camera to root node.
  m_rootSceneNode->addChildNode(scene::ISceneNodePtr(hierarchy::newSceneNode<scene::SimpleSceneNode>(m_sphericCamera.get())));

  {
    // Scene objects.

    m_coordinateSystem.reset(xobject::XCoordinateSystem::create(m_device));
    //m_rootSceneNode->addObject(m_coordinateSystem.get());

    m_triangle.reset(xobject::XTriangle::create(m_device));
    //m_triangle->setShow(false);

    m_mesh.reset(xobject::XMesh::create(m_device, "data", "Tiger.x"));
    //m_mesh->setShow(false);

    //m_surface.reset(xobject::xsurface::createPlane(m_device, 3, 4));
    //m_surface.reset(xobject::xsurface::createTorus(m_device, 1.5, 0.5, 100, 100, xobject::xsurface::color_generator::chessboard()));
    //typedef xobject::xsurface::color_generator::yuv colorspace_type;
    typedef xobject::xsurface::color_generator::chessboard colorspace_type;
    //typedef xobject::xsurface::color_generator::yuv colorspace_type;
    m_surface.reset(xobject::xsurface::createTorus(m_device, 1.5, 0.5, 100, 50, 
      xobject::xsurface::ScaleColorSpace<colorspace_type>(colorspace_type(), 1 / 10.0, 1 / 5.0)));
  }

  {
    // Scene hierarchy.

    if (1)
    {
      m_rootSceneNode->addObject(m_coordinateSystem.get());
    }

    if (0)
    {
      scene::ISceneNodePtr node;
      node = scene::ISceneNodePtr(hierarchy::newSceneNode<scene::SimpleSceneNode>(m_triangle.get()));
      m_rootSceneNode->addChildNode(node);
    }

    if (0)
    {
      scene::RotatingSceneNode *node = new scene::RotatingSceneNode(D3DXVECTOR3(1, 0, 0), 1.0);
      node->addObject(m_triangle.get());
      m_rootSceneNode->addChildNode(scene::ISceneNodePtr(node));
    }

    if (0)
    {
      scene::LCSArrowPgUpPgDownMoveSceneNode *node = new scene::LCSArrowPgUpPgDownMoveSceneNode;
      node->addObject(m_mesh.get());
      m_rootSceneNode->addChildNode(scene::ISceneNodePtr(node));
    }

    if (1)
    {
      scene::SimpleSceneNode *translationNode = new scene::SimpleSceneNode(D3DXVECTOR3(1, 3, 0));
      m_rootSceneNode->addChildNode(scene::ISceneNodePtr(translationNode));

      scene::LCSArrowPgUpPgDownRotateNode *rotatingNode = new scene::LCSArrowPgUpPgDownRotateNode;
      rotatingNode->addObject(m_surface.get());
      translationNode->addChildNode(scene::ISceneNodePtr(rotatingNode));
    }
  }
}

Application::~Application()
{
}

static bool processInputOnScene( scene::ISceneNodePtr node, unsigned int message, int wParam, long lParam )
{
  if (!node)
    return false;

  if (node->handleMessage(message, wParam, lParam))
    return true;

  for (size_t i = 0; i < node->objectsNum(); ++i)
    if (node->object(i)->handleMessage(message, wParam, lParam))
      return true;

  for (size_t i = 0; i < node->childNodesNum(); ++i)
    if (processInputOnScene(node->childNode(i), message, wParam, lParam))
      return true;

  return false;
}

static void updateScene( scene::ISceneNodePtr node, double time, D3DXMATRIX const *world = 0 )
{
  if (!node)
    return;

  D3DXMATRIX identity;
  D3DXMatrixIdentity(&identity);
  if (!world)
    world = &identity;

  node->updateWorldMatrix(world);
  node->update(time);

  for (size_t i = 0; i < node->objectsNum(); ++i)
  {
    node->object(i)->updateWorldMatrix(world);
    node->object(i)->update(time);
  }

  D3DXMATRIX const newWorld = node->matrix() * *world;

  for (size_t i = 0; i < node->childNodesNum(); ++i)
    updateScene(node->childNode(i), time, &newWorld);
}

static void drawScene( IDirect3DDevice9 *device, scene::ISceneNodePtr node, D3DXMATRIX const *world = 0 )
{
  if (!node)
    return;

  D3DXMATRIX newWorld;
  if (!world)
    newWorld = node->matrix();
  else
    newWorld = node->matrix() * *world;

  device->SetTransform(D3DTS_WORLD, &newWorld);
  if (node->show())
    node->draw();

  node->beginChildsDrawing(device);
  for (size_t i = 0; i < node->objectsNum(); ++i)
    if (node->object(i)->show())
      node->object(i)->draw();

  for (size_t i = 0; i < node->childNodesNum(); ++i)
    drawScene(device, node->childNode(i), &newWorld);
  node->endChildsDrawing(device);
}

void Application::update()
{
  cglApp::update();

  updateScene(m_rootSceneNode, m_timer.getTime());
}

void Application::renderInternal()
{
  //m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
  m_device->SetRenderState(D3DRS_LIGHTING, FALSE);
  //m_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

  //D3DXMATRIX identity;
  //D3DXMatrixIdentity(&identity);
  //m_device->SetTransform(D3DTS_WORLD, &initialWorld);
  
  m_device->SetTransform(D3DTS_VIEW, &m_sphericCamera->viewMatrix());
  m_device->SetTransform(D3DTS_PROJECTION, &m_projectionMatrix->projectionMatrix());

  /*
  D3DXVECTOR3 vEyePt( 0.0f, 3.0f,-5.0f );
  D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
  D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
  D3DXMATRIXA16 matView;
  D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
  m_device->SetTransform( D3DTS_VIEW, &matView );*/

  drawScene(m_device, m_rootSceneNode);

  //m_coordinateSystem->draw();
}

bool Application::processInput( unsigned int message, int wParam, long lParam )
{
  if (cglApp::processInput(message, wParam, lParam))
    return true;

  return processInputOnScene(m_rootSceneNode, message, wParam, lParam);
}

char const * Application::getWindowText()
{
  return "CG labs. Vladimir Rutsky, 4057/2, 2010    ";
}
