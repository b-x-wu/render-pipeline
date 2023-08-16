#ifndef VERTEX_H
#define VERTEX_H

#include "vector3.hpp"
#include "color.hpp"
#include "geometry.hpp"

struct Vertex
{
  Point position; // in world space
  Color color;
  Vector3 normal;
};

#endif
