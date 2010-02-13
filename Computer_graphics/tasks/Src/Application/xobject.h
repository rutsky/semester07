// xobject.h
// Drawable objects.
// Vladimir Rutsky, 4057/2
// 10.02.2010

#ifndef XOBJECT_H
#define XOBJECT_H

#include <vector>
#include <cassert>
#include <ostream>
#include <sstream>

#include <boost/shared_ptr.hpp>

#include <d3d9.h>
#include <d3dx9math.h>

#include "FVF_Gen.h"

#include "util.h"
#include "object.h"
#include "constants.h"

namespace xobject
{
  namespace
  {
    struct FVFGenConfig
    {
        struct Pos          {D3DXVECTOR3 v;};
        struct RHW          {float rhw;};
        template<int n>
        struct Weights_Gen  {float weights[n]; typedef Weights_Gen<n> Res;};
        struct Normal       {D3DXVECTOR3 n;};
        struct Diffuse      {DWORD diffuse;};
        struct Specular     {DWORD specular;};
        template<int n>
        struct Tex_1_Gen    {float tex_1[n]; typedef Tex_1_Gen<n> Res;};
        template<int n>
        struct Tex_2_Gen    {float tex_2[n]; typedef Tex_2_Gen<n> Res;};
        template<int n>
        struct Tex_3_Gen    {float tex_3[n]; typedef Tex_3_Gen<n> Res;};
        template<int n>
        struct Tex_4_Gen    {float tex_4[n]; typedef Tex_4_Gen<n> Res;};
    };
  } // End of anonymous namespace

#pragma pack ( push, 1 )
  namespace vertex_xyzcolor
  {
    DWORD const vertexFormat = D3DFVF_XYZ | D3DFVF_DIFFUSE;
    typedef D3D_Util::FVF_Gen<vertexFormat, FVFGenConfig>::Res Vertex;

    inline Vertex fill( D3DXVECTOR3 const &v, DWORD diffuse )
    {
      Vertex result;
      result.v = v;
      result.diffuse = diffuse;
      return result;
    }
  } // End of namespace 'vertex_xyzcolor'

  namespace vertex_xyznormalcolor
  {
    DWORD const vertexFormat = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE;
    typedef D3D_Util::FVF_Gen<vertexFormat, FVFGenConfig>::Res Vertex;

    inline Vertex fill( D3DXVECTOR3 const &v, D3DXVECTOR3 const &n, DWORD diffuse )
    {
      Vertex result;
      result.v = v;
      result.n = n;
      result.diffuse = diffuse;
      return result;
    }
  } // End of namespace 'vertex_xyznormalcolor'
#pragma pack ( pop )

  class BaseXObject
    : public virtual object::IDrawableObject
    , public virtual object::ISceneObject
  {
  protected:
    BaseXObject(IDirect3DDevice9 *device)
      : m_device(device)
    {
    }

  protected:
    IDirect3DDevice9 *m_device;
  };

  inline IDirect3DVertexBuffer9 * createAndFillVertexBuffer( IDirect3DDevice9 *device, 
    void *vertices, size_t bufferSize, DWORD vertexFormat )
  {
    IDirect3DVertexBuffer9 *vertexBuffer;
    if (FAILED(device->CreateVertexBuffer(bufferSize,
                 0, vertexFormat,
                 D3DPOOL_DEFAULT, &vertexBuffer, NULL)))
      return 0;

    void *verticesMem;
    if (FAILED(vertexBuffer->Lock(0, bufferSize, &verticesMem, 0)))
    {
      vertexBuffer->Release();
      return 0;
    }
    memcpy(verticesMem, vertices, bufferSize);
    vertexBuffer->Unlock();

    return vertexBuffer;
  }

  inline IDirect3DIndexBuffer9 * createAndFillIndexBuffer( IDirect3DDevice9 *device, 
    void *indices, size_t bufferSize, D3DFORMAT indexFormat )
  {
    IDirect3DIndexBuffer9 *indexBuffer;
    if (FAILED(device->CreateIndexBuffer(bufferSize,
                 0, indexFormat,
                 D3DPOOL_DEFAULT, &indexBuffer, NULL)))
      return 0;

    void *indicesMem;
    if (FAILED(indexBuffer->Lock(0, bufferSize, &indicesMem, 0)))
    {
      indexBuffer->Release();
      return 0;
    }
    memcpy(indicesMem, indices, bufferSize);
    indexBuffer->Unlock();

    return indexBuffer;
  }

  class XPrimitive
    : public BaseXObject
  {
  public:
    XPrimitive( IDirect3DDevice9 *device, 
                IDirect3DVertexBuffer9* streamData, 
                DWORD vertexFormat, size_t vertexSize,
                D3DPRIMITIVETYPE primitiveType, size_t primitiveCount )
      : BaseXObject(device)
      , m_streamData(streamData)
      , m_vertexFormat(vertexFormat)
      , m_vertexSize(vertexSize)
      , m_primitiveType(primitiveType)
      , m_primitiveCount(primitiveCount)
    {
    }

    ~XPrimitive()
    {
      m_streamData->Release();
    }

    // object::IDrawableObject
  public:
    void draw()
    {
      m_device->SetStreamSource(0, m_streamData, 0, m_vertexSize);
      m_device->SetFVF(m_vertexFormat);
      m_device->DrawPrimitive(m_primitiveType, 0, m_primitiveCount);
    }

  protected:
    IDirect3DVertexBuffer9 *m_streamData;
    DWORD m_vertexFormat;
    size_t m_vertexSize;
    D3DPRIMITIVETYPE m_primitiveType;
    size_t m_primitiveCount;
  };

  class XMesh
    : public BaseXObject
  {
  public:
    XMesh( IDirect3DDevice9 *device, 
           ID3DXMesh *mesh,
           std::vector<D3DMATERIAL9> materials,
           std::vector<IDirect3DTexture9 *> textures )
      : BaseXObject(device)
      , m_mesh(mesh)
      , m_materials(materials)
      , m_textures(textures)
    {
      assert(materials.size() == textures.size());
    }

    ~XMesh()
    {
      for (size_t i = 0; i < m_materials.size(); ++i)
      {
        if (m_textures[i])
          m_textures[i]->Release();
      }
      m_mesh->Release();
    }

  public:
    static XMesh * create( IDirect3DDevice9 *device, char const *dataDirectory, char const *fileName )
    {
      // Based on DirectX Meshes example.

      ID3DXMesh *mesh;
      DWORD materialsNum;
      LPD3DXBUFFER materialsBuffer;


      {
        std::ostringstream ostr;
        ostr << dataDirectory << "/" << fileName;

        // Load the mesh from the specified file.
        if (FAILED(D3DXLoadMeshFromX(ostr.str().c_str(), D3DXMESH_SYSTEMMEM,
                                     device, NULL,
                                     &materialsBuffer, NULL, &materialsNum,
                                     &mesh)))
          return 0;
      }

      // Extracting the material properties and texture names from the materialsBuffer.
      D3DXMATERIAL *xmaterials = (D3DXMATERIAL *)materialsBuffer->GetBufferPointer();
      std::vector<D3DMATERIAL9>       materials(materialsNum);
      std::vector<IDirect3DTexture9 *> textures(materialsNum);
      
      for (size_t i = 0; i < materialsNum; ++i)
      {
        // Copy the material.
        materials[i] = xmaterials[i].MatD3D;

        // Set the ambient color for the material (D3DX does not do this).
        materials[i].Ambient = materials[i].Diffuse;

        textures[i] = NULL;
        if (xmaterials[i].pTextureFilename != NULL &&
            lstrlenA(xmaterials[i].pTextureFilename) > 0)
        {
          std::ostringstream ostr;
          ostr << dataDirectory << "/" << xmaterials[i].pTextureFilename;

          // Create the texture.
          if (FAILED(D3DXCreateTextureFromFileA(device,
                                                ostr.str().c_str(),
                                                &textures[i])))
            OutputDebugString("Failed to load some texture\n");
        }
      }

      // Done with the material buffer.
      materialsBuffer->Release();

      return new XMesh(device, mesh, materials, textures);
    }

    // object::IDrawableObject
  public:
    void draw()
    {
      for (size_t i = 0; i < m_materials.size(); ++i)
      {
        m_device->SetMaterial(&m_materials[i]);
        m_device->SetTexture(0, m_textures[i]);

        m_mesh->DrawSubset(i);
      }
    }

  protected:
    ID3DXMesh *m_mesh;
    std::vector<D3DMATERIAL9> m_materials;
    std::vector<IDirect3DTexture9 *> m_textures;
  };

  class XTriangle
    : public XPrimitive
  {
  protected:
    XTriangle( IDirect3DDevice9 *device, 
               IDirect3DVertexBuffer9* streamData, 
               DWORD vertexFormat, size_t vertexSize,
               D3DPRIMITIVETYPE primitiveType, size_t primitiveCount )
      : XPrimitive(device, streamData, vertexFormat, vertexSize, primitiveType, primitiveCount)
    {
    }

  public:
    static XTriangle * create( IDirect3DDevice9 *device,
      D3DXVECTOR3 const &p0, D3DXVECTOR3 const &p1, D3DXVECTOR3 const &p2,
      DWORD color0, DWORD color1, DWORD color2 )
    {
      vertex_xyzcolor::Vertex const vertices[] = 
        {
          vertex_xyzcolor::fill(p0, color0),
          vertex_xyzcolor::fill(p1, color1),
          vertex_xyzcolor::fill(p2, color2),
        };
      size_t const verticesNum = util::array_size(vertices);

      IDirect3DVertexBuffer9 *vertexBuffer = 
        createAndFillVertexBuffer(device, (void *)vertices, sizeof(vertices), vertex_xyzcolor::vertexFormat);
      if (!vertexBuffer)
        return 0;

      return new XTriangle(device, vertexBuffer, vertex_xyzcolor::vertexFormat, 
        sizeof(vertex_xyzcolor::Vertex), D3DPT_TRIANGLELIST, 1);
    }

    static XTriangle * create( IDirect3DDevice9 *device,
      D3DXVECTOR3 const &p0, D3DXVECTOR3 const &p1, D3DXVECTOR3 const &p2 )
    {
      return create(device, p0, p1, p2, RGB(255, 0, 0), RGB(0, 255, 0), RGB(0, 0, 255));
    }

    static XTriangle * create( IDirect3DDevice9 *device )
    {
      return create(device, D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 1, 0), D3DXVECTOR3(1, 0, 0));
    }
  };

  class XLine
    : public XPrimitive
  {
  protected:
    XLine( IDirect3DDevice9 *device, 
               IDirect3DVertexBuffer9* streamData, 
               DWORD vertexFormat, size_t vertexSize,
               D3DPRIMITIVETYPE primitiveType, size_t primitiveCount )
      : XPrimitive(device, streamData, vertexFormat, vertexSize, primitiveType, primitiveCount)
    {
    }

  public:
    static XLine * create( IDirect3DDevice9 *device,
      D3DXVECTOR3 const &p0, D3DXVECTOR3 const &p1, 
      DWORD color0, DWORD color1 )
    {
      vertex_xyzcolor::Vertex const vertices[] = 
        {
          vertex_xyzcolor::fill(p0, color0),
          vertex_xyzcolor::fill(p1, color1),
        };
      size_t const verticesNum = util::array_size(vertices);

      IDirect3DVertexBuffer9 *vertexBuffer = 
        createAndFillVertexBuffer(device, (void *)vertices, sizeof(vertices), vertex_xyzcolor::vertexFormat);
      if (!vertexBuffer)
        return 0;

      return new XLine(device, vertexBuffer, vertex_xyzcolor::vertexFormat, 
        sizeof(vertex_xyzcolor::Vertex), D3DPT_LINELIST, 1);
    }

    static XLine * create( IDirect3DDevice9 *device,
      D3DXVECTOR3 const &p0, D3DXVECTOR3 const &p1 )
    {
      return create(device, p0, p1, RGB(255, 0, 0), RGB(0, 255, 0));
    }

    static XLine * create( IDirect3DDevice9 *device )
    {
      return create(device, D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 1, 0));
    }
  };

  typedef boost::shared_ptr<XLine> xline_ptr_type;

  class XCoordinateSystem
    : public BaseXObject
  {
  protected:
    XCoordinateSystem( IDirect3DDevice9 *device, xline_ptr_type xAxis, xline_ptr_type yAxis, xline_ptr_type zAxis )
      : BaseXObject(device)
      , m_xAxis(xAxis)
      , m_yAxis(yAxis)
      , m_zAxis(zAxis)
    {
      assert(m_xAxis);
      assert(m_yAxis);
      assert(m_zAxis);
    }

  public:
    static XCoordinateSystem * create( IDirect3DDevice9 *device )
    {
      xline_ptr_type xAxis(XLine::create(device, 
        D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 0, 0), 
        constants::color::red, constants::color::red));
      xline_ptr_type yAxis(XLine::create(device, 
        D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 1, 0), 
        constants::color::green, constants::color::green));
      xline_ptr_type zAxis(XLine::create(device, 
        D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 1), 
        constants::color::blue, constants::color::blue));

      if (!xAxis || !yAxis || !zAxis)
        return 0;
      else
        return new XCoordinateSystem(device, xAxis, yAxis, zAxis);
    }

    // object::IDrawableObject
  public:
    void draw()
    {
      m_xAxis->draw();
      m_yAxis->draw();
      m_zAxis->draw();
    }

  protected:
    xline_ptr_type m_xAxis, m_yAxis, m_zAxis;
  };
} // End of namespace 'xobject'

#endif // XOBJECT_H
