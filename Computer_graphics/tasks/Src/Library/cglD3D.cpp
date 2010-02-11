/*
 *  CVS Revision:$Id: cglD3D.cpp,v 1.0 10 Sep 2005 ã. Bvs Exp $
 *
 *  Contact Person: Sang Oak WOO, James D.K. KIM
 *
 *  This software module was originally developed by SAMSUNG Electronics
 *  Co., Ltd. in the course of development of Direct3D Mobile Device
 *  Driver.
 *
 *  Copyright is not released for non SAMSUNG Electronics products. SAMSUNG
 *  Electronics Co., Ltd. retains full right to use the code for his/her
 *  own purpose, assign or donate the code to a third party and to inhibit
 *  third parties from using the code for non SAMSUNG Electronics products.
 *  This copyright notice must be included in all copies or derivative
 *  works.
 *
 *  Copyright (C) 2005, SAMSUNG Electronics Co., Ltd.  All Rights Reserved.
 *
 *
 *  For more information or to receive an up to date version of this
 *  module, you may contact Sang Oak WOO at sowoo@samsung.com and James
 *  D. K. KIM at jamesdk.kim@samsung.com.
 */

#include "precompiled.h"

/**
  @file
  @brief    @documentme
  @date     Created on 10/09/2005
  @project  D3DBase
  @author   Bvs
*/
// *******************************************************
// compiler specific

// *******************************************************************
// includes
#include <windows.h>

// this system
#include "cglD3D.h"

// *******************************************************************
// defines & constants

// *******************************************************************
// static data

// *******************************************************************
// methods 

// *******************************************************************
// functions 

cglD3D::FormatRecord cglD3D::m_formats[BPP_LAST] = 
{ {   D3DFMT_R5G6B5, D3DFMT_D16 },
  {   D3DFMT_R8G8B8, D3DFMT_D24X8 },
  { D3DFMT_X8R8G8B8, D3DFMT_D24S8 } };

// *******************************************************************
// functions

/**
* This method creates Direct3D8, Direct3D8Device
*/
cglD3D::cglD3D(const CreateParams &params)
{
  D3DPRESENT_PARAMETERS ppParams;
  HRESULT               hRes;
  DWORD                 nBehaviour;

  // Create interface
  m_lpD3D9 = Direct3DCreate9(D3D_SDK_VERSION);
  if (m_lpD3D9 == NULL)
    return;

  // A bit of checking: check adapters count
  if (m_lpD3D9->GetAdapterCount() < 1)
    return;

  // Here we simply assume that we ALWAYS start adapter with 0 index.
  // Commonly there is only one adapter, but in case of additional PCI video cards
  // we gonna miss them. 

  // Get caps for future use
  hRes = m_lpD3D9->GetDeviceCaps(0, D3DDEVTYPE_HAL, &m_caps);

  // Simply fill presentation parameters
  memset(&ppParams, 0, sizeof(D3DPRESENT_PARAMETERS));
  ppParams.Windowed               = TRUE; // We choose windowed mode
  ppParams.BackBufferCount        = 1;
  ppParams.MultiSampleType        = D3DMULTISAMPLE_NONE;
  ppParams.SwapEffect             = D3DSWAPEFFECT_DISCARD;
  ppParams.EnableAutoDepthStencil = TRUE; // We want to create depth (z-buffer)
  ppParams.AutoDepthStencilFormat = m_formats[params.nBPP].fmtDepthBuffer;
  ppParams.hDeviceWindow          = HWND(params.hWnd);
  ppParams.BackBufferWidth        = params.nWidth;
  ppParams.BackBufferHeight       = params.nHeight;
  ppParams.BackBufferFormat       = m_formats[params.nBPP].fmtBackBuffer;

  // Determine the behaviour
  if ((m_caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) != 0)
    nBehaviour = D3DCREATE_HARDWARE_VERTEXPROCESSING;
  else
    nBehaviour = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

  // Create the device
  hRes = m_lpD3D9->CreateDevice(0, D3DDEVTYPE_HAL, ppParams.hDeviceWindow, nBehaviour, 
                                &ppParams, &m_lpD3D9Device);
  if (hRes != D3D_OK)
    return;
}

cglD3D::~cglD3D()
{
  // Kill device if was created
  if (m_lpD3D9Device != NULL)
    m_lpD3D9Device->Release();

  // Kill interface if was created
  if (m_lpD3D9 != NULL)
    m_lpD3D9->Release();
} 

bool cglD3D::isFailed()
{
  return (m_lpD3D9 == NULL || m_lpD3D9Device == NULL);
}

bool cglD3D::beginRender()
{
  // Begin rendering
  HRESULT hRes = m_lpD3D9Device->BeginScene();
  return (hRes == D3D_OK); 
} 

void cglD3D::endRender()
{
  // Finish rendering
  m_lpD3D9Device->EndScene();

  // Present rendering results (performs coping from back to front buffer)
  m_lpD3D9Device->Present(NULL, NULL, NULL, NULL);
} 

void cglD3D::clear(unsigned int nColor)
{
  m_lpD3D9Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, nColor, 1.0f, 0);
} 
