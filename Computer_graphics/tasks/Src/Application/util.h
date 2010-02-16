// util.h
// Utilities.
// Vladimir Rutsky, 4057/2
// 10.02.2010

#ifndef UTIL_H
#define UTIL_H

#include <cassert>

#include "constants.h"

namespace util
{
  template< class T, int N >
  int array_size( T const (&)[N] )
  {
    return N;
  }

  template< class T >
  class com_scoped_ptr
  {
  public:
    explicit com_scoped_ptr( T *p = 0 )
      : m_p(p)
    {
    }

    ~com_scoped_ptr()
    {
      if (m_p)
        m_p->Release;
    }

  public:
    com_scoped_ptr( com_scoped_ptr<T> &other )
    {
      reset(other.get());
      other.m_p = 0;
    }

    com_scoped_ptr<T> & operator = ( com_scoped_ptr<T> &other )
    {
      reset(other.get());
      other.m_p = 0;
      return *this;
    }

  public:
    T operator *()
    {
      assert(m_p);
      return *m_p;
    }

    T * operator -> ()
    {
      assert(m_p);
      return m_p;
    }

    T * get()
    {
      return m_p;
    }

    void reset( T *p )
    {
      if (m_p != 0)
        m_p->Release();
      m_p = p;
    }

    operator bool ()
    {
      return m_p != 0;
    }

  private:
    T *m_p;
  };

  inline double rad2deg( double rad )
  {
    return (rad / constants::pi) * 180.0;
  }

  inline double deg2rad( double deg )
  {
    return (deg / 180.0) * constants::pi;
  }

  template< class T >
  struct clamp_impl
  {
    clamp_impl( T lo, T hi )
      : m_lo(lo)
      , m_hi(hi)
    {
    }

    T operator () ( T v )
    {
      if (v < m_lo)
        return m_lo;
      else if (v > m_hi)
        return m_hi;
      else
        return v;
    }

  private:
    T m_lo, m_hi;
  };

  template< class T >
  inline clamp_impl<T> clamp( T lo, T hi )
  {
    return clamp_impl<T>(lo, hi);
  }

  template< class T >
  inline clamp_impl<T> clamp()
  {
    return clamp_impl<T>(T(0), T(1));
  }

  template< class T >
  inline T sqr( T x )
  {
    return x * x;
  }
} // End of namespace 'util'

#endif // UTIL_H
