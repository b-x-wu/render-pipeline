#include "vector3.hpp"
#include <iostream>
#include <assert.h>

// TODO: create a test suite class

void test_operator_plus() {
  Vector3 lhs = { 1.0, 2.0, 3.0 };
  Vector3 rhs = { 2.0, 3.0, 4.0 };
  Vector3 actual = lhs + rhs;
  Vector3 expected = { 3.0, 5.0, 7.0 };

  assert(actual == expected);
}

void test_operator_minus() {
  Vector3 lhs = { 1.0, 2.0, 3.0 };
  Vector3 rhs = { 2.0, 3.0, 4.0 };
  Vector3 actual = lhs - rhs;
  Vector3 expected = { -1.0, -1.0, -1.0 };

  assert(actual == expected);
}

void test_operator_times() {
  double lhs = 2.0;
  Vector3 rhs = { 1.0, 2.0, 3.0 };
  Vector3 actual = lhs * rhs;
  Vector3 expected = { 2.0, 4.0, 6.0 };

  assert(actual == expected);
}

void test_operator_equivalent() {
  Vector3 lhs = { 1.0, 2.0, 3.0 };
  Vector3 rhs = { 1.0, 2.0, 3.0 };

  assert(lhs == rhs);
}

void test_operator_inequivalent() {
  Vector3 lhs = { 1.0, 2.0, 3.0 };
  Vector3 rhs = { 2.0, 2.0, 3.0 };

  assert(lhs != rhs);
}

void test_magnitude() {
  Vector3 v = { 12.0, 15.0, 16.0 };
  double actual = magnitude(v);
  double expected = 25.0;

  assert(actual == expected);
}

void test_sqr_magnitude() {
  Vector3 v = { 2.0, 3.0, 4.0 };
  double actual = sqr_magnitude(v);
  double expected = 29.0;

  assert(actual == expected);
}

void test_normalize() {
  Vector3 v = { 1.0, 2.0, 2.0 };
  Vector3 actual = normalize(v);
  Vector3 expected = { 1.0 / 3.0, 2.0 / 3.0, 2.0 / 3.0 };

  assert(actual == expected);
  assert(v == expected);
}

void test_dot() {
  Vector3 lhs = { 1.0, 2.0, 3.0 };
  Vector3 rhs = { 4.0, -5.0, 6.0 };
  double actual = dot(lhs, rhs);
  double expected = 12.0;

  assert(actual == expected);
}

void test_cross() {
  Vector3 lhs = { 3.0, -3.0, 1.0 };
  Vector3 rhs = { 4.0, 9.0, 2.0 };
  Vector3 actual = cross(lhs, rhs);
  Vector3 expected = { -15.0, -2.0, 39.0 };

  assert(actual == expected);
}

void test_componentwise_get() {
  Vector3 v = { 1.0, 2.0, 3.0 };

  assert(v.get_x() == 1.0);
  assert(v.get_y() == 2.0);
  assert(v.get_z() == 3.0);
}

int main() {
  test_operator_plus();
  test_operator_minus();
  test_operator_times();
  test_operator_equivalent();
  test_operator_inequivalent();
  test_magnitude();
  test_sqr_magnitude();
  test_normalize();
}
