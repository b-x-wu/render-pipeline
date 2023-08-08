#ifndef VECTOR3_H
#define VECTOR3_H

struct Vector3 {
  double values[3];
  double get_x()
  {
    return values[0];
  }
  double get_y()
  {
    return values[1];
  }
  double get_z()
  {
    return values[2];
  }
};

Vector3 operator+(const Vector3 &lhs, const Vector3 &rhs);

Vector3 operator-(const Vector3 &lhs, const Vector3 &rhs);

template <typename U = double>
Vector3 operator*(const U &lhs, const Vector3 &rhs);

bool operator==(const Vector3 &lhs, const Vector3 &rhs);

bool operator!=(const Vector3 &lhs, const Vector3 &rhs);

double magnitude(const Vector3 &v);

double sqr_magnitude(const Vector3 &v);

Vector3 normalize(Vector3 &v);

double dot(const Vector3 &lhs, const Vector3 &rhs);

Vector3 cross(const Vector3 &lhs, const Vector3 &rhs);

#endif
