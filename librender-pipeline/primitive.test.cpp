#include <assert.h>

#include "primitive.hpp"

void test_primitive_equality()
{
  Primitive point1 = Primitive({ 1, 1, 1 });
  Primitive point2 = Primitive({ 1, 1, 1 });

  assert(point1 == point2);

  Primitive line1 = Primitive({ 1, 1, 1 }, { 1, 2, 3 });
  Primitive line2 = Primitive({ 1, 2, 3 }, { 1, 1, 1 });

  assert(line1 == line2);

  Primitive triangle1 = Primitive({ 1, 1, 1 }, { 1, 2, 3 }, { 3, 2, 1});
  Primitive triangle2 = Primitive({ 1, 2, 3 }, { 1, 1, 1 }, { 3, 2, 1});
  Primitive triangle3 = Primitive({ 3, 2, 1 }, { 1, 2, 3 }, { 3, 2, 1});

  assert(triangle1 == triangle2);
  assert(!(triangle1 == triangle3));

  assert(!(point1 == triangle1));
}

int main()
{
  test_primitive_equality();
}