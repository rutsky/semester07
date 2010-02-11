// config.h
// Configuration constants.
// Vladimir Rutsky, 4057/2
// 09.02.2010

#ifndef CONFIG_H
#define CONFIG_H

#include "constants.h"

namespace config
{
  double const keyboardTranslationSpeed = 2.0;
  double const mouseRotationSpeedX = 2 * constants::pi / 400.0;
  double const mouseRotationSpeedY = 2 * constants::pi / 400.0;
} // End of namespace 'config'

#endif // CONFIG_H
