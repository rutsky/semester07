// light.h
// Lights.
// Vladimir Rutsky, 4057/2
// 18.02.2010

#ifndef LIGHT_H
#define LIGHT_H

#include <d3d9.h>
#include <d3d9types.h>
#include <d3dx9math.h>

#include "constants.h"
#include "cs.h"

namespace light
{
  class ILight
  {
  public:
    virtual D3DLIGHT9 light() const = 0;

    ~ILight() {}
  };

  namespace details
  {
    class BaseLight
      : public ILight
    {
    public:
      BaseLight()
      {
        memset((void *)&m_light, 0, sizeof(m_light));
      }

      // ILight
    public:
      D3DLIGHT9 light() const
      {
        return m_light;
      }
      
    protected:
      D3DLIGHT9 m_light;
    };

    class TypeProperty
      : public virtual BaseLight
    {
    public:
      TypeProperty( D3DLIGHTTYPE type )
      {
        m_light.Type = type;
      }
    };

    class MaterialProperty
      : public virtual BaseLight
    {
    public:
      MaterialProperty()
      {
        m_light.Ambient = constants::color::white();
        m_light.Diffuse = constants::color::white();
        m_light.Specular = constants::color::white();
      }

    public:
      void setDiffuse( D3DXCOLOR const &ambient, D3DXCOLOR const &diffuse, D3DXCOLOR const &specular )
      {
        m_light.Ambient = ambient;
        m_light.Diffuse = diffuse;
        m_light.Specular = specular;
      }
    };

    class PositionProperty
      : public virtual BaseLight
    {
    public:
      PositionProperty()
      {
        m_light.Position = D3DXVECTOR3(0, 0, 0);
      }

    public:
      void setPosition( D3DXVECTOR3 const &pos )
      {
        m_light.Position = pos;
      }
    };

    class DirectionProperty
      : public virtual BaseLight
    {
    public:
      DirectionProperty()
      {
        m_light.Direction = D3DXVECTOR3(0, 0, -30);
      }

    public:
      void setDirection( D3DXVECTOR3 const &dir )
      {
        m_light.Direction = dir;
      }
    };

    class RangeProperty
      : public virtual BaseLight
    {
    public:
      RangeProperty()
      {
        m_light.Range = 1000.0f;
      }

    public:
      void setRange( float range )
      {
        m_light.Range = range;
      }
    };

    class FalloffProperty
      : public virtual BaseLight
    {
    public:
      FalloffProperty()
      {
        m_light.Falloff = 1.0f;
      }

    public:
      void setFalloff( float falloff )
      {
        m_light.Falloff = falloff;
      }
    };

    class AttenuationProperty
      : public virtual BaseLight
    {
    public:
      AttenuationProperty()
      {
        m_light.Attenuation0 = 0.0f;
        m_light.Attenuation1 = 0.1f;
        m_light.Attenuation2 = 0.0f;
      }

    public:
      void setAttenuation( float a0, float a1, float a2 )
      {
        m_light.Attenuation0 = a0;
        m_light.Attenuation1 = a1;
        m_light.Attenuation2 = a2;
      }
    };

    class AnglesProperty
      : public virtual BaseLight
    {
    public:
      AnglesProperty()
      {
        m_light.Theta = (float)(2.0 * constants::pi / 3.0);
        m_light.Phi = (float)(constants::pi / 3.0);
      }

    public:
      void setAttenuation( float a0, float a1, float a2 )
      {
        m_light.Attenuation0 = a0;
        m_light.Attenuation1 = a1;
        m_light.Attenuation2 = a2;
      }
    };
  } // End of namespace 'details'
  
  class DirectionLight
    : public details::TypeProperty
    , public details::MaterialProperty
    , public details::DirectionProperty
  {
  public:
    DirectionLight()
      : details::TypeProperty(D3DLIGHT_DIRECTIONAL)
    {
    }
  };

  class PointLight
    : public details::TypeProperty
    , public details::MaterialProperty
    , public details::PositionProperty
    , public details::RangeProperty
    , public details::AttenuationProperty
  {
  public:
    PointLight()
      : details::TypeProperty(D3DLIGHT_POINT)
    {
    }
  };

  class SpotLight
    : public details::TypeProperty
    , public details::MaterialProperty
    , public details::PositionProperty
    , public details::DirectionProperty
    , public details::RangeProperty
    , public details::AttenuationProperty
    , public details::AnglesProperty
    , public details::FalloffProperty
  {
  public:
    SpotLight()
      : details::TypeProperty(D3DLIGHT_SPOT)
    {
    }
  };
} // End of namespace 'light'

#endif // LIGHT_H
