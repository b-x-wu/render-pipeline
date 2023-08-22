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

inline bool operator==(const Vertex &v1, const Vertex &v2)
{
  return v1.position == v2.position && v1.color == v2.color && v1.normal == v2.normal;
}

#endif
