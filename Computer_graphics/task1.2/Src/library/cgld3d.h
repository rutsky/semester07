#ifndef __CGLD3D_H__632619820234375000
#define __CGLD3D_H__632619820234375000

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
// engine

// standard

// *******************************************************************
// defines & constants

// *******************************************************************
// classes 

#include <d3d9.h>

// *******************************************************************
// defines

// *******************************************************************
// class

class cglD3D
{
public:
  // Bit-per-pixel enum
  enum BPP
  {
    BPP_NA = -1,
    BPP_16,
    BPP_24,
    BPP_32,
    BPP_LAST,
    BPP_FORCEDWORD = 0x7FFFFFFF
  };

  // Direct X initialization parameters
  struct CreateParams
  {
    void*   hWnd;      // Main window handle
    // Back buffer parameters
    DWORD   nWidth;    // Back buffer width
    DWORD   nHeight;   // Back buffer height
    BPP     nBPP;      // Back buffer bits per pixel: 16, 24, 32 allowed.
  };

  cglD3D(const CreateParams &params);
  ~cglD3D();

  bool isFailed();

  // This function should be called before all rendering on current frame
  bool beginRender();
  // This function should be called after all rendering on current frame
  void endRender();
  // This function clears target & depth buffer
  void clear(unsigned int nColor);
  // Return device for external use
  LPDIRECT3DDEVICE9 getDevice() const { return m_lpD3D9Device; }

protected:
  // Format correspondence record
  struct FormatRecord 
  {
    D3DFORMAT fmtBackBuffer;
    D3DFORMAT fmtDepthBuffer;
  };

  // Fields
  static FormatRecord m_formats[BPP_LAST];

  // D3D data
  LPDIRECT3D9        m_lpD3D9;        // D3D9 interface pointer
  LPDIRECT3DDEVICE9  m_lpD3D9Device;  // D3D9 device interface pointer
  D3DCAPS9           m_caps;          // D3D9 caps
};

// *******************************************************************
// functions 

#endif //__CGLD3D_H__632619820234375000
