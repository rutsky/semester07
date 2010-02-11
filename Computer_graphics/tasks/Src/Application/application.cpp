// application.cpp
// Main application class definition.
// Vladimir Rutsky, 4057/2
// 09.02.2010

#include "precompiled.h"

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

  //m_rootSceneNode = scene::ISceneNodePtr(new scene::SimpleSceneNode);

  /*
  boost::shared_ptr<xobject::XTriangle> sp;
  
  m_triangle = std::auto_ptr<xobject::XTriangle>(xobject::XTriangle::create(m_device));
  m_mesh = std::auto_ptr<xobject::XMesh>(xobject::XMesh::create(m_device, "data", "Tiger.x"));

  sceneNodes.push_back(hierarchy::newSceneNode<hierarchy::SimpleSceneNode>(m_triangle.get()));
  rootSceneNode.addChildNode(sceneNodes.back());

  sceneNodes.push_back(hierarchy::newSceneNode<hierarchy::SimpleSceneNode>(m_mesh.get()));
  rootSceneNode.addChildNode(sceneNodes.back());

  hierarchy::RotatingSceneNode *rotatingNode = new hierarchy::RotatingSceneNode(D3DXVECTOR3(0, 0, 1), 1.0);
  rotatingNode->setObject(m_triangle.get());
  sceneNodes.push_back(rotatingNode);
  rootSceneNode.addChildNode(rotatingNode);

  hierarchy::LCSArrowPgUpPgDownMoveSceneNode *arrowsControl = new hierarchy::LCSArrowPgUpPgDownMoveSceneNode;
  arrowsControl->setObject(m_mesh.get());
  controls.push_back(arrowsControl);
  rootSceneNode.addChildNode(arrowsControl);*/
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

  if (node->object())
    if (node->object()->handleMessage(message, wParam, lParam))
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

  node->update(world);
  node->update(time);

  if (node->object())
  {
    node->object()->update(world);
    node->object()->update(time);
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

  if (node->object())
  {
    device->SetTransform(D3DTS_WORLD, &newWorld);
    node->object()->draw();
  }

  for (size_t i = 0; i < node->childNodesNum(); ++i)
    drawScene(device, node->childNode(i), &newWorld);
}

void Application::update()
{
  cglApp::update();

  //updateScene(m_rootSceneNode, m_timer.getTime());
}

void Application::renderInternal()
{
  //m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
  //m_device->SetRenderState(D3DRS_LIGHTING, FALSE);

  //drawScene(m_device, m_rootSceneNode);
}

bool Application::processInput( unsigned int message, int wParam, long lParam )
{
  //return processInputOnScene(m_rootSceneNode, message, wParam, lParam);
  return false;
}

char const * Application::getWindowText()
{
  return "CG labs. Vladimir Rutsky, 4057/2, 2010    ";
}
