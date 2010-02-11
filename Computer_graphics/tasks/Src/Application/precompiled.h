// precompiled.h
// Precompiled header.
// Vladimir Rutsky, 4057/2
// 10.02.2010

// Warning: '...': inherits '...' via dominance
#pragma warning( disable : 4250 )

#ifndef NDEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif // NDEBUG
