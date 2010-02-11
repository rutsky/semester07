// precompiled.cpp
// File for generating precompiled header files.
// Vladimir Rutsky, 4057/2
// 12.02.2010

#include "precompiled.h"

#include <vector>
#include <cassert>
#include <ostream>
#include <sstream>

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>

#include <windows.h>
#include <windowsx.h>

#include <d3d9.h>
#include <d3d9types.h>
#include <d3dx9math.h>
