/**
  @file     myApp.cpp
  @brief    User's application class
  @date     Created on 10/09/2005
  @project  D3DBase
  @author   Bvs
*/

// *******************************************************************
// includes

#include <math.h>
#include <stdlib.h>
#include <windows.h>
#include <windowsx.h>
#include <zmouse.h>

#include "myapp.h"

// *******************************************************************
// defines

namespace
{

const float s_rMouseMove2Rotate = 0.001f;
const float s_rMouseWheel2Zoom = 0.001f;
const float s_rKbd2Rotate = 1.16f;
const float s_rKbd2Zoom = 1.16f;

void shiftColor(unsigned &color, float delta, int shift)
{
  int nComp = (color >> shift) & 0xFF;
  nComp += int(delta * 255.0f);
  if (nComp > 0xFF) 
    nComp = 0xFF;
  else if (nComp < 0)
    nComp = 0;
  color &= ~(0xFF << shift);
  color |= nComp << shift;
}

}

// *******************************************************************
// Methods

bool myApp::processInput(unsigned int nMsg, int wParam, long lParam)
{
  // Handle input
  switch (nMsg)
  {
    // Process mouse move message
    case WM_MOUSEMOVE:
    {
      // Get mouse x & y (to the upper-left corner of the client area)
      int xPos = GET_X_LPARAM(lParam); 
      int yPos = GET_Y_LPARAM(lParam); 

      if ((wParam & MK_LBUTTON) != 0 && m_nPrevMouseX >= 0) // 
      {
        rotate(s_rMouseMove2Rotate*(xPos-m_nPrevMouseX), 
               s_rMouseMove2Rotate*(yPos-m_nPrevMouseY));
      }
      
      m_nPrevMouseX = xPos;
      m_nPrevMouseY = yPos;
      break;
    }
    
    // Process mouse wheel message
    case WM_MOUSEWHEEL:
    {
      int zDelta = (int)((signed short)(HIWORD(wParam)));
      zoom(zDelta * s_rMouseWheel2Zoom);
      break;
    }
    
    case WM_KEYDOWN:
    {
      // Save flags for continuous controls
      if (wParam < MAX_KEYS)
        m_keysPressed[wParam] = true;
      break;
    }

    case WM_KEYUP:
    {
      // Save flags for continuous controls
      if (wParam < MAX_KEYS)
        m_keysPressed[wParam] = false;
      // Process switch controls
      switch (wParam)
      {
        case '1': /* do something */ break;
        case '2': /* do something */ break;
        case '3': /* do something */ break;
      }
      break;
    }
  }
  
  return cglApp::processInput(nMsg, wParam, lParam);
}

void myApp::rotate(float dx, float dy)
{
  shiftColor(m_nClearColor, dx, 16); // Red
  shiftColor(m_nClearColor, dy, 8); // Green
}

void myApp::zoom(float dr)
{
  shiftColor(m_nClearColor, dr, 0); // Blue
}

char const *myApp::getWindowText()
{
  return "Task 1.2, Vladimir Rutsky, 4057/2.";
}

void myApp::update()
{
  // Call predecessor update
  cglApp::update();
  
  // Process keyboard
  float dx = 0.0f;
  float dy = 0.0f;
  float dr = 0.0f;
  if (m_keysPressed[VK_LEFT])   
    dx -= s_rKbd2Rotate * m_timer.getDelta();
  if (m_keysPressed[VK_RIGHT])   
    dx += s_rKbd2Rotate * m_timer.getDelta();
  if (m_keysPressed[VK_UP])   
    dy -= s_rKbd2Rotate * m_timer.getDelta();
  if (m_keysPressed[VK_DOWN])   
    dy += s_rKbd2Rotate * m_timer.getDelta();
  if (m_keysPressed[VK_SUBTRACT])   
    dr -= s_rKbd2Zoom * m_timer.getDelta();
  if (m_keysPressed[VK_ADD])   
    dr += s_rKbd2Zoom * m_timer.getDelta();
  
  rotate(dx, dy);
  zoom(dr);
  
  /*
  float rI = 0.0f;
  for (int i = 0; i < 10000000;i++)
    rI += sin(i);*/
}
