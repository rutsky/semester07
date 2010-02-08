/**
  @file     cglMain.cpp
  @brief    WinMain container
  @date     Created on 10/09/2005
  @project  D3DBase
  @author   Bvs
*/

// *******************************************************************
// includes

#include "windows.h"

#include "application.h"

/**
  @brief    This function is WinMain for D3DBase project

  @return   Windows error code
  @param    hInstance        standard WinMain input
  @param    hPrevInsatnce    standard WinMain input
  @param    lpszCommandLine  standard WinMain input
  @param    nCmdShow         standard WinMain input
  @author   Bvs
  @see      MSDN =)
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInsatnce,
                   LPTSTR lpszCommandLine, int nCmdShow)
{
  Application app(800, 600, (void*)hInstance, nCmdShow);
  if (!app.isFailed())
    app.theLoop();
} // end of WinMain

