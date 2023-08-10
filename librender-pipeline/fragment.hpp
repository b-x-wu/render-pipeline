#ifndef FRAGMENT_H
#define FRAGMENT_H

#include "stdint.h"
#include "color.hpp"
#include "vector3.hpp"

struct Fragment
{
  Vector3 position; // in screen space
  Color color;
};

#endif
