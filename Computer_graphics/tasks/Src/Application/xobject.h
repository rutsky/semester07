// xobject.h
// Drawable objects.
// Vladimir Rutsky, 4057/2
// 10.02.2010

#ifndef XOBJECT_H
#define XOBJECT_H

#include <vector>
#include <map>
#include <cassert>
#include <ostream>
#include <sstream>

#include <boost/shared_ptr.hpp>
#include <boost/static_assert.hpp>

#include <d3d9.h>
#include <d3dx9math.h>

#include "FVF_Gen.h"

#include "util.h"
#include "object.h"
#include "constants.h"
#include "texture.h"

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
  namespace vertex_v_diffuse
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
  } // End of namespace 'vertex_v_diffuse'

  namespace vertex_v_n_diffuse
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
  } // End of namespace 'vertex_v_n_diffuse'
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
                IDirect3DVertexBuffer9 *vertexBuffer, 
                DWORD vertexFormat, size_t vertexSize,
                D3DPRIMITIVETYPE primitiveType, size_t primitiveCount )
      : BaseXObject(device)
      , m_vertexBuffer(vertexBuffer)
      , m_vertexFormat(vertexFormat)
      , m_vertexSize(vertexSize)
      , m_primitiveType(primitiveType)
      , m_primitiveCount(primitiveCount)
    {
    }

    ~XPrimitive()
    {
      m_vertexBuffer->Release();
    }

    // object::IDrawableObject
  public:
    void draw()
    {
      m_device->SetStreamSource(0, m_vertexBuffer, 0, m_vertexSize);
      m_device->SetFVF(m_vertexFormat);
      m_device->DrawPrimitive(m_primitiveType, 0, m_primitiveCount);
    }

  protected:
    IDirect3DVertexBuffer9 *m_vertexBuffer;
    DWORD m_vertexFormat;
    size_t m_vertexSize;
    D3DPRIMITIVETYPE m_primitiveType;
    size_t m_primitiveCount;
  };

  class XIndexedPrimitive
    : public BaseXObject
  {
  public:
    XIndexedPrimitive( IDirect3DDevice9 *device, 
                       IDirect3DVertexBuffer9 *vertexBuffer, 
                       IDirect3DIndexBuffer9 *indexBuffer, 
                       DWORD vertexFormat,
                       size_t vertexSize,
                       size_t verticesNum,
                       D3DPRIMITIVETYPE primitiveType, 
                       size_t primitiveCount )
      : BaseXObject(device)
      , m_vertexBuffer(vertexBuffer)
      , m_indexBuffer(indexBuffer)
      , m_vertexFormat(vertexFormat)
      , m_vertexSize(vertexSize)
      , m_verticesNum(verticesNum)
      , m_primitiveType(primitiveType)
      , m_primitiveCount(primitiveCount)
    {
    }

    ~XIndexedPrimitive()
    {
      m_vertexBuffer->Release();
      m_indexBuffer->Release();
    }

    // object::IDrawableObject
  public:
    void draw()
    {
      m_device->SetStreamSource(0, m_vertexBuffer, 0, m_vertexSize);
      m_device->SetFVF(m_vertexFormat);
      m_device->SetIndices(m_indexBuffer);
      m_device->DrawIndexedPrimitive(m_primitiveType, 0, 0, m_verticesNum, 0, m_primitiveCount);
    }

  protected:
    IDirect3DVertexBuffer9 *m_vertexBuffer;
    IDirect3DIndexBuffer9 *m_indexBuffer;
    DWORD m_vertexFormat;
    size_t m_vertexSize;
    size_t m_verticesNum;
    D3DPRIMITIVETYPE m_primitiveType;
    size_t m_primitiveCount;
  };

  class XMesh
    : public BaseXObject
  {
  public:
    typedef std::map<size_t, D3DMATERIAL9>        materials_map_type;
    typedef std::map<size_t, IDirect3DTexture9 *> textures_map_type;

    XMesh( IDirect3DDevice9 *device, 
           ID3DXMesh *mesh,
           materials_map_type const &materials,
           textures_map_type const &textures )
      : BaseXObject(device)
      , m_mesh(mesh)
      , m_materials(materials)
      , m_textures(textures)
    {
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
    static XMesh * create( IDirect3DDevice9 *device, char const *dataDirectory, char const *fileName, bool loadTextures = true )
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
      materials_map_type materials;
      textures_map_type textures;
      
      for (size_t i = 0; i < materialsNum; ++i)
      {
        // Copy the material.
        materials[i] = xmaterials[i].MatD3D;

        // Set the ambient color for the material (D3DX does not do this).
        materials[i].Ambient = materials[i].Diffuse;

        IDirect3DTexture9 *texture = NULL;
        if (loadTextures &&
            xmaterials[i].pTextureFilename != NULL &&
            lstrlenA(xmaterials[i].pTextureFilename) > 0)
        {
          std::ostringstream ostr;
          ostr << dataDirectory << "/" << xmaterials[i].pTextureFilename;

          // Create the texture.
          if (FAILED(D3DXCreateTextureFromFileA(device,
                                                ostr.str().c_str(),
                                                &texture)))
            OutputDebugString("Failed to load some texture\n");
        }

        if (texture)
          textures[i] = texture;
      }

      // Done with the material buffer.
      materialsBuffer->Release();

      return new XMesh(device, mesh, materials, textures);
    }

    template< class FileNameIterator >
    static XMesh * createWithCustomTextures( IDirect3DDevice9 *device, char const *dataDirectory, char const *fileName,
      size_t width, size_t height, D3DFORMAT format, FileNameIterator textureFileNameFirst, FileNameIterator textureFileNameBeyond )
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
      materials_map_type materials;
      textures_map_type  textures;
      
      for (size_t i = 0; i < materialsNum; ++i)
      {
        // Copy the material.
        materials[i] = xmaterials[i].MatD3D;

        // Set the ambient color for the material (D3DX does not do this).
        materials[i].Ambient = materials[i].Diffuse;

        textures[i] = texture::loadTextureWithMipmaps(device, width, height, format, dataDirectory, 
          textureFileNameFirst, textureFileNameBeyond);
      }

      // Done with the material buffer.
      materialsBuffer->Release();

      return new XMesh(device, mesh, materials, textures);
    }

    static XMesh * createCylinder( IDirect3DDevice9 *device,
      double radius1,
      double radius2,
      double length,
      size_t slices,
      size_t stacks,
      D3DMATERIAL9 const &material )
    {
      ID3DXMesh *mesh;
      if (FAILED(D3DXCreateCylinder(device, (float)radius1, (float)radius2, (float)length, slices, stacks, &mesh, NULL)))
        return NULL;

      materials_map_type materials;
      materials[0] = material;
      return new XMesh(device, mesh, materials, textures_map_type());
    }

    // object::IDrawableObject
  public:
    void draw()
    {
      DWORD size;
      m_mesh->GetAttributeTable(NULL, &size); // TODO: Not sure, not sure...

      // FIXME
      if (size == 0)
        size = 1;

      for (size_t i = 0; i < size; ++i)
      {
        if (m_materials.find(i) != m_materials.end())
          m_device->SetMaterial(&m_materials[i]);

        if (m_textures.find(i) != m_textures.end())
          m_device->SetTexture(0, m_textures[i]);

        m_mesh->DrawSubset(i);
      }
    }

  protected:
    ID3DXMesh *m_mesh;
    materials_map_type m_materials;
    textures_map_type m_textures;
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
      vertex_v_diffuse::Vertex const vertices[] = 
        {
          vertex_v_diffuse::fill(p0, color0),
          vertex_v_diffuse::fill(p1, color1),
          vertex_v_diffuse::fill(p2, color2),
        };
      size_t const verticesNum = util::array_size(vertices);

      IDirect3DVertexBuffer9 *vertexBuffer = 
        createAndFillVertexBuffer(device, (void *)vertices, sizeof(vertices), vertex_v_diffuse::vertexFormat);
      if (!vertexBuffer)
        return 0;

      return new XTriangle(device, vertexBuffer, vertex_v_diffuse::vertexFormat, 
        sizeof(vertex_v_diffuse::Vertex), D3DPT_TRIANGLELIST, 1);
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

  class XTrapezoid
    : public XPrimitive
  {
  protected:
    XTrapezoid( IDirect3DDevice9 *device, 
                IDirect3DVertexBuffer9* streamData, 
                DWORD vertexFormat, size_t vertexSize,
                D3DPRIMITIVETYPE primitiveType, size_t primitiveCount )
      : XPrimitive(device, streamData, vertexFormat, vertexSize, primitiveType, primitiveCount)
    {
    }

  public:
    static XTrapezoid * create( IDirect3DDevice9 *device,
      double lowerSide, double upperSide, double trapezoidHeight, double zdepth,
      DWORD forwardFaceColor, DWORD rightFaceColor, 
      DWORD topFaceColor, DWORD leftFaceColor, 
      DWORD bottomFaceColor, DWORD backFaceColor )
    {
      float const x = (float)(lowerSide / 2.0);
      float const X = (float)(upperSide / 2.0);
      float const y = (float)(trapezoidHeight / 2.0);
      float const z = (float)(zdepth / 2.0);

      // TODO: Not checked.
      float const tga = (float)((x - X) / (2.0 * y));
      float const ax = (float)(sqrt(1.0 / (1.0 + util::sqr(tga))));
      float const ay = (float)(sqrt(1.0 / (1.0 + 1.0 / util::sqr(tga))));

      vertex_v_n_diffuse::Vertex const vertices[] = 
        {
          // Foreground.
          vertex_v_n_diffuse::fill(D3DXVECTOR3(-x, -y, +z), D3DXVECTOR3( 0,  0,  1), forwardFaceColor),
          vertex_v_n_diffuse::fill(D3DXVECTOR3(-X, +y, +z), D3DXVECTOR3( 0,  0,  1), forwardFaceColor),
          vertex_v_n_diffuse::fill(D3DXVECTOR3(+x, -y, +z), D3DXVECTOR3( 0,  0,  1), forwardFaceColor),

          vertex_v_n_diffuse::fill(D3DXVECTOR3(+x, -y, +z), D3DXVECTOR3( 0,  0,  1), forwardFaceColor),
          vertex_v_n_diffuse::fill(D3DXVECTOR3(-X, +y, +z), D3DXVECTOR3( 0,  0,  1), forwardFaceColor),
          vertex_v_n_diffuse::fill(D3DXVECTOR3(+X, +y, +z), D3DXVECTOR3( 0,  0,  1), forwardFaceColor),

          // Background.
          vertex_v_n_diffuse::fill(D3DXVECTOR3(-X, +y, -z), D3DXVECTOR3( 0,  0, -1), forwardFaceColor),
          vertex_v_n_diffuse::fill(D3DXVECTOR3(-x, -y, -z), D3DXVECTOR3( 0,  0, -1), forwardFaceColor),
          vertex_v_n_diffuse::fill(D3DXVECTOR3(+x, -y, -z), D3DXVECTOR3( 0,  0, -1), forwardFaceColor),

          vertex_v_n_diffuse::fill(D3DXVECTOR3(-X, +y, -z), D3DXVECTOR3( 0,  0, -1), forwardFaceColor),
          vertex_v_n_diffuse::fill(D3DXVECTOR3(+x, -y, -z), D3DXVECTOR3( 0,  0, -1), forwardFaceColor),
          vertex_v_n_diffuse::fill(D3DXVECTOR3(+X, +y, -z), D3DXVECTOR3( 0,  0, -1), forwardFaceColor),

          // Left.
          vertex_v_n_diffuse::fill(D3DXVECTOR3(-x, -y, -z), D3DXVECTOR3(-ax, ay, 0), forwardFaceColor),
          vertex_v_n_diffuse::fill(D3DXVECTOR3(-X, +y, -z), D3DXVECTOR3(-ax, ay, 0), forwardFaceColor),
          vertex_v_n_diffuse::fill(D3DXVECTOR3(-X, +y, +z), D3DXVECTOR3(-ax, ay, 0), forwardFaceColor),

          vertex_v_n_diffuse::fill(D3DXVECTOR3(-X, +y, +z), D3DXVECTOR3(-ax, ay, 0), forwardFaceColor),
          vertex_v_n_diffuse::fill(D3DXVECTOR3(-x, -y, +z), D3DXVECTOR3(-ax, ay, 0), forwardFaceColor),
          vertex_v_n_diffuse::fill(D3DXVECTOR3(-x, -y, -z), D3DXVECTOR3(-ax, ay, 0), forwardFaceColor),

          // Right.
          vertex_v_n_diffuse::fill(D3DXVECTOR3(+x, -y, -z), D3DXVECTOR3(-ax, ay, 0), forwardFaceColor),
          vertex_v_n_diffuse::fill(D3DXVECTOR3(+X, +y, -z), D3DXVECTOR3(-ax, ay, 0), forwardFaceColor),
          vertex_v_n_diffuse::fill(D3DXVECTOR3(+X, +y, +z), D3DXVECTOR3(-ax, ay, 0), forwardFaceColor),

          vertex_v_n_diffuse::fill(D3DXVECTOR3(+X, +y, +z), D3DXVECTOR3(-ax, ay, 0), forwardFaceColor),
          vertex_v_n_diffuse::fill(D3DXVECTOR3(+x, -y, +z), D3DXVECTOR3(-ax, ay, 0), forwardFaceColor),
          vertex_v_n_diffuse::fill(D3DXVECTOR3(+x, -y, -z), D3DXVECTOR3(-ax, ay, 0), forwardFaceColor),

          // Top.
          vertex_v_n_diffuse::fill(D3DXVECTOR3(-X, +y, +z), D3DXVECTOR3( 0,  1,  0), forwardFaceColor),
          vertex_v_n_diffuse::fill(D3DXVECTOR3(-X, +y, -z), D3DXVECTOR3( 0,  1,  0), forwardFaceColor),
          vertex_v_n_diffuse::fill(D3DXVECTOR3(+X, +y, +z), D3DXVECTOR3( 0,  1,  0), forwardFaceColor),

          vertex_v_n_diffuse::fill(D3DXVECTOR3(-X, +y, -z), D3DXVECTOR3( 0,  1,  0), forwardFaceColor),
          vertex_v_n_diffuse::fill(D3DXVECTOR3(+X, +y, -z), D3DXVECTOR3( 0,  1,  0), forwardFaceColor),
          vertex_v_n_diffuse::fill(D3DXVECTOR3(+X, +y, +z), D3DXVECTOR3( 0,  1,  0), forwardFaceColor),

          // Bottom.
          vertex_v_n_diffuse::fill(D3DXVECTOR3(-x, -y, +z), D3DXVECTOR3( 0, -1,  0), forwardFaceColor),
          vertex_v_n_diffuse::fill(D3DXVECTOR3(-x, -y, -z), D3DXVECTOR3( 0, -1,  0), forwardFaceColor),
          vertex_v_n_diffuse::fill(D3DXVECTOR3(+x, -y, +z), D3DXVECTOR3( 0, -1,  0), forwardFaceColor),

          vertex_v_n_diffuse::fill(D3DXVECTOR3(-x, -y, -z), D3DXVECTOR3( 0, -1,  0), forwardFaceColor),
          vertex_v_n_diffuse::fill(D3DXVECTOR3(+x, -y, -z), D3DXVECTOR3( 0, -1,  0), forwardFaceColor),
          vertex_v_n_diffuse::fill(D3DXVECTOR3(+x, -y, +z), D3DXVECTOR3( 0, -1,  0), forwardFaceColor),
        };
      size_t const verticesNum = util::array_size(vertices);

      IDirect3DVertexBuffer9 *vertexBuffer = 
        createAndFillVertexBuffer(device, (void *)vertices, sizeof(vertices), vertex_v_n_diffuse::vertexFormat);
      if (!vertexBuffer)
        return 0;

      return new XTrapezoid(device, vertexBuffer, vertex_v_n_diffuse::vertexFormat, 
        sizeof(vertex_v_n_diffuse::Vertex), D3DPT_TRIANGLELIST, verticesNum / 3);
    }

    static XTrapezoid * create( IDirect3DDevice9 *device,
      double lowerSide, double upperSide, double trapezoidHeight, double zdepth,
      DWORD color )
    {
      return create(device, lowerSide, upperSide, trapezoidHeight, zdepth,
        color, color, 
        color, color, 
        color, color);
    }

    static XTrapezoid * create( IDirect3DDevice9 *device,
      double lowerSide, double upperSide, double trapezoidHeight, double zdepth )
    {
      DWORD color = constants::color::white();
      return create(device, lowerSide, upperSide, trapezoidHeight, zdepth,
        color, color, 
        color, color, 
        color, color);
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
      vertex_v_diffuse::Vertex const vertices[] = 
        {
          vertex_v_diffuse::fill(p0, color0),
          vertex_v_diffuse::fill(p1, color1),
        };
      size_t const verticesNum = util::array_size(vertices);

      IDirect3DVertexBuffer9 *vertexBuffer = 
        createAndFillVertexBuffer(device, (void *)vertices, sizeof(vertices), vertex_v_diffuse::vertexFormat);
      if (!vertexBuffer)
        return 0;

      return new XLine(device, vertexBuffer, vertex_v_diffuse::vertexFormat, 
        sizeof(vertex_v_diffuse::Vertex), D3DPT_LINELIST, 1);
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

  namespace xsurface
  {
    class XSurface
      : public XIndexedPrimitive
    {
    protected:
      XSurface( IDirect3DDevice9 *device, 
                IDirect3DVertexBuffer9 *vertexBuffer, 
                IDirect3DIndexBuffer9 *indexBuffer, 
                DWORD vertexFormat,
                size_t vertexSize,
                size_t verticesNum,
                D3DPRIMITIVETYPE primitiveType, 
                size_t primitiveCount )
        : XIndexedPrimitive(device, vertexBuffer, indexBuffer, vertexFormat, 
            vertexSize, verticesNum, primitiveType, primitiveCount)
      {
      }

    public:
      template< typename VertexGenerator, typename NormalGenerator, typename ColorGenerator >
      static XSurface * create( IDirect3DDevice9 *device,
        size_t nX, size_t nY,
        VertexGenerator vertexGen, NormalGenerator normalGen, ColorGenerator colorGen )
      {
        if (nY < 2 || nY < 2)
          return 0;

        D3DPRIMITIVETYPE const primitiveType = D3DPT_TRIANGLESTRIP;
        typedef vertex_v_n_diffuse::Vertex vertex_type;
        DWORD const vertexFormat = vertex_v_n_diffuse::vertexFormat;
        size_t const verticesNum = nX * nY;
        std::vector<vertex_type> vertices(verticesNum);
        BOOST_STATIC_ASSERT(sizeof(vertices[0]) == sizeof(vertex_type)); // To be sure that packing is expected.

        // Indexing:
        //    9 
        //    | \    ...
        // 1,7,8- 3 - 5,6
        //    | \ | \ |
        //    0 - 2 - 4
        //
        // Alternative (not used currently):
        //  7,8-10
        //   | /    ...
        //  0,9- 2 - 4
        //   | / | / |
        //   1 - 3 - 5,6
        D3DFORMAT indexFormat = D3DFMT_INDEX16;
        typedef unsigned short index_type;
        size_t const indicesNum = (nY - 1) * (nX * 2 + 2) - 2;
        std::vector<index_type> indices;
        BOOST_STATIC_ASSERT(sizeof(indices[0]) == sizeof(index_type)); // To be sure that packing is expected.

        size_t const primitiveCount = indicesNum - 2;

        {
          // Filling vertex buffer.
          for (size_t y = 0; y < nY; ++y)
            for (size_t x = 0; x < nX; ++x)
            {
              vertex_type &vertex = vertices[y * nX + x];

              double const rx = (double)x / (nX - 1);
              double const ry = (double)y / (nY - 1);

              vertex.v = vertexGen(rx, ry);
              vertex.n = normalGen(rx, ry);
              vertex.diffuse = colorGen(rx, ry);
            }

          // Filling index buffer.
          for (size_t y = 0; y < nY - 1; ++y)
          {
            for (size_t x = 0; x < nX; ++x)
            {
              indices.push_back(index_type((y + 0) * nX + x));
              indices.push_back(index_type((y + 1) * nX + x));
            }

            if ((y + 1) < nY - 1)
            {
              indices.push_back(indices.back());
              indices.push_back(index_type((y + 1) * nX));
            }
          }
        }
        assert(indices.size() == indicesNum);

        IDirect3DVertexBuffer9 *vertexBuffer = 
          createAndFillVertexBuffer(device, (void *)&(vertices[0]), sizeof(vertex_type) * verticesNum, vertexFormat);
        if (!vertexBuffer)
          return 0;

        IDirect3DIndexBuffer9 *indexBuffer = 
          createAndFillIndexBuffer(device, (void *)&(indices[0]), sizeof(index_type) * indicesNum, indexFormat);
        if (!indexBuffer)
        {
          vertexBuffer->Release();
          return 0;
        }

        return new XSurface(device, vertexBuffer, indexBuffer, vertexFormat, sizeof(vertex_type),
                verticesNum, primitiveType, primitiveCount);
      }
    };

    namespace plane_generator
    {
      struct vertex
      {
        D3DXVECTOR3 operator () ( double u, double v )
        {
          return D3DXVECTOR3((float)(u - 0.5), (float)(v - 0.5), 0);
        }
      };

      struct normal
      {
        D3DXVECTOR3 operator () ( double u, double v )
        {
          return D3DXVECTOR3(0, 0, 1);
        }
      };
    } // End of namespace 'plane_generator'

    namespace torus_generator
    {
      struct vertex
      {
        vertex( double outerR, double innerR )
          : m_outerR(outerR)
          , m_innerR(innerR)
        {
        }

        D3DXVECTOR3 operator () ( double u, double v )
        {
          double const phi   = -v * 2.0 * constants::pi;
          double const theta = -u * 2.0 * constants::pi;

          double const x = (m_outerR + m_innerR * cos(phi)) * cos(theta);
          double const y = (m_outerR + m_innerR * cos(phi)) * sin(theta);
          double const z = m_innerR * sin(phi);

          return D3DXVECTOR3((float)x, (float)y, (float)z);
        }

      private:
        double m_outerR;
        double m_innerR;
      };

      struct normal
      {
        D3DXVECTOR3 operator () ( double u, double v )
        {
          double const phi   = -v * 2.0 * constants::pi;
          double const theta = -u * 2.0 * constants::pi;

          double const x = cos(phi) * cos(theta);
          double const y = cos(phi) * sin(theta);
          double const z = sin(phi);

          return D3DXVECTOR3((float)x, (float)y, (float)z);
        }
      };
    } // End of namespace 'torus_generator'

    namespace color_generator
    {
      struct yuv
      {
        yuv( double y = 1.0 )
          : m_y(util::clamp(0.0, 1.0)(y))
        {
        }

        DWORD operator () ( double u, double v )
        {
          // By some formula from 
          // http://en.wikipedia.org/wiki/YUV
          int const r = (int)(255 * util::clamp<double>()(m_y + 1.402 * (v - 0.5)));
          int const g = (int)(255 * util::clamp<double>()(m_y - 0.344 * (u - 0.5) - 0.714 * (v - 0.5)));
          int const b = (int)(255 * util::clamp<double>()(m_y + 1.772 * (u - 0.5)));

          return D3DCOLOR_ARGB(255, r, g, b);
        }

      private:
        double m_y;
      };

      struct chessboard
      {
        chessboard( size_t uCells = 2, size_t vCells = 2 )
          : m_uCells(uCells)
          , m_vCells(vCells)
        {
          assert(m_uCells > 0);
          assert(m_vCells > 0);
        }

        DWORD operator () ( double u, double v )
        {
          if (((int)(u * m_uCells) + (int)(v * m_vCells)) % 2 == 0)
            return constants::color::black();
          else
            return constants::color::white();
        }

      private:
        size_t m_uCells;
        size_t m_vCells;
      };
    };

    template< class G >
    class ScaleColorSpace
    {
    public:
      ScaleColorSpace( G generator, double uFactor, double vFactor )
        : m_generator(generator)
        , m_uFactor(uFactor)
        , m_vFactor(vFactor)
      {
        assert(m_uFactor > 0);
        assert(m_vFactor > 0);
      }

      DWORD operator () ( double u, double v ) 
      {
        return m_generator(fmod(u, m_uFactor) / m_uFactor, fmod(v, m_vFactor) / m_vFactor);
      }

    private:
      G m_generator;
      double m_uFactor;
      double m_vFactor;
    };

    template< class ColorGenerator >
    inline XSurface * createPlane( IDirect3DDevice9 *device, size_t nX, size_t nY, 
      ColorGenerator colorGen )
    {
      return XSurface::create(device, nX, nY, 
        plane_generator::vertex(), plane_generator::normal(), colorGen);
    }

    inline XSurface * createPlane( IDirect3DDevice9 *device, size_t nX, size_t nY )
    {
      return createPlane(device, nX, nY, color_generator::yuv());
    }

    template< class ColorGenerator >
    inline XSurface * createTorus( IDirect3DDevice9 *device, double outerR, double innerR, size_t nX, size_t nY,
      ColorGenerator colorGen )
    {
      return XSurface::create(device, nX, nY, 
        torus_generator::vertex(outerR, innerR), torus_generator::normal(), colorGen);
    }

    inline XSurface * createTorus( IDirect3DDevice9 *device, double outerR, double innerR, size_t nX, size_t nY )
    {
      return createTorus(device, outerR, innerR, nX, nY, color_generator::yuv());
    }
  } // End of namespace 'xsurface'

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
        constants::color::red(), constants::color::red()));
      xline_ptr_type yAxis(XLine::create(device, 
        D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 1, 0), 
        constants::color::green(), constants::color::green()));
      xline_ptr_type zAxis(XLine::create(device, 
        D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 1), 
        constants::color::blue(), constants::color::blue()));

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
