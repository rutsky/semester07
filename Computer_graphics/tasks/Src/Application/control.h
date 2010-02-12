// control.h
// User control.
// Vladimir Rutsky, 4057/2
// 10.02.2010

#ifndef CONTROL_H
#define CONTROL_H

#include <windows.h>
#include <windowsx.h>

namespace control
{
  class IControlHandler
  {
  public:
    virtual bool handleMessage( unsigned int message, int wParam, long lParam ) = 0;
    virtual ~IControlHandler() {}
  };

  class DummyControlHandler
    : public virtual IControlHandler
  {
    // IControlHandler
  public:
    virtual bool handleMessage( unsigned int message, int wParam, long lParam )
    {
      return false; 
    };
  };
  
  inline bool isKeyDown( int nVirtKey )
  {
    //return (GetAsyncKeyState(nVirtKey) & 0x80) != 0;
    return (GetKeyState(nVirtKey) & 0x80) != 0;
  }

  class IOnMouseMoveHandler
  {
  public:
    virtual bool onMouseMove( int dx, int dy, int keys ) = 0;
    ~IOnMouseMoveHandler() {}
  };

  class BaseMouseMoveControl
    : public virtual IOnMouseMoveHandler
    , public virtual DummyControlHandler
  {
  public:
    BaseMouseMoveControl()
      : m_firstMessage(true)
    {
    }

    // IControlHandler
  public:
    virtual bool handleMessage( unsigned int message, int wParam, long lParam )
    {
      if (message == WM_MOUSEMOVE)
      {
        int const keys = GET_KEYSTATE_WPARAM(wParam);

        int const prevMousePosX = m_mousePosX;
        int const prevMousePosY = m_mousePosY;

        m_mousePosX = GET_X_LPARAM(lParam); 
        m_mousePosY = GET_Y_LPARAM(lParam);

        int dx, dy;
        if (m_firstMessage)
        {
          dx = dy = 0;
          m_firstMessage = false;
        }
        else
        {
          dx = m_mousePosX - prevMousePosX;
          dy = m_mousePosY - prevMousePosY;
        }
        return onMouseMove(dx, dy, keys);
      }

      return false; 
    };

    // IOnMouseMoveHandler
  public:
    virtual bool onMouseMove( int dx, int dy, int keys )
    {
      return false;
    }

  protected:
    // Mouse position is relative to upper-left corner of the client area.
    int m_mousePosX, m_mousePosY;

  private:
    bool m_firstMessage;
  };

  class IOnMouseWheelHandler
  {
  public:
    virtual bool onMouseWheel( int zDelta, int keys ) = 0;
    ~IOnMouseWheelHandler() {}
  };

  class BaseMouseWheelControl
    : public virtual IOnMouseWheelHandler
    , public virtual IControlHandler
  {
    // IControlHandler
  public:
    virtual bool handleMessage( unsigned int message, int wParam, long lParam )
    {
      if (message == WM_MOUSEWHEEL)
      {
        int keys = GET_KEYSTATE_WPARAM(wParam);
        int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);

        return onMouseWheel(zDelta / 120, keys);
      }

      return false; 
    };

    // IOnMouseWheelHandler
  public:
    virtual bool onMouseWheel( int zDelta, int keys )
    {
      return false;
    }
  };

  class BaseMouseControl
    : public BaseMouseMoveControl
    , public BaseMouseWheelControl
  {
    // IControlHandler
  public:
    virtual bool handleMessage( unsigned int message, int wParam, long lParam )
    {
      return BaseMouseMoveControl::handleMessage(message, wParam, lParam) ||
          BaseMouseWheelControl::handleMessage(message, wParam, lParam);
    }
  };
} // End of namespace 'control'

#endif // CONTROL_H
