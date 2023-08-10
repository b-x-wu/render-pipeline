#ifndef VERTEX_H
#define VERTEX_H

#include "vector3.hpp"
#include "color.hpp"

struct Vertex
{
  Vector3 position; // in world space
  Color color;
  Vector3 normal;
};

#endif
