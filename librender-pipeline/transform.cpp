#include "transform.hpp"
#include <iostream>

bool operator==(const Transform &lhs, const Transform &rhs)
{
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      if (lhs.values[i][j] != rhs.values[i][j])
      {
        return false;
      }
    }
  }
  return true;
}

bool operator!=(const Transform &lhs, const Transform &rhs)
{
  return !(lhs == rhs);
}

Transform operator*(const Transform &lhs, const Transform &rhs)
{
  Transform product = Transform();
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      product.values[i][j] = lhs.values[i][0] * rhs.values[0][j] + lhs.values[i][1] * rhs.values[1][j] + lhs.values[i][2] * rhs.values[2][j] + lhs.values[i][3] * rhs.values[3][j];
    }
  }
  return product;
}

HVector operator*(const Transform &lhs, const HVector &rhs)
{
  return (HVector) {
    lhs.values[0][0] * rhs.values[0] + lhs.values[0][1] * rhs.values[1] + lhs.values[0][2] * rhs.values[2] + lhs.values[0][3] * rhs.values[3],
    lhs.values[1][0] * rhs.values[0] + lhs.values[1][1] * rhs.values[1] + lhs.values[1][2] * rhs.values[2] + lhs.values[1][3] * rhs.values[3],
    lhs.values[2][0] * rhs.values[0] + lhs.values[2][1] * rhs.values[1] + lhs.values[2][2] * rhs.values[2] + lhs.values[2][3] * rhs.values[3],
    lhs.values[3][0] * rhs.values[0] + lhs.values[3][1] * rhs.values[1] + lhs.values[3][2] * rhs.values[2] + lhs.values[3][3] * rhs.values[3],
  };
}
