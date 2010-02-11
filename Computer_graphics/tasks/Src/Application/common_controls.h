// common_controls.h
// Common controls.
// Vladimir Rutsky, 4057/2
// 11.02.2010

#ifndef COMMON_CONTROLS_H
#define COMMON_CONTROLS_H

#include "control.h"

#include "cs.h"
#include "object.h"
#include "config.h"

namespace control
{
  class LCSArrowPgUpPgDownMove
    : public virtual cs::BaseCoordinateSystem
    , public virtual object::BaseDynamicObject
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

#endif // COMMON_CONTROLS_H
