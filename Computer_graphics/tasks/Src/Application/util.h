// util.h
// Utilities.
// Vladimir Rutsky, 4057/2
// 10.02.2010

#ifndef UTIL_H
#define UTIL_H

#include <cassert>

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
} // End of namespace 'util'

#endif // UTIL_H
