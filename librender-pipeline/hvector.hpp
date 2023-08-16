#ifndef HVECTOR_H
#define HVECTOR_H

#include "vector3.hpp"

struct HVector {
  double values[4];
  const double get_x()
  {
    return values[0];
  }
  const double get_y()
  {
    return values[1];
  }
  const double get_z()
  {
    return values[2];
  }
  const double get_w()
  {
    return values[3];
  }
  Vector3 to_vector3();
  HVector normalize();
  static HVector from_vector3(Vector3 &v);
};

bool operator==(const HVector &lhs, const HVector &rhs);

bool operator!=(const HVector &lhs, const HVector &rhs);

#endif