#ifndef __CGLTIMER_H__645353535354375000
#define __CGLTIMER_H__645353535354375000

/**
  @file     cglTimer.h
  @brief    Simple high resolution timer
  @date     Created on 11/09/2006
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

// *******************************************************************
// defines

// *******************************************************************
// class

class cglTimer
{
public:
  cglTimer();
  
  void update();
  float getDelta() const { return m_rDelta; }
  float getTime() const { return m_rTime; }

private:
  /// Unsigned 64-bit integer
  #if defined (_MSC_VER)
    typedef unsigned __int64  UInt64;
  #else
    typedef unsigned long int UInt64;
  #endif

  float getCurTime();
  
  UInt64 m_freq;
  float  m_rPrevTime;
  float  m_rTime;
  float  m_rDelta;
};

#endif //__CGLTIMER_H__632619820234375000
