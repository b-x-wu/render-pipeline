#ifndef VECTOR3_H
#define VECTOR3_H

struct Vector3 {
  double values[3];
  double get_x() const
  {
    return values[0];
  }
  double get_y() const
  {
    return values[1];
  }
  double get_z() const
  {
    return values[2];
  }
  double magnitude() const;
  double sqr_magnitude() const;
  Vector3 normalize();
};

Vector3 operator-(const Vector3 &v);

Vector3 operator+(const Vector3 &lhs, const Vector3 &rhs);

Vector3 operator-(const Vector3 &lhs, const Vector3 &rhs);

Vector3 operator*(const double &lhs, const Vector3 &rhs);

bool operator==(const Vector3 &lhs, const Vector3 &rhs);

bool operator!=(const Vector3 &lhs, const Vector3 &rhs);

double dot(const Vector3 &lhs, const Vector3 &rhs);

Vector3 cross(const Vector3 &lhs, const Vector3 &rhs);

#endif
