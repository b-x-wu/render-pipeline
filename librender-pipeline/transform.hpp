#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "hvector.hpp"

struct Transform {
  double values[4][4];
  Transform() {}
  Transform(double values[4][4])
  {
    for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j < 4; j++)
      {
        this->values[i][j] = values[i][j];
      }
    }
  }
};

bool operator==(const Transform &lhs, const Transform &rhs);

bool operator!=(const Transform &lhs, const Transform &rhs);

Transform operator*(const Transform &lhs, const Transform &rhs);

HVector operator*(const Transform &lhs, const HVector &rhs);

#endif
