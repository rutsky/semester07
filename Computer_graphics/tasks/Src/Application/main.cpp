/**
  @file     cglMain.cpp
  @brief    WinMain container
  @date     Created on 10/09/2005
  @project  D3DBase
  @author   Bvs
*/

// *******************************************************************
// includes

#include "precompiled.h"

#include <cassert>
#include <memory>

#include "windows.h"

#include "application.h"
#include "myApp.h"

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
#ifndef NDEBUG
  //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  //_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
#endif // NDEBUG

  bool failed = false;

  {
    //std::auto_ptr<cglApp> app(new myApp(800, 600, (void*)hInstance, nCmdShow));
    std::auto_ptr<cglApp> app(new Application(800, 600, (void*)hInstance, nCmdShow));
    if (!app->isFailed())
      failed = failed || app->theLoop();
    else
      failed = true;
  }
  
#ifndef NDEBUG
  _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
  failed = failed || (_CrtDumpMemoryLeaks() != 0);
#endif // NDEBUG

  assert(!failed);
  return (int)failed;
} // end of WinMain

