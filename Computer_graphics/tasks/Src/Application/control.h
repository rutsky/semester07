// control.h
// User control.
// Vladimir Rutsky, 4057/2
// 10.02.2010

#ifndef CONTROL_H
#define CONTROL_H

#include <vector>

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

  template< class U, class V >
  class CombineControlHandlers
    : public U
    , public V
    , public virtual IControlHandler
  {
    // IControlHandler
  public:
    bool handleMessage( unsigned int message, int wParam, long lParam )
    {
      return 
        U::handleMessage(message, wParam, lParam) || 
        V::handleMessage(message, wParam, lParam);
    }
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
    }

    // IOnMouseWheelHandler
  public:
    virtual bool onMouseWheel( int zDelta, int keys )
    {
      return false;
    }
  };

  class BaseMouseControl
    : public CombineControlHandlers<BaseMouseMoveControl, BaseMouseWheelControl>
  {
  };

  class IOnKeyDownHandler
  {
  public:
    bool onKeyDown( int key, long lParam );
    ~IOnKeyDownHandler() {}
  };

  class BaseOnKeyDownHandler
    : public virtual DummyControlHandler
    , public virtual IOnKeyDownHandler
  {
    // IControlHandler
  public:
    virtual bool handleMessage( unsigned int message, int wParam, long lParam )
    {
      if (message == WM_KEYDOWN)
        return onKeyDown(wParam, lParam);

      return false; 
    }

    // IOnKeyDownHandler
  public:
    virtual bool onKeyDown( int key, long lParam )
    {
      return false;
    }
  };

  /*
  class IOnSpecifiedKeyDownHandler
  {
  public:
    bool onSpecifiedKeyDown( long lParam );
    ~IOnSpecifiedKeyDownHandler() {}
  };

  template< int specifiedKey >
  class OnSpecifiedKeyDown
    : public BaseOnKeyDownHandler
    , public IOnSpecifiedKeyDownHandler
  {
    // IOnKeyDownHandler
  public:
    bool onKeyDown( int key, long lParam )
    {
      if (key == specifiedKey)
        return onSpecifiedKeyDown(lParam);
      return false;
    }
  };
  */

  template< class T, int key >
  class SwitchByKey
    : public BaseOnKeyDownHandler
  {
  public:
    SwitchByKey()
      : m_initialized(false)
      , m_key(key)
      , m_index(0)
    {
    }

    void init( T *var, T val0, T val1 )
    {
      m_var = var;
      m_values.push_back(val0);
      m_values.push_back(val1);

      m_initialized = true;
    }

    void init( T *var, T val0, T val1, T val2 )
    {
      m_var = var;
      m_values.push_back(val0);
      m_values.push_back(val1);
      m_values.push_back(val2);

      m_initialized = true;
    }

    void init( T *var, T val0, T val1, T val2, T val3 )
    {
      m_var = var;
      m_values.push_back(val0);
      m_values.push_back(val1);
      m_values.push_back(val2);
      m_values.push_back(val3);

      m_initialized = true;
    }

    // IOnKeyDownHandler
  public:
    bool onKeyDown( int key, long lParam )
    {
      assert(m_initialized);

      if (key == m_key)
      {
        m_index = (m_index + 1) % m_values.size();
        *m_var = m_values[m_index];
        return true;
      }
      return false;
    }

  private:
    bool m_initialized;
    int m_key;
    T *m_var;
    size_t m_index;
    std::vector<T> m_values;
  };
} // End of namespace 'control'

#endif // CONTROL_H
