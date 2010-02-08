/**
  @file     cglapp.cpp
  @brief    Class cglApp definition
  @date     Created on 10/09/2005
  @project  D3DBase
  @author   Bvs
*/

// *******************************************************************
// includes

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "cglD3D.h"

#include "cglApp.h"

// *******************************************************************
// defines

// *******************************************************************
// local data

namespace
{
  const char * s_windowClassName = "D3DBase9";
  const float  s_fpsMeasurementTime = 5.0f;

}

// *******************************************************************
// functions

LRESULT CALLBACK D3DBaseAppCallback(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
  // Retrieve our object pointer
  cglApp *pApp = (cglApp*)(GetWindowLong(hWnd, 0));
  
  if (pApp != NULL && pApp->processInput(nMsg, wParam, lParam))
    return 0;
  else
    return DefWindowProc(hWnd, nMsg, wParam, lParam); 
} 

// *******************************************************************
// Methods

cglApp::cglApp(int nW, int nH, void* hInst, int nCmdShow) 
  : m_hWnd(NULL)
  , m_hInstance(hInst)
  , m_nClearColor(0xFF007F00)
  , m_pD3D(NULL)
  , m_nFrameCount(0)
  , m_rPrevTime(0.0f)
{
  // Register window class
  WNDCLASS wndClass;
  wndClass.style          = 0;
  wndClass.lpfnWndProc    = D3DBaseAppCallback;
  wndClass.cbClsExtra     = 0;
  wndClass.cbWndExtra     = 4;
  wndClass.hInstance      = HINSTANCE(hInst);
  wndClass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
  wndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
  wndClass.hbrBackground  = HBRUSH(GetStockObject(WHITE_BRUSH));
  wndClass.lpszMenuName   = NULL;
  wndClass.lpszClassName  = s_windowClassName;
  RegisterClass(&wndClass);

  // Adjust window in regard to client area nW x nH
  int  nStyle = WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
  RECT rRect;
  SetRect(&rRect, 0, 0, nW, nH);
  AdjustWindowRect(&rRect, nStyle, TRUE);
  
  // Create main window
  m_hWnd = NULL;
  m_hWnd = (void*)CreateWindow(s_windowClassName, getWindowText(), nStyle,
                               CW_USEDEFAULT, CW_USEDEFAULT, 
                               (rRect.right - rRect.left), (rRect.bottom - rRect.top),
                               NULL, NULL, HINSTANCE(hInst), NULL);
  if (m_hWnd == NULL)
    return;
    
  // Set pointer
  SetWindowLong(HWND(m_hWnd), 0, LONG(this));

  // Show window
  ShowWindow(HWND(m_hWnd), nCmdShow);
  UpdateWindow(HWND(m_hWnd));
  
  // We need to determine the BPP of desktop
  HDC hDC = GetDC(HWND(m_hWnd));            // Get DC of desktop
  int nBPP = GetDeviceCaps(hDC, BITSPIXEL); // Retrieve BPP
  ReleaseDC(HWND(m_hWnd), hDC);             // Release DC handle

  // Create our D3D class
  cglD3D::CreateParams params;
  params.hWnd    = m_hWnd;
  params.nBPP    = (nBPP == 32) ? cglD3D::BPP_32 : cglD3D::BPP_16;
  params.nWidth  = nW;
  params.nHeight = nH;
  m_pD3D = new cglD3D(params);
  // Check creation result
  if (m_pD3D == NULL || m_pD3D->isFailed())
    return;

  // Init random generator
  srand(0);
}

cglApp::~cglApp()
{
  // Kill D3D
  if (m_pD3D != NULL)
    delete m_pD3D;
  // Kill window
  if (m_hWnd != NULL)
    DestroyWindow(HWND(m_hWnd));
} 

void cglApp::theLoop()
{
  while (TRUE)
  {
    MSG nMsg;
    if (PeekMessage(&nMsg, NULL, 0U, 0U, PM_REMOVE))
    {
      if (nMsg.message == WM_QUIT)
        break;

      TranslateMessage(&nMsg);
      DispatchMessage(&nMsg);
    }
    else
    {
      update();
      render();
    } // end if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
  } // end while (TRUE)
}

bool cglApp::isFailed()
{
  return (m_hWnd == NULL /*|| m_pD3D == NULL*/);
}

bool cglApp::processInput(unsigned int nMsg, int wParam, long lParam)
{
  // Handle input
  switch (nMsg)
  {
  case WM_CLOSE:
    PostQuitMessage(0);
    return true;
  case WM_KEYDOWN:
    if (wParam == VK_ESCAPE)
    {
      PostQuitMessage(0);
      return true;
    }
    break;
  }
  
  return false;
}

void cglApp::update(void)
{
  m_timer.update();
  float rTime = m_timer.getTime() - m_rPrevTime;
  if (rTime > s_fpsMeasurementTime)
  {
    // Calculate FPS
    float rFPS = float(m_nFrameCount) / rTime;
    // Show fps
    char fpsString[50];
    sprintf_s(fpsString, "%s FPS = %3.6f", getWindowText(), rFPS);
    SetWindowText(HWND(m_hWnd), fpsString);
    // Drop
    m_rPrevTime   = m_timer.getTime();
    m_nFrameCount = 0;
  }
  m_nFrameCount++;
} 

void cglApp::render()
{
  if (m_pD3D->beginRender())
  {
    // Clear screen with current color
    m_pD3D->clear(m_nClearColor);
    
    // Perform rendering internals
    renderInternal();

    m_pD3D->endRender();
  } 
} 
