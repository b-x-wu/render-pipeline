#include <assert.h>

#include "color.hpp"
#include "util.hpp"

void test_operator_add()
{
  Color color1 = { 10, 15, 20, 30 };
  Color color2 = { 12, 17, 22, 32 };

  Color actual = color1 + color2;
  Color expected = { 22, 32, 42, 62 };

  assert(actual == expected);
}

void test_operator_add_overflow()
{
  Color color1 = { 255, 255, 255, 255 };
  Color color2 = { 10, 10, 10, 10 };

  Color actual = color1 + color2;
  Color expected = { 255, 255, 255, 255 };

  assert(actual == expected);
}

void test_operator_multiply()
{
  Color color = { 10, 20, 30, 40 };
  double val = 2;

  Color actual = val * color;
  Color expected = { 20, 40, 60, 80 };

  assert(actual == expected);
}

void test_operator_multiply_overflow()
{
  Color color = { 200, 200, 200, 200 };
  double val = 5;

  Color actual = val * color;
  Color expected = { 255, 255, 255, 255 };

  assert(actual == expected);
}

void test_operator_subtract()
{
  Color color1 = { 10, 20, 30, 40 };
  Color color2 = { 5, 10, 15, 20 };

  Color actual = color1 - color2;
  Color expected = { 5, 10, 15, 20 };

  assert(actual == expected);
}

void test_operator_subtract_underflow()
{
  Color color1 = { 5, 5, 10, 10 };
  Color color2 = { 10, 10, 5, 5 };

  Color actual = color1 - color2;
  Color expected = { 0, 0, 5, 5 };

  assert(actual == expected);
}

int main()
{
  test_operator_add();
  test_operator_add_overflow();
  test_operator_multiply();
  test_operator_multiply_overflow();
}
