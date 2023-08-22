#include "primitive.hpp"

bool line_equality(const Primitive &line1, const Primitive &line2)
{
  Vertex ordered_verticies1[2];
  Vertex ordered_verticies2[2];

  if (line1.vertices[0].position < line1.vertices[1].position)
  {
    ordered_verticies1[0] = line1.vertices[0];
    ordered_verticies1[1] = line1.vertices[1];
  }
  else
  {
    ordered_verticies1[0] = line1.vertices[1];
    ordered_verticies1[1] = line1.vertices[0];
  }

  if (line2.vertices[0].position < line2.vertices[1].position)
  {
    ordered_verticies2[0] = line2.vertices[0];
    ordered_verticies2[1] = line2.vertices[1];
  }
  else
  {
    ordered_verticies2[0] = line2.vertices[1];
    ordered_verticies2[1] = line2.vertices[0];
  }

  return (ordered_verticies1[0] == ordered_verticies2[0]) && (ordered_verticies1[1] == ordered_verticies2[1]);
}

bool triangle_equality(const Primitive &triangle1, const Primitive &triangle2)
{
  Vertex smallest_vertex1 = triangle1.vertices[0];
  Vertex medium_vertex1 = triangle1.vertices[1];
  Vertex largest_vertex1 = triangle1.vertices[2];

  if (medium_vertex1.position < smallest_vertex1.position)
  {
    std::swap(smallest_vertex1, medium_vertex1);
  }
  if (largest_vertex1.position < smallest_vertex1.position)
  {
    std::swap(smallest_vertex1, largest_vertex1);
  }
  if (largest_vertex1.position < medium_vertex1.position)
  {
    std::swap(medium_vertex1, largest_vertex1);
  }
  
  Vertex smallest_vertex2 = triangle2.vertices[0];
  Vertex medium_vertex2 = triangle2.vertices[1];
  Vertex largest_vertex2 = triangle2.vertices[2];

  if (medium_vertex2.position < smallest_vertex2.position)
  {
    std::swap(smallest_vertex2, medium_vertex2);
  }
  if (largest_vertex2.position < smallest_vertex2.position)
  {
    std::swap(smallest_vertex2, largest_vertex2);
  }
  if (largest_vertex2.position < medium_vertex2.position)
  {
    std::swap(medium_vertex2, largest_vertex2);
  }

  return (smallest_vertex1 == smallest_vertex2) && (medium_vertex1 == medium_vertex2) && (largest_vertex1 == largest_vertex2);
}

bool operator==(const Primitive &p1, const Primitive &p2)
{
  if (p1.type != p2.type)
  {
    return false;
  }
  
  switch (p1.type)
  {
  case POINT:
    return p1.vertices[0] == p2.vertices[0];
    break;
  case LINE:
    return line_equality(p1, p2);
    break;
  case TRIANGLE:
    return triangle_equality(p1, p2);
    break;
  }
  
  return false;
}