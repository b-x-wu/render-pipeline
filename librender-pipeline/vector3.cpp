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

Vector3 operator*(const double &lhs, const Vector3 &rhs)
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

const double Vector3::magnitude()
{
  return sqrt(this->values[0] * this->values[0] + this->values[1] * this->values[1] + this->values[2] * this->values[2]);
}

const double Vector3::sqr_magnitude()
{
  return this->values[0] * this->values[0] + this->values[1] * this->values[1] + this->values[2] * this->values[2];
}

Vector3 Vector3::normalize()
{
  double magnitude = this->magnitude();
  this->values[0] /= magnitude;
  this->values[1] /= magnitude;
  this->values[2] /= magnitude;
  return *this;
}

double dot(const Vector3 &lhs, const Vector3 &rhs)
{
  return lhs.values[0] * rhs.values[0] + lhs.values[1] * rhs.values[1] + lhs.values[2] * rhs.values[2];
}

Vector3 cross(const Vector3 &lhs, const Vector3 &rhs)
{
  return { lhs.values[1] * rhs.values[2] - lhs.values[2] * rhs.values[1], lhs.values[2] * rhs.values[0] - lhs.values[0] * rhs.values[2], lhs.values[0] * rhs.values[1] - lhs.values[1] * rhs.values[0] };
}
