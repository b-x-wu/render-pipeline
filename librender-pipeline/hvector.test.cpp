#include "hvector.hpp"
#include <assert.h>
#include <stdexcept>

void test_componentwise_get()
{
  HVector v = { 1.0, 2.0, 3.0, 4.0 };
  
  assert(v.get_x() == 1.0);
  assert(v.get_y() == 2.0);
  assert(v.get_z() == 3.0);
  assert(v.get_w() == 4.0);
}

void test_get_normalized_vector3()
{
  HVector v = { 2.0, 4.0, 6.0, 2.0 };
  Vector3 actual = v.to_vector3();
  Vector3 expected = { 1.0, 2.0, 3.0 };

  assert(actual == expected);
}

void test_normalize()
{
  HVector v = { 2.0, 4.0, 6.0, 2.0 };
  HVector actual = v.normalize();
  HVector expected = { 1.0, 2.0, 3.0, 1.0 };

  assert(actual == expected);
  assert(v == expected);
}

void test_normalize_divide_by_zero_exception()
{
  bool normalize_exception_thrown = false;
  bool get_normalized_vector3_exception_thrown = false;
  HVector v = { 1.0, 1.0, 1.0, 0.0 };
  try
  {
    v.normalize();
  }
  catch (const std::runtime_error& e)
  {
    normalize_exception_thrown = true;
  }

  try
  {
    v.to_vector3();
  }
  catch(const std::runtime_error& e)
  {
    get_normalized_vector3_exception_thrown = true;
  }

  assert(get_normalized_vector3_exception_thrown);
  assert(normalize_exception_thrown);
}

int main()
{
  test_componentwise_get();
  test_get_normalized_vector3();
  test_normalize();
}
