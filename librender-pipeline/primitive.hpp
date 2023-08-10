#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "vertex.hpp"

enum PRIMITIVE_TYPE
{
  POINT, LINE, TRIANGLE
};

struct Primitive
{
  PRIMITIVE_TYPE type;
  Vertex vertices[3];
  Primitive(const Vertex &v1) : type(POINT) { vertices[0] = v1; };
  Primitive(const Vertex &v1, const Vertex &v2) : type(LINE) { vertices[0] = v1; vertices[1] = v2; };
  Primitive(const Vertex &v1, const Vertex &v2, const Vertex &v3) : type(TRIANGLE) { vertices[0] = v1; vertices[1] = v2; vertices[2] = v3; };
};

#endif
