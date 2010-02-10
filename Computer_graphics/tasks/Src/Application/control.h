// control.h
// User control.
// Vladimir Rutsky, 4057/2
// 10.02.2010

#include <windows.h>

#include "cs.h"
#include "object.h"
#include "config.h"

namespace control
{
  class IControlHandler
  {
  public:
    virtual bool handleMessage( unsigned int message, int wParam, long lParam )
    {
      return false; 
    };

    virtual ~IControlHandler() {}
  };

  inline bool isKeyDown( int nVirtKey )
  {
    return (GetAsyncKeyState(nVirtKey) & 0x80) != 0;
  }

  class LCSArrowPgUpPgDownMove
    : public virtual IControlHandler
    , public cs::BaseCoordinateSystem
    , public object::BaseDynamicObject
  {
    // IDynamicObject
  public:
    void update( double time )
    {
      object::BaseDynamicObject::update(time);

      D3DXMATRIX translation;
      float const distance = (float)(config::keyboardTranslationSpeed * dtime());

      if (isKeyDown(VK_UP))
      {
        D3DXMatrixTranslation(&translation, 0, distance, 0);
        m_matrix = m_matrix * translation;
      }

      if (isKeyDown(VK_DOWN))
      {
        D3DXMatrixTranslation(&translation, 0, -distance, 0);
        m_matrix = m_matrix * translation;
      }

      if (isKeyDown(VK_LEFT))
      {
        D3DXMatrixTranslation(&translation, -distance, 0, 0);
        m_matrix = m_matrix * translation;
      }

      if (isKeyDown(VK_RIGHT))
      {
        D3DXMatrixTranslation(&translation, distance, 0, 0);
        m_matrix = m_matrix * translation;
      }

      if (isKeyDown(VK_PRIOR)) // Page Up
      {
        D3DXMatrixTranslation(&translation, 0, 0, distance);
        m_matrix = m_matrix * translation;
      }

      if (isKeyDown(VK_NEXT)) // Page Down
      {
        D3DXMatrixTranslation(&translation, 0, 0, -distance);
        m_matrix = m_matrix * translation;
      }
    }
  };
} // End of namespace 'control'
