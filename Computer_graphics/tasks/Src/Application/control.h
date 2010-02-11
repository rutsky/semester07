// control.h
// User control.
// Vladimir Rutsky, 4057/2
// 10.02.2010

#ifndef CONTROL_H
#define CONTROL_H

#include <windows.h>

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
    //return (GetAsyncKeyState(nVirtKey) & 0x80) != 0;
    return (GetKeyState(nVirtKey) & 0x80) != 0;
  }
} // End of namespace 'control'

#endif // CONTROL_H
