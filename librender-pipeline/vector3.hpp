#ifndef VECTOR3_H
#define VECTOR3_H

struct Vector3 {
  double values[3];
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
  const double magnitude();
  const double sqr_magnitude();
  Vector3 normalize();
};

Vector3 operator+(const Vector3 &lhs, const Vector3 &rhs);

Vector3 operator-(const Vector3 &lhs, const Vector3 &rhs);

Vector3 operator*(const double &lhs, const Vector3 &rhs);

bool operator==(const Vector3 &lhs, const Vector3 &rhs);

bool operator!=(const Vector3 &lhs, const Vector3 &rhs);

double dot(const Vector3 &lhs, const Vector3 &rhs);

Vector3 cross(const Vector3 &lhs, const Vector3 &rhs);

#endif
