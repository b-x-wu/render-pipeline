#include "vector3.hpp"
#include <math.h>

Vector3 operator+(const Vector3 &lhs, const Vector3 &rhs)
{
  return { lhs.values[0] + rhs.values[0], lhs.values[1] + rhs.values[1], lhs.values[2] + rhs.values[2] };
}

Vector3 operator-(const Vector3 &lhs, const Vector3 &rhs)
{
  return { lhs.values[0] - rhs.values[0], lhs.values[1] - rhs.values[1], lhs.values[2] - rhs.values[2] };
}

template <typename U>
Vector3 operator*(const U& lhs, const Vector3& rhs)
{
  return { lhs * rhs.values[0], lhs * rhs.values[1], lhs * rhs.values[2] };
}

bool operator==(const Vector3 &lhs, const Vector3 &rhs)
{
  return lhs.values[0] == rhs.values[0] && lhs.values[1] == rhs.values[1] && lhs.values[2] == rhs.values[2];
}

bool operator!=(const Vector3 &lhs, const Vector3 &rhs)
{
  return lhs.values[0] != rhs.values[0] || lhs.values[1] != rhs.values[1] || lhs.values[2] != rhs.values[2];
}

double magnitude(const Vector3& v)
{
  return sqrt(v.values[0] * v.values[0] + v.values[1] * v.values[1] + v.values[2] * v.values[2]);
}

double sqr_magnitude(const Vector3& v)
{
  return v.values[0] * v.values[0] + v.values[1] * v.values[1] + v.values[2] * v.values[2];
}

Vector3 normalize(Vector3 &v)
{
  v = (1 / magnitude(v)) * v;
  return v;
}

double dot(const Vector3 &lhs, const Vector3 &rhs)
{
  return lhs.values[0] * rhs.values[0] + lhs.values[1] * rhs.values[1] + lhs.values[2] * rhs.values[2];
}

Vector3 cross(const Vector3 &lhs, const Vector3 &rhs)
{
  return { lhs.values[1] * rhs.values[2] - lhs.values[2] * rhs.values[1], lhs.values[2] * rhs.values[0] - lhs.values[0] * rhs.values[2], lhs.values[0] * rhs.values[1] - lhs.values[1] * rhs.values[0] };
}
