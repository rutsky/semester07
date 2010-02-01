// xprimitive.h
// DirectX primitive abstract class declaration and some implementations.
// Vladimir Rutsky <altsysrq@gmail.com>
// 09.09.2009

#ifndef XPRIMITIVE_H
#define XPRIMITIVE_H

#include "point.h"
#include "triangle.h"
#include "color.h"
#include "xvertex.h"
#include "xcom_ptr.h"

#include <d3dx9.h>

namespace xprimitives
{
  class IXDrawablePrimitive
  {
  public:
    virtual void render( LPDIRECT3DDEVICE9 d3ddev ) = 0;
  };
}  // End of namespace 'primitives'

// TODO: Move to separate file.
namespace xprimitives
{
  struct Triangle
    : IXDrawablePrimitive
  {
    Triangle( LPDIRECT3DDEVICE9 d3ddev,
              cg::triangle_4f const &tr, 
              cg::color_4b const &c0 = cg::color_4b(),
              cg::color_4b const &c1 = cg::color_4b(),
              cg::color_4b const &c2 = cg::color_4b() )
      : tr_(tr)
      , c0_(c0), c1_(c1), c2_(c2)
    {
      xcg::vertex vertices[3];
      
      {
        // Initializing vertices array.
        xcg::set_vertex_position(vertices[0], tr.p0);
        xcg::set_vertex_position(vertices[1], tr.p1);
        xcg::set_vertex_position(vertices[2], tr.p2);
      
        xcg::set_vertex_color(vertices[0], c0);
        xcg::set_vertex_color(vertices[1], c1);
        xcg::set_vertex_color(vertices[2], c2);
      }
    
      {
        // Creating vertex buffer.
        LPDIRECT3DVERTEXBUFFER9 vBuffer;
        d3ddev->CreateVertexBuffer(3 * sizeof(xcg::vertex), // Length.
                                   0,                       // Usage.
                                   xcg::VERTEX_FVF,         // FVF.
                                   D3DPOOL_MANAGED,         // Pool.
                                   &vBuffer,                // Pointer to pointer to vertex buffer.
                                   NULL);                   // Reserved.
        vBuffer_.reset(vBuffer);
      }
      
      {
        // Filling vertex buffer.
        void *pVoid;
        
        vBuffer_->Lock(0, 0, &pVoid, 0);            // Locking buffer.
        memcpy(pVoid, vertices, sizeof(vertices)); // Copying vertices to the vertex buffer.
        vBuffer_->Unlock();                        // Unlocking buffer.
      }
    }
    
    // IXDrawablePrimitive
  public:
    void render( LPDIRECT3DDEVICE9 d3ddev )
    {
      // Setting FVF
      d3ddev->SetFVF(xcg::VERTEX_FVF);
      
      // Setting drawing buffer.
      d3ddev->SetStreamSource(0,                    // Stream number.
                              vBuffer_.get(),       // Pointer to stream data.
                              0,                    // Offset in bytes.
                              sizeof(xcg::vertex)); // Stride.
      
      // Copying primitive to back byuffer.
      d3ddev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
    }
    
  private:
    cg::triangle_4f tr_;
    cg::color_4b    c0_, c1_, c2_;
    
    xcg::com_ptr<IDirect3DVertexBuffer9> vBuffer_;
  };
} // End of namespace 'primitives'

#endif // XPRIMITIVE_H
