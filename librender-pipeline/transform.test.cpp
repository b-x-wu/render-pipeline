#include "transform.hpp"
#include "hvector.hpp"
#include <assert.h>

void test_operator_equality()
{
  double v1_values[4][4] = {{1,3,5,7},{3,5,7,9},{5,7,9,11},{7,9,11,13}};
  double v2_values[4][4] = {{1,3,5,7},{3,5,7,9},{5,7,9,11},{7,9,11,13}};
  double v3_values[4][4] = {{1,2,3,4},{2,3,4,5},{3,4,5,6},{4,5,6,7}};
  Transform v1 = Transform(v1_values);
  Transform v2 = Transform(v2_values);
  Transform v3 = Transform(v3_values);

  assert(v1 == v2);
  assert(v1 == v1);
  assert(v1 != v3);
  assert(v2 != v3);
}

void test_transform_transform_multiplication()
{
  double lhs_values[4][4] = {{1,2,3,4},{2,3,4,5},{3,4,5,6},{4,5,6,7}};
  Transform lhs = Transform(lhs_values);
  double rhs_values[4][4] = {{1,3,5,7},{3,5,7,9},{5,7,9,11},{7,9,11,13}};
  Transform rhs = Transform(rhs_values);

  Transform actual = lhs * rhs;
  double expected_values[4][4] = {{50,70,90,110},{66,94,122,150},{82,118,154,190},{98,142,186,230}};
  Transform expected = Transform(expected_values);

  assert(actual == expected);
}

void test_transform_hvector_multiplication()
{
  double lhs_values[4][4] = {{1,2,3,4},{2,3,4,5},{3,4,5,6},{4,5,6,7}};
  Transform lhs = Transform(lhs_values);
  HVector rhs = { 1.0, 2.0, 3.0, 4.0 };

  HVector actual = lhs * rhs;
  HVector expected = { 30.0, 40.0, 50.0, 60.0 };

  assert(actual == expected);
}

int main()
{
  test_operator_equality();
  test_transform_hvector_multiplication();
  test_transform_transform_multiplication();
}
