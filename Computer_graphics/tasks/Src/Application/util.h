// util.h
// Utilities.
// Vladimir Rutsky, 4057/2
// 10.02.2010

namespace util
{
  template< class T, int N >
  int array_size( T const (&)[N] )
  {
    return N;
  }
} // End of namespace 'util'
