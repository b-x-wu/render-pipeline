#ifndef FRAGMENT_H
#define FRAGMENT_H

#include "stdint.h"
#include "color.hpp"
#include "vector3.hpp"
#include "geometry.hpp"

struct Fragment
{
  int screen_x_idx;
  int screen_y_idx;
  // double screen_x_offset; // proportional horizontal distance from center of pixel (in [-.5, .5))
  // double screen_y_offset; // proportional vertical distance from center of pixel (in [-.5, .5))
  double depth;
  Color color;
  Vector3 normal;

  Fragment() {}
  
  Fragment(int screen_x_idx, int screen_y_idx, double depth, Color color, Vector3 normal)
  {
    this->screen_x_idx = screen_x_idx;
    this->screen_y_idx = screen_y_idx;
    this->depth = depth;
    this->color = color;
    this->normal = normal;
  }
};

#endif
