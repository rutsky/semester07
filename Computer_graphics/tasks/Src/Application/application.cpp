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
#include "light.h"
#include "xutil.h"

// DEBUG
bool const doingTask1 = false;
bool const doingTask2 = false;
bool const doingTask3 = false;
bool const doingTask4 = true;
bool const doingTask5 = false;

Application::Application( int windowWidth, int windowHeight, void* hInstance, int nCmdShow )
  : cglApp(windowWidth, windowHeight, hInstance, nCmdShow)  
  , m_windowWidth(windowWidth)
  , m_windowHeight(windowHeight)
  , m_device(m_pD3D->getDevice())
  , m_usingSphericCamera(true)
  , m_directionLightEnabled(true)
  , m_pointLightEnabled(true)
  , m_spotLightEnabled(true)
  , m_mipmapLODBias(0.0f)
{
  // Updating caption first time.
  SetWindowText(HWND(m_hWnd), Application::getWindowText());
  m_nClearColor = 0;

  assert(m_device);

  if (doingTask1)
  {
    // Task 1.

    // Root node.
    m_weakRootNode = new scene::RootNode;
    m_rootSceneNode.reset(m_weakRootNode);

    // Projection matrix.
    m_projectionMatrix.reset(new projection::PerspectiveProjection(constants::pi / 2.0, (double)windowWidth / windowHeight, 1.0, 10000.0));

    // Camera (view matrix).
    m_sphericCamera.reset(new camera::SphericCamera);
    m_sphericCamera->setSphericCoordinates(7, util::deg2rad(30), util::deg2rad(45));
    // Attaching camera to root node.
    m_rootSceneNode->addChildNode(scene::ISceneNodePtr(hierarchy::newSceneNode<scene::SimpleSceneNode>(m_sphericCamera.get())));

    // Coordinate system rendering object.
    m_coordinateSystem.reset(xobject::XCoordinateSystem::create(m_device));
    
    // Chessboard-colored torus.
    typedef xobject::xsurface::color_generator::chessboard colorspace_type;
    m_surface.reset(xobject::xsurface::createTorus(m_device, 1.5, 0.5, 100, 50, 
      xobject::xsurface::ScaleColorSpace<colorspace_type>(colorspace_type(), 1 / 10.0, 1 / 5.0)));

    // Adding CS to root node.
    m_rootSceneNode->addObject(m_coordinateSystem.get());

    // Adding translation node to root node.
    scene::SimpleSceneNode *translationNode = new scene::SimpleSceneNode(D3DXVECTOR3(1, 3, 0));
    m_rootSceneNode->addChildNode(scene::ISceneNodePtr(translationNode));

    // Adding keyboard-rotating node to translation node.
    scene::LCSArrowPgUpPgDownRotateNode *rotatingNode = new scene::LCSArrowPgUpPgDownRotateNode;
    translationNode->addChildNode(scene::ISceneNodePtr(rotatingNode));
    // Attaching surface to rotating node.
    rotatingNode->addObject(m_surface.get());
  }
  else if (doingTask2)
  {
    // Task 2.

    // Root node.
    m_weakRootNode = new scene::RootNode;
    m_rootSceneNode.reset(m_weakRootNode);

    // Projection matrix.
    m_projectionMatrix.reset(new projection::PerspectiveProjection(constants::pi / 2.0, (double)windowWidth / windowHeight, 1.0, 10000.0));

    // Spheric camera (view matrix).
    m_sphericCamera.reset(new camera::SphericCamera);
    m_sphericCamera->setSphericCoordinates(50, util::deg2rad(30), util::deg2rad(45));
    // Attaching camera to root node.
    m_rootSceneNode->addChildNode(scene::ISceneNodePtr(hierarchy::newSceneNode<scene::SimpleSceneNode>(m_sphericCamera.get())));

    // Free view camera (view matrix)
    m_freeViewCamera.reset(new camera::FreeViewCamera);
    m_freeViewCamera->lookAt(D3DXVECTOR3(10, 0, 0), D3DXVECTOR3(0, 0, 0));
    // Attaching camera to root node.
    m_rootSceneNode->addChildNode(scene::ISceneNodePtr(hierarchy::newSceneNode<scene::SimpleSceneNode>(m_freeViewCamera.get())));

    // Direction light (Sun).
    light::DirectionLight directionLight;
    directionLight.setDirection(D3DXVECTOR3(-0.3f, 0.0f, -1.0f));
    directionLight.setMaterial(constants::color::gray(0.5f), constants::color::gray(0.5f), constants::color::gray(0.5f));
    // Attaching light to root node.
    m_weakRootNode->addLight(0, directionLight.light());

    // Point light.
    light::PointLight pointLight;
    pointLight.setPosition(D3DXVECTOR3(30.0f, 0.0f, 6.0f));
    pointLight.setMaterial(constants::color::gray(0.7f), constants::color::gray(0.7f), constants::color::gray(0.7f));
    // Attaching light to root node.
    m_weakRootNode->addLight(1, pointLight.light());

    // Coordinate system object.
    m_coordinateSystem.reset(xobject::XCoordinateSystem::create(m_device));

    // Car model.
    m_mesh.reset(xobject::XMesh::create(m_device, "data", "car00.x", false));

    // Ground model.
    m_groundMesh.reset(xobject::XMesh::create(m_device, "data", "ground_paletted.x", false));


    // Adding coordinate system model to root.
    //m_rootSceneNode->addObject(m_coordinateSystem.get());
    
    // Scene hierarchy.

    // Attaching ground.
    scene::SimpleSceneNode *groundNode = new scene::SimpleSceneNode(D3DXMATRIX(
        1,  0,  0,  0,
        0,  0, -1,  0,
        0,  1,  0,  0,
        0,  0,  0,  1));
    groundNode->addObject(m_groundMesh.get());
    m_rootSceneNode->addChildNode(scene::ISceneNodePtr(groundNode));

    // Attaching car.
    m_rotatingNode = new scene::RotatingSceneNode(D3DXVECTOR3(0, 0, 1), 0.4);
    m_rootSceneNode->addChildNode(scene::ISceneNodePtr(m_rotatingNode));

    scene::SimpleSceneNode *translationNode = new scene::SimpleSceneNode(D3DXVECTOR3(0, 30.0f, 2.4f));
    m_rotatingNode->addChildNode(scene::ISceneNodePtr(translationNode));

    scene::LCSArrowPgUpPgDownRotateNode *keyboardRotatingNode = new scene::LCSArrowPgUpPgDownRotateNode;
    translationNode->addChildNode(scene::ISceneNodePtr(keyboardRotatingNode));

    scene::SimpleSceneNode *xmeshNode = new scene::SimpleSceneNode(D3DXMATRIX(
        1,  0,  0,  0,
        0,  0, -1,  0,
        0,  1,  0,  0,
        0,  0,  0,  1));
    xmeshNode->addObject(m_mesh.get());
    keyboardRotatingNode->addChildNode(scene::ISceneNodePtr(xmeshNode));

    // Attaching car light
    m_carLight = new scene::LightsNode;
    light::SpotLight spotLight;
    spotLight.setPosition(D3DXVECTOR3(-7.5f, 0.0f, 0.5f));
    spotLight.setDirection(D3DXVECTOR3(-1.0f, 0.0f, 0.0f));
    spotLight.setAngles((float)util::deg2rad(30), (float)util::deg2rad(50));
    pointLight.setMaterial(constants::color::gray(0.6f), constants::color::gray(0.6f), constants::color::gray(0.6f));
    m_carLight->addLight(2, spotLight.light());
    keyboardRotatingNode->addChildNode(scene::ISceneNodePtr(m_carLight));
  }
  else if (doingTask3)
  {
    // Task 3.

    // Root node.
    m_weakRootNode = new scene::RootNode;
    m_rootSceneNode.reset(m_weakRootNode);

    // Projection matrix.
    m_projectionMatrix.reset(new projection::PerspectiveProjection(constants::pi / 2.0, (double)windowWidth / windowHeight, 1.0, 10000.0));

    // Spheric camera (view matrix).
    m_sphericCamera.reset(new camera::SphericCamera);
    m_sphericCamera->setSphericCoordinates(50, util::deg2rad(30), util::deg2rad(45));
    // Attaching camera to root node.
    m_rootSceneNode->addChildNode(scene::ISceneNodePtr(hierarchy::newSceneNode<scene::SimpleSceneNode>(m_sphericCamera.get())));

    // Free view camera (view matrix)
    m_freeViewCamera.reset(new camera::FreeViewCamera);
    m_freeViewCamera->lookAt(D3DXVECTOR3(10, 0, 0), D3DXVECTOR3(0, 0, 0));
    // Attaching camera to root node.
    m_rootSceneNode->addChildNode(scene::ISceneNodePtr(hierarchy::newSceneNode<scene::SimpleSceneNode>(m_freeViewCamera.get())));

    // Direction light (Sun).
    light::DirectionLight directionLight;
    directionLight.setDirection(D3DXVECTOR3(-0.3f, 0.0f, -1.0f));
    directionLight.setMaterial(constants::color::gray(0.5f), constants::color::gray(0.5f), constants::color::gray(0.5f));
    // Attaching light to root node.
    m_weakRootNode->addLight(0, directionLight.light());

    // Point light.
    light::PointLight pointLight;
    pointLight.setPosition(D3DXVECTOR3(30.0f, 0.0f, 6.0f));
    pointLight.setMaterial(constants::color::gray(0.7f), constants::color::gray(0.7f), constants::color::gray(0.7f));
    // Attaching light to root node.
    m_weakRootNode->addLight(1, pointLight.light());

    // Coordinate system object.
    m_coordinateSystem.reset(xobject::XCoordinateSystem::create(m_device));

    // Car model.
    char *mipmaps[] = { "1.png", "2.png", "3.png", "4.png" };
    m_mesh.reset(xobject::XMesh::createWithCustomTextures(m_device, "data", /*"car00.x"*/ "airplane00.x", 256, 256, D3DFMT_X8R8G8B8, 
      &(mipmaps[0]), &(mipmaps[util::array_size(mipmaps)])));

    // Ground model.
    m_groundMesh.reset(xobject::XMesh::create(m_device, "data", "ground_paletted.x"));

    // Adding coordinate system model to root.
    //m_rootSceneNode->addObject(m_coordinateSystem.get());
    
    // Scene hierarchy.

    // Attaching ground.
    scene::SimpleSceneNode *groundNode = new scene::SimpleSceneNode(D3DXMATRIX(
        1,  0,  0,  0,
        0,  0, -1,  0,
        0,  1,  0,  0,
        0,  0,  0,  1));
    groundNode->addObject(m_groundMesh.get());
    m_rootSceneNode->addChildNode(scene::ISceneNodePtr(groundNode));

    // Attaching car.
    m_rotatingNode = new scene::RotatingSceneNode(D3DXVECTOR3(0, 0, 1), 0.4);
    m_rootSceneNode->addChildNode(scene::ISceneNodePtr(m_rotatingNode));

    scene::SimpleSceneNode *translationNode = new scene::SimpleSceneNode(D3DXVECTOR3(0, 30.0f, 2.4f));
    m_rotatingNode->addChildNode(scene::ISceneNodePtr(translationNode));

    scene::LCSArrowPgUpPgDownRotateNode *keyboardRotatingNode = new scene::LCSArrowPgUpPgDownRotateNode;
    translationNode->addChildNode(scene::ISceneNodePtr(keyboardRotatingNode));

    scene::TextureTransformNode *textureTransformNode = new scene::TextureTransformNode(D3DXMATRIX(
        20,  0,  0,  0,
        0,  20,  0,  0,
        0,   0,  1,  0,
        0,   0,  0,  1));
    keyboardRotatingNode->addChildNode(scene::ISceneNodePtr(textureTransformNode));

    scene::SimpleSceneNode *xmeshNode = new scene::SimpleSceneNode(D3DXMATRIX(
        0,  1,  0,  0,
        0,  0,  1,  0,
       -1,  0,  0,  0,
        0,  0,  0,  (float)(1.0 / 5.0)));
    xmeshNode->addObject(m_mesh.get());
    textureTransformNode->addChildNode(scene::ISceneNodePtr(xmeshNode));

    // Attaching car light
    m_carLight = new scene::LightsNode;
    light::SpotLight spotLight;
    spotLight.setPosition(D3DXVECTOR3(-7.5f, 0.0f, 0.5f));
    spotLight.setDirection(D3DXVECTOR3(-1.0f, 0.0f, 0.0f));
    spotLight.setAngles((float)util::deg2rad(30), (float)util::deg2rad(50));
    pointLight.setMaterial(constants::color::gray(0.6f), constants::color::gray(0.6f), constants::color::gray(0.6f));
    m_carLight->addLight(2, spotLight.light());
    textureTransformNode->addChildNode(scene::ISceneNodePtr(m_carLight));
  }
  else if (doingTask4)
  {
    // Task 4.

    // Root node.
    m_weakRootNode = new scene::RootNode;
    m_rootSceneNode.reset(m_weakRootNode);

    // Projection matrix.
    m_projectionMatrix.reset(new projection::PerspectiveProjection(constants::pi / 2.0, (double)windowWidth / windowHeight, 1.0, 10000.0));

    // Spheric camera (view matrix).
    m_sphericCamera.reset(new camera::SphericCamera);
    m_sphericCamera->setSphericCoordinates(12, util::deg2rad(30), util::deg2rad(45));
    // Attaching camera to root node.
    m_rootSceneNode->addChildNode(scene::ISceneNodePtr(hierarchy::newSceneNode<scene::SimpleSceneNode>(m_sphericCamera.get())));

    // Free view camera (view matrix)
    m_freeViewCamera.reset(new camera::FreeViewCamera);
    m_freeViewCamera->lookAt(D3DXVECTOR3(10, 0, 0), D3DXVECTOR3(0, 0, 0));
    // Attaching camera to root node.
    m_rootSceneNode->addChildNode(scene::ISceneNodePtr(hierarchy::newSceneNode<scene::SimpleSceneNode>(m_freeViewCamera.get())));

    // Direction light (Sun).
    light::DirectionLight directionLight;
    directionLight.setDirection(D3DXVECTOR3(-0.3f, 0.0f, -1.0f));
    directionLight.setMaterial(constants::color::gray(0.5f), constants::color::gray(0.5f), constants::color::gray(0.5f));
    // Attaching light to root node.
    m_weakRootNode->addLight(0, directionLight.light());

    // Coordinate system object.
    m_coordinateSystem.reset(xobject::XCoordinateSystem::create(m_device));

    // Adding coordinate system model to root.
    m_rootSceneNode->addObject(m_coordinateSystem.get());
    
    // Scene hierarchy.

    double const trunkR = 0.1, lowerCupR = 0.6, middleCupR = 0.9, topCupR = 0.7;
    double const trunkHeight = 2.0, cupBottomHeight = 0.1;
    double const cupLowerLen = 0.7, cupUpperLen = 0.6;

    scene::SimpleSceneNode *translation1Node = new scene::SimpleSceneNode(D3DXVECTOR3(1, 3, 0));
    //translation1Node->addObject(m_coordinateSystem.get());
    m_rootSceneNode->addChildNode(scene::ISceneNodePtr(translation1Node));
    
    scene::RotatingSceneNode *rotation1Node = new scene::RotatingSceneNode(D3DXVECTOR3(0, 0, 1), 0.1);
    translation1Node->addChildNode(scene::ISceneNodePtr(rotation1Node));

    m_trunk.reset(xobject::XMesh::createCylinder(m_device, trunkR, trunkR, trunkHeight, 20, 20, 
      xutil::material(constants::color::green() * 0.5f, constants::color::green() * 0.1f)));

    scene::SimpleSceneNode *translation2Node = new scene::SimpleSceneNode(D3DXVECTOR3(0, 0, (float)(trunkHeight / 2.0)));
    translation2Node->addObject(m_trunk.get());
    //translation2Node->addObject(m_coordinateSystem.get());
    rotation1Node->addChildNode(scene::ISceneNodePtr(translation2Node));

    m_cup.reset(xobject::XMesh::createCylinder(m_device, lowerCupR, lowerCupR, cupBottomHeight, 20, 1, 
      xutil::material(constants::color::green() * 0.5f, constants::color::green() * 0.1f)));

    scene::SimpleSceneNode *translation3Node = new scene::SimpleSceneNode(D3DXVECTOR3(0, 0, (float)(trunkHeight / 2.0)));
    translation3Node->addObject(m_cup.get());
    //translation2Node->addObject(m_coordinateSystem.get());
    translation2Node->addChildNode(scene::ISceneNodePtr(translation3Node));

    // Attaching ground.
    /*
    scene::SimpleSceneNode *groundNode = new scene::SimpleSceneNode(D3DXMATRIX(
        1,  0,  0,  0,
        0,  0, -1,  0,
        0,  1,  0,  0,
        0,  0,  0,  1));
    groundNode->addObject(m_groundMesh.get());
    m_rootSceneNode->addChildNode(scene::ISceneNodePtr(groundNode));

    // Attaching car.
    m_rotatingNode = new scene::RotatingSceneNode(D3DXVECTOR3(0, 0, 1), 0.4);
    m_rootSceneNode->addChildNode(scene::ISceneNodePtr(m_rotatingNode));

    scene::SimpleSceneNode *translationNode = new scene::SimpleSceneNode(D3DXVECTOR3(0, 30.0f, 2.4f));
    m_rotatingNode->addChildNode(scene::ISceneNodePtr(translationNode));

    scene::LCSArrowPgUpPgDownRotateNode *keyboardRotatingNode = new scene::LCSArrowPgUpPgDownRotateNode;
    translationNode->addChildNode(scene::ISceneNodePtr(keyboardRotatingNode));

    scene::TextureTransformNode *textureTransformNode = new scene::TextureTransformNode(D3DXMATRIX(
        20,  0,  0,  0,
        0,  20,  0,  0,
        0,   0,  1,  0,
        0,   0,  0,  1));
    keyboardRotatingNode->addChildNode(scene::ISceneNodePtr(textureTransformNode));

    scene::SimpleSceneNode *xmeshNode = new scene::SimpleSceneNode(D3DXMATRIX(
        0,  1,  0,  0,
        0,  0,  1,  0,
       -1,  0,  0,  0,
        0,  0,  0,  (float)(1.0 / 5.0)));
    xmeshNode->addObject(m_mesh.get());
    textureTransformNode->addChildNode(scene::ISceneNodePtr(xmeshNode));

    // Attaching car light
    m_carLight = new scene::LightsNode;
    light::SpotLight spotLight;
    spotLight.setPosition(D3DXVECTOR3(-7.5f, 0.0f, 0.5f));
    spotLight.setDirection(D3DXVECTOR3(-1.0f, 0.0f, 0.0f));
    spotLight.setAngles((float)util::deg2rad(30), (float)util::deg2rad(50));
    pointLight.setMaterial(constants::color::gray(0.6f), constants::color::gray(0.6f), constants::color::gray(0.6f));
    m_carLight->addLight(2, spotLight.light());
    textureTransformNode->addChildNode(scene::ISceneNodePtr(m_carLight));
    */
  }
  else if (1)
  {
    // Debug
    // Root node.
    m_weakRootNode = new scene::RootNode;
    m_rootSceneNode.reset(m_weakRootNode);

    // Projection matrix.
    m_projectionMatrix.reset(new projection::PerspectiveProjection(constants::pi / 2.0, (double)windowWidth / windowHeight, 1.0, 10000.0));

    // Camera (view matrix).
    m_sphericCamera.reset(new camera::SphericCamera);
    m_sphericCamera->setSphericCoordinates(50, util::deg2rad(30), util::deg2rad(45));
    // Attaching camera to root node.
    m_rootSceneNode->addChildNode(scene::ISceneNodePtr(hierarchy::newSceneNode<scene::SimpleSceneNode>(m_sphericCamera.get())));

    m_freeViewCamera.reset(new camera::FreeViewCamera);
    m_freeViewCamera->lookAt(D3DXVECTOR3(10, 0, 0), D3DXVECTOR3(0, 0, 0));
    
    // Attaching camera to root node.
    m_rootSceneNode->addChildNode(scene::ISceneNodePtr(hierarchy::newSceneNode<scene::SimpleSceneNode>(m_freeViewCamera.get())));

    light::DirectionLight directionLight;
    directionLight.setDirection(D3DXVECTOR3(-0.3f, 0.0f, -1.0f));
    directionLight.setMaterial(constants::color::gray(0.5f), constants::color::gray(0.5f), constants::color::gray(0.5f));
    m_weakRootNode->addLight(0, directionLight.light());

    light::PointLight pointLight;
    pointLight.setPosition(D3DXVECTOR3(30.0f, 0.0f, 6.0f));
    pointLight.setMaterial(constants::color::gray(0.7f), constants::color::gray(0.7f), constants::color::gray(0.7f));
    m_weakRootNode->addLight(1, pointLight.light());

    {
      // Scene objects.

      m_coordinateSystem.reset(xobject::XCoordinateSystem::create(m_device));
      //m_rootSceneNode->addObject(m_coordinateSystem.get());

      m_triangle.reset(xobject::XTriangle::create(m_device));
      //m_triangle->setShow(false);

      m_mesh.reset(xobject::XMesh::create(m_device, "data", "car00.x", false));
      //m_mesh.reset(xobject::XMesh::create(m_device, "data", "tiger.x"));
      //m_mesh->setShow(false);

      m_groundMesh.reset(xobject::XMesh::create(m_device, "data", "ground_paletted.x", false));

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
        scene::RotatingSceneNode *rotatingNode = new scene::RotatingSceneNode(D3DXVECTOR3(0, 0, 1), 0.4);
        m_rootSceneNode->addChildNode(scene::ISceneNodePtr(rotatingNode));

        scene::SimpleSceneNode *translationNode = new scene::SimpleSceneNode(D3DXVECTOR3(0, 30.0f, 2.4f));
        rotatingNode->addChildNode(scene::ISceneNodePtr(translationNode));

        scene::SimpleSceneNode *groundNode = new scene::SimpleSceneNode(D3DXMATRIX(
            1,  0,  0,  0,
            0,  0, -1,  0,
            0,  1,  0,  0,
            0,  0,  0,  1));
        groundNode->addObject(m_groundMesh.get());
        m_rootSceneNode->addChildNode(scene::ISceneNodePtr(groundNode));

        scene::LCSArrowPgUpPgDownRotateNode *keyboardRotatingNode = new scene::LCSArrowPgUpPgDownRotateNode;
        translationNode->addChildNode(scene::ISceneNodePtr(keyboardRotatingNode));

        scene::SimpleSceneNode *xmeshNode = new scene::SimpleSceneNode(D3DXMATRIX(
            1,  0,  0,  0,
            0,  0, -1,  0,
            0,  1,  0,  0,
            0,  0,  0,  1));
        xmeshNode->addObject(m_mesh.get());
        keyboardRotatingNode->addChildNode(scene::ISceneNodePtr(xmeshNode));

        m_carLight = new scene::LightsNode;
        light::SpotLight spotLight;
        spotLight.setPosition(D3DXVECTOR3(-5.0f, 0.0f, 3.5f));
        spotLight.setDirection(D3DXVECTOR3(-1.0f, 0.0f, 0.0f));
        spotLight.setAngles((float)util::deg2rad(30), (float)util::deg2rad(50));
        pointLight.setMaterial(constants::color::gray(0.6f), constants::color::gray(0.6f), constants::color::gray(0.6f));
        m_carLight->addLight(2, spotLight.light());
        keyboardRotatingNode->addChildNode(scene::ISceneNodePtr(m_carLight));
      }
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
    assert(node->object(i));
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
  if (doingTask1)
  {
    // Task 1.

    // Disabling lighting.
    m_device->SetRenderState(D3DRS_LIGHTING, FALSE);

    // Setting view matrix.
    m_device->SetTransform(D3DTS_VIEW, &m_sphericCamera->viewMatrix());

    // Setting projection matrix.
    m_device->SetTransform(D3DTS_PROJECTION, &m_projectionMatrix->projectionMatrix());

    // Drawing scene.
    drawScene(m_device, m_rootSceneNode);
  }
  else if (doingTask2)
  {
    // Task 2.

    if (m_usingSphericCamera)
      m_device->SetTransform(D3DTS_VIEW, &m_sphericCamera->viewMatrix());
    else
      m_device->SetTransform(D3DTS_VIEW, &m_freeViewCamera->viewMatrix());

    m_device->SetTransform(D3DTS_PROJECTION, &m_projectionMatrix->projectionMatrix());

    m_device->SetRenderState(D3DRS_COLORVERTEX, TRUE);
    m_device->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);
    m_device->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
    m_device->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_MATERIAL);

    drawScene(m_device, m_rootSceneNode);
  }
  else if (doingTask3)
  {
    // Task 3.

    if (m_usingSphericCamera)
      m_device->SetTransform(D3DTS_VIEW, &m_sphericCamera->viewMatrix());
    else
      m_device->SetTransform(D3DTS_VIEW, &m_freeViewCamera->viewMatrix());

    m_device->SetTransform(D3DTS_PROJECTION, &m_projectionMatrix->projectionMatrix());

    m_device->SetRenderState(D3DRS_COLORVERTEX, TRUE);
    m_device->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);
    m_device->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
    m_device->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_MATERIAL);

    m_device->SetSamplerState(0, D3DSAMP_MIPMAPLODBIAS, *((DWORD *)(&m_mipmapLODBias)));

    drawScene(m_device, m_rootSceneNode);
  }
  else if (doingTask4)
  {
    // Task 4.

    if (m_usingSphericCamera)
      m_device->SetTransform(D3DTS_VIEW, &m_sphericCamera->viewMatrix());
    else
      m_device->SetTransform(D3DTS_VIEW, &m_freeViewCamera->viewMatrix());

    m_device->SetTransform(D3DTS_PROJECTION, &m_projectionMatrix->projectionMatrix());

    m_device->SetRenderState(D3DRS_COLORVERTEX, TRUE);
    m_device->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);
    m_device->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
    m_device->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_MATERIAL);

    drawScene(m_device, m_rootSceneNode);
  }
  else if (1)
  {
    // Debug

    //m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    //m_device->SetRenderState(D3DRS_LIGHTING, FALSE);
    //m_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

    //D3DXMATRIX identity;
    //D3DXMatrixIdentity(&identity);
    //m_device->SetTransform(D3DTS_WORLD, &initialWorld);
    
    if (m_usingSphericCamera)
      m_device->SetTransform(D3DTS_VIEW, &m_sphericCamera->viewMatrix());
    else
      m_device->SetTransform(D3DTS_VIEW, &m_freeViewCamera->viewMatrix());

    m_device->SetTransform(D3DTS_PROJECTION, &m_projectionMatrix->projectionMatrix());

    m_device->SetRenderState(D3DRS_COLORVERTEX, TRUE);
    m_device->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);
    m_device->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
    m_device->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_MATERIAL);


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
}

bool Application::processInput( unsigned int message, int wParam, long lParam )
{
  if (cglApp::processInput(message, wParam, lParam))
    return true;

  if (doingTask1)
  {
  }
  else if (doingTask2)
  {
    if (message == WM_KEYDOWN)
    {
      if (wParam == VK_F1)
      {
        // FIXME: Not using world matrix information.
        if (m_usingSphericCamera)
          m_freeViewCamera->lookAt(m_sphericCamera->eyePosition(), D3DXVECTOR3(0, 0, 0));
        else
          m_sphericCamera->setEyePosition(m_freeViewCamera->eyePosition());
       
        m_usingSphericCamera = !m_usingSphericCamera;
      }
      else if (wParam == '1')
      {
        m_directionLightEnabled = !m_directionLightEnabled;
        m_weakRootNode->enableLight(0, m_directionLightEnabled);
      }
      else if (wParam == '2')
      {
        m_pointLightEnabled = !m_pointLightEnabled;
        m_weakRootNode->enableLight(1, m_pointLightEnabled);
      }
      else if (wParam == '3')
      {
        m_spotLightEnabled = !m_spotLightEnabled;
        m_carLight->enableLight(2, m_spotLightEnabled);
      }
      else if (wParam == VK_SPACE)
      {
        m_rotatingNode->pause(!m_rotatingNode->isPaused());
      }
    }
  }
  else if (doingTask3)
  {
    if (message == WM_KEYDOWN)
    {
      if (wParam == VK_F1)
      {
        // FIXME: Not using world matrix information.
        if (m_usingSphericCamera)
          m_freeViewCamera->lookAt(m_sphericCamera->eyePosition(), D3DXVECTOR3(0, 0, 0));
        else
          m_sphericCamera->setEyePosition(m_freeViewCamera->eyePosition());
       
        m_usingSphericCamera = !m_usingSphericCamera;
      }
      else if (wParam == '1')
      {
        m_directionLightEnabled = !m_directionLightEnabled;
        m_weakRootNode->enableLight(0, m_directionLightEnabled);
      }
      else if (wParam == '2')
      {
        m_pointLightEnabled = !m_pointLightEnabled;
        m_weakRootNode->enableLight(1, m_pointLightEnabled);
      }
      else if (wParam == '3')
      {
        m_spotLightEnabled = !m_spotLightEnabled;
        m_carLight->enableLight(2, m_spotLightEnabled);
      }
      else if (wParam == VK_SPACE)
      {
        m_rotatingNode->pause(!m_rotatingNode->isPaused());
      }
      else if (wParam == VK_ADD || wParam == VK_OEM_PLUS)
      {
        m_mipmapLODBias += 0.2f;
      }
      else if (wParam == VK_SUBTRACT || wParam == VK_OEM_MINUS)
      {
        m_mipmapLODBias -= 0.2f;
      }
    }
  }
  else if (doingTask4)
  {
    if (message == WM_KEYDOWN)
    {
      if (wParam == VK_F1)
      {
        // FIXME: Not using world matrix information.
        if (m_usingSphericCamera)
          m_freeViewCamera->lookAt(m_sphericCamera->eyePosition(), D3DXVECTOR3(0, 0, 0));
        else
          m_sphericCamera->setEyePosition(m_freeViewCamera->eyePosition());
       
        m_usingSphericCamera = !m_usingSphericCamera;
      }
    }
  }
  else if (1)
  {
    // Debug
  }

  return processInputOnScene(m_rootSceneNode, message, wParam, lParam);
}

char const * Application::getWindowText()
{
  return "CG labs. Vladimir Rutsky, 4057/2, 2010    ";
}
