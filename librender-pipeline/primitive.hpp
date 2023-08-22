#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "vertex.hpp"

enum PRIMITIVE_TYPE
{
  POINT = 1,
  LINE = 2,
  TRIANGLE = 3,
};

struct Primitive
{
  PRIMITIVE_TYPE type;
  Vertex vertices[3];
  Primitive(const Vertex &v1) : type(POINT) { vertices[0] = v1; };
  Primitive(const Vertex &v1, const Vertex &v2) : type(LINE) { vertices[0] = v1; vertices[1] = v2; };
  Primitive(const Vertex &v1, const Vertex &v2, const Vertex &v3) : type(TRIANGLE) { vertices[0] = v1; vertices[1] = v2; vertices[2] = v3; };
};

bool operator==(const Primitive &p1, const Primitive &p2);

#endif
