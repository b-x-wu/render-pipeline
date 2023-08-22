#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "vector3.hpp"

using Point = Vector3;

// implicit equation for the plane: f(p) = <normal, p> + offset = 0
// for bounding planes, consider f(p) < 0 to be "inside" and f(p) > 0 to be "outside"
struct Plane
{
  Vector3 normal; // points "outward"
  double offset;
};

inline bool is_bounded(Point p, Plane* bounding_planes, int bound_count)
{
  for (int i = 0; i < bound_count; i++)
  {
    if (dot(p, bounding_planes[i].normal) + bounding_planes[i].offset > 0)
    {
      return false;
    } 
  }
  return true;
}

inline bool is_bounded(Point p, Plane bounding_plane)
{
  return dot(bounding_plane.normal, p) + bounding_plane.offset <= 0;
}

#endif
