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

  m_rootSceneNode.reset(new scene::SimpleSceneNode);

  m_projectionMatrix.reset(new projection::PerspectiveProjection(constants::pi / 2.0, windowWidth / windowHeight, 1.0, 10000.0));

  m_sphericCamera.reset(new camera::SphericCamera);
  m_rootSceneNode->addChildNode(scene::ISceneNodePtr(hierarchy::newSceneNode<scene::SimpleSceneNode>(m_sphericCamera.get())));

  m_coordinateSystem.reset(xobject::XCoordinateSystem::create(m_device));
  m_rootSceneNode->addObject(m_coordinateSystem.get());

  m_triangle.reset(xobject::XTriangle::create(m_device));
  m_triangle->setShow(false);

  m_mesh.reset(xobject::XMesh::create(m_device, "data", "Tiger.x"));

  /*
  scene::ISceneNodePtr node;

  node = scene::ISceneNodePtr(hierarchy::newSceneNode<scene::SimpleSceneNode>(m_triangle.get()));
  m_rootSceneNode->addChildNode(node);*/

  scene::RotatingSceneNode *rotatingNode = new scene::RotatingSceneNode(D3DXVECTOR3(0, 0, 1), 1.0);
  rotatingNode->addObject(m_triangle.get());
  m_rootSceneNode->addChildNode(scene::ISceneNodePtr(rotatingNode));

  scene::LCSArrowPgUpPgDownMoveSceneNode *arrowsControl = new scene::LCSArrowPgUpPgDownMoveSceneNode;
  arrowsControl->addObject(m_mesh.get());
  m_rootSceneNode->addChildNode(scene::ISceneNodePtr(arrowsControl));
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

  D3DXMATRIX const newWorld = *world * node->matrix();

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
    newWorld = *world * node->matrix();

  device->SetTransform(D3DTS_WORLD, &newWorld);
  if (node->show())
    node->draw();
  for (size_t i = 0; i < node->objectsNum(); ++i)
    if (node->object(i)->show())
      node->object(i)->draw();

  for (size_t i = 0; i < node->childNodesNum(); ++i)
    drawScene(device, node->childNode(i), &newWorld);
}

void Application::update()
{
  cglApp::update();

  updateScene(m_rootSceneNode, m_timer.getTime());
}

void Application::renderInternal()
{
  m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
  m_device->SetRenderState(D3DRS_LIGHTING, FALSE);

  D3DXMATRIX initialWorld;
  D3DXMatrixIdentity(&initialWorld);

  m_device->SetTransform(D3DTS_WORLD, &initialWorld);
  m_device->SetTransform(D3DTS_VIEW, &m_sphericCamera->viewMatrix());
  //m_device->SetTransform(D3DTS_PROJECTION, &m_projectionMatrix->projectionMatrix());
  drawScene(m_device, m_rootSceneNode);
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
