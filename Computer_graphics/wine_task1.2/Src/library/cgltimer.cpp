/**
  @file     cglTimer.cpp
  @brief    Simple high resolution timer
  @date     Created on 11/09/2006
  @project  D3DBase
  @author   Bvs
*/
// *******************************************************
// compiler specific

// *******************************************************************
// includes
#include <windows.h>

// this system
#include "cgltimer.h"

// *******************************************************************
// defines & constants

// *******************************************************************
// static data

// *******************************************************************
// methods 

cglTimer::cglTimer()
  : m_rTime(0.0f)
  , m_rDelta(0.0f)
{
  QueryPerformanceFrequency((LARGE_INTEGER*)&m_freq);
  m_rPrevTime = getCurTime();
}

float cglTimer::getCurTime()
{
  UInt64 time;
  QueryPerformanceCounter((LARGE_INTEGER*)&time);
  //return float(double(time) / double(m_freq));
  // FIXME: Strange fail is going above!
  float t = float(double(time) / double(m_freq));
  return t;
}

void cglTimer::update()
{
  float rCurTime = getCurTime();
  m_rDelta = rCurTime - m_rPrevTime;
  m_rTime += m_rDelta;
  m_rPrevTime = rCurTime;
}
