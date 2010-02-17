// config.cpp
// User control.
// Vladimir Rutsky, 4057/2
// 10.02.2010

#include "precompiled.h"

#include "config.h"
#include "constants.h"

namespace config
{
  extern double const keyboardTranslationSpeed = 13.0;
  extern double const keyboardRotationSpeed = 2 * constants::pi / 1.5;
  extern double const centerMouseRotationSpeedX = 2 * constants::pi / 400.0;
  extern double const centerMouseRotationSpeedY = 2 * constants::pi / 400.0;
  extern double const freeViewMouseRotationSpeedX = 2 * constants::pi / 500.0;
  extern double const freeViewMouseRotationSpeedY = 2 * constants::pi / 500.0;
  extern double const mouseWheelZoomFactor = 1.1;
} // End of namespace 'config'
