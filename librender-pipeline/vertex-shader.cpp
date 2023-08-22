#include <assert.h>
#include <iostream>

#include "vertex-shader.hpp"
#include "primitive.hpp"
#include "util.hpp"

void VertexShader::_update_viewport_transform()
{
  double viewport_transform_values[4][4] = {
    { ((double) this->_screen_x) / 2.0, 0, 0, (((double) this->_screen_x) - 1) / 2.0 },
    { 0, ((double) this->_screen_y) / 2.0, 0, (((double) this->_screen_y) - 1) / 2.0 },
    { 0, 0, 1, 0 },
    { 0, 0, 0, 1 },
  };
  this->_viewport_transform = Transform(viewport_transform_values);
}

std::vector<Primitive> VertexShader::_clip_point_helper(Primitive &point, int plane_idx) const
{
  std::vector<Primitive> clipped_points = std::vector<Primitive>();
  if (plane_idx == 6)
  {
    clipped_points.push_back(point);
    return clipped_points;
  }

  Plane plane = this->_camera->view_volume_bounds[plane_idx];
  if (is_bounded(point.vertices[0].position, plane))
  {
    return this->_clip_point_helper(point, plane_idx + 1);
  }

  return clipped_points;
}

std::vector<Primitive> VertexShader::_clip_line_helper(Primitive &line, int plane_idx) const
{
  std::vector<Primitive> clipped_lines = std::vector<Primitive>();
  
  if (plane_idx == 6)
  {
    clipped_lines.push_back(line);
    return clipped_lines;
  }

  Plane plane = this->_camera->view_volume_bounds[plane_idx];
  Vertex a = line.vertices[0];
  Vertex b = line.vertices[1];
  bool a_is_bounded = is_bounded(a.position, plane);
  bool b_is_bounded = is_bounded(b.position, plane);

  if (a_is_bounded && b_is_bounded) // line is completely inside the plane
  {
    return this->_clip_line_helper(line, plane_idx + 1);
  }

  if (!a_is_bounded && !b_is_bounded) // line is completely outside the plane
  {
    return clipped_lines;
  }

  // line spans the plane
  double t = (dot(plane.normal, a.position) + plane.offset) / (dot(plane.normal, a.position - b.position));

  if (a_is_bounded) // a is bounded and b is not
  {
    line.vertices[1] = {
      lerp<Point>(t, a.position, b.position),
      lerp<Color>(t, a.color, b.color),
      lerp<Vector3>(t, a.normal, b.normal),
    };
    return this->_clip_line_helper(line, plane_idx + 1);
  }

  // b is bounded and a is not
  line.vertices[0] = {
    lerp<Point>(t, a.position, b.position),
    lerp<Color>(t, a.color, b.color),
    lerp<Vector3>(t, a.normal, b.normal),
  };
  return this->_clip_line_helper(line, plane_idx + 1);
}

std::vector<Primitive> VertexShader::_clip_triangle_helper(Primitive &triangle, int plane_idx) const
{
  std::vector<Primitive> clipped_triangles = std::vector<Primitive>();

  if (plane_idx == 6)
  {
    clipped_triangles.push_back(triangle);
    return clipped_triangles;
  }

  Plane plane = this->_camera->view_volume_bounds[plane_idx];
  Vertex a = triangle.vertices[0];
  Vertex b = triangle.vertices[1];
  Vertex c = triangle.vertices[2];
  int bounded_vertices_count = (int) (is_bounded(a.position, plane)) + (int) (is_bounded(b.position, plane)) + (int) (is_bounded(c.position, plane));

  if (bounded_vertices_count == 0) // triangle lies completely out of the plane
  {
    return clipped_triangles;
  }

  if (bounded_vertices_count == 3) // triangle lies completely inside this plane. check next plane
  {
    return _clip_triangle_helper(triangle, plane_idx + 1);
  }

  if (bounded_vertices_count == 1) // the clipped shape is a triangle
  {
    Vertex bounded_vertex, unbounded_vertex1, unbounded_vertex2;
    if (is_bounded(a.position, plane))
    {
      bounded_vertex = a;
      unbounded_vertex1 = b;
      unbounded_vertex2 = c;
    }
    else if (is_bounded(b.position, plane))
    {
      bounded_vertex = b;
      unbounded_vertex1 = c;
      unbounded_vertex2 = a;
    }
    else
    {
      bounded_vertex = c;
      unbounded_vertex1 = a;
      unbounded_vertex2 = b;
    }
 
    double t1 = (dot(plane.normal, bounded_vertex.position) + plane.offset) / (dot(plane.normal, bounded_vertex.position - unbounded_vertex1.position));
    double t2 = (dot(plane.normal, bounded_vertex.position) + plane.offset) / (dot(plane.normal, bounded_vertex.position - unbounded_vertex2.position));

    Vertex plane_intersection_vertex1 = {
      lerp<Point>(t1, bounded_vertex.position, unbounded_vertex1.position),
      lerp<Color>(t1, bounded_vertex.color, unbounded_vertex1.color),
      lerp<Vector3>(t1, bounded_vertex.normal, unbounded_vertex1.normal)
    };
    Vertex plane_intersection_vertex2 = {
      lerp<Point>(t2, bounded_vertex.position, unbounded_vertex2.position),
      lerp<Color>(t2, bounded_vertex.color, unbounded_vertex2.color),
      lerp<Vector3>(t2, bounded_vertex.normal, unbounded_vertex2.normal)
    };

    Primitive clipped_triangle = Primitive(bounded_vertex, plane_intersection_vertex1, plane_intersection_vertex2);
    return _clip_triangle_helper(clipped_triangle, plane_idx + 1);
  }

  // the clipped shape is a quad
  Vertex unbounded_vertex, bounded_vertex1, bounded_vertex2;
  if (!is_bounded(a.position, plane))
  {
    unbounded_vertex = a;
    bounded_vertex1 = b;
    bounded_vertex2 = c;
  }
  else if (!is_bounded(b.position, plane))
  {
    unbounded_vertex = b;
    bounded_vertex1 = c;
    bounded_vertex2 = a;
  }
  else
  {
    unbounded_vertex = c;
    bounded_vertex1 = a;
    bounded_vertex2 = b;
  }

  double t1 = (dot(plane.normal, unbounded_vertex.position) + plane.offset) / (dot(plane.normal, unbounded_vertex.position - bounded_vertex1.position));
  double t2 = (dot(plane.normal, unbounded_vertex.position) + plane.offset) / (dot(plane.normal, unbounded_vertex.position - bounded_vertex2.position));

  Vertex plane_intersection_vertex1 = {
    lerp<Point>(t1, unbounded_vertex.position, bounded_vertex1.position),
    lerp<Color>(t1, unbounded_vertex.color, bounded_vertex1.color),
    lerp<Vector3>(t1, unbounded_vertex.normal, bounded_vertex1.normal)
  };
  Vertex plane_intersection_vertex2 = {
    lerp<Point>(t2, unbounded_vertex.position, bounded_vertex2.position),
    lerp<Color>(t2, unbounded_vertex.color, bounded_vertex2.color),
    lerp<Vector3>(t2, unbounded_vertex.normal, bounded_vertex2.normal)
  };

  Primitive clipped_triangle1 = Primitive(bounded_vertex1, plane_intersection_vertex1, plane_intersection_vertex2);
  Primitive clipped_triangle2 = Primitive(bounded_vertex1, plane_intersection_vertex2, bounded_vertex2);

  std::vector<Primitive> clipped_triangles1 = _clip_triangle_helper(clipped_triangle1, plane_idx + 1);
  std::vector<Primitive> clipped_triangles2 = _clip_triangle_helper(clipped_triangle2, plane_idx + 1);

  clipped_triangles.insert(clipped_triangles.end(), clipped_triangles1.begin(), clipped_triangles1.end());
  clipped_triangles.insert(clipped_triangles.end(), clipped_triangles2.begin(), clipped_triangles2.end());
  return clipped_triangles;
}

std::deque<Primitive> VertexShader::transform_to_view_space(std::deque<Primitive> &primitives) const
{
  int primitives_count = primitives.size();

  for (int i = 0; i < primitives_count; i++)
  {
    Primitive primitive = primitives.front();
    primitives.pop_front();

    for (int point_idx = 0; point_idx < primitive.type; point_idx++)
    {
      primitive.vertices[point_idx].position = (this->_camera->camera_transform * HVector::from_vector3(primitive.vertices[point_idx].position)).to_vector3();
    }
    
    primitives.push_back(primitive);
  }

  return primitives;
}

std::deque<Primitive> VertexShader::clip_to_view_volume(std::deque<Primitive> &primitives) const
{
  const int initial_primitives_count = primitives.size();
  std::vector<Primitive> primitives_to_add;

  for (int primitive_idx = 0; primitive_idx < initial_primitives_count; primitive_idx++)
  {
    Primitive primitive = primitives.front();
    primitives.pop_front();

    switch (primitive.type)
    {
    case POINT:
      primitives_to_add = this->_clip_point_helper(primitive, 0);
      break;
    case LINE:
      primitives_to_add = this->_clip_line_helper(primitive, 0);
      break;
    case TRIANGLE:
      primitives_to_add = this->_clip_triangle_helper(primitive, 0);
      break;
    }

    // insert all clipped primitives to the deque of primitives
    for (Primitive primitive : primitives_to_add)
    {
      primitives.push_back(primitive);
    }
    primitives_to_add.clear();
  }

  return primitives;
}

std::deque<Primitive> VertexShader::transform_to_screen_space(std::deque<Primitive> &primitives) const
{
  int primitives_count = primitives.size();
  Transform camera_space_to_screen_space = this->_viewport_transform * this->_camera->projection_transform;

  for (int i = 0; i < primitives_count; i++)
  {
    Primitive primitive = primitives.front();
    primitives.pop_front();

    for (int point_idx = 0; point_idx < primitive.type; point_idx++)
    {
      primitive.vertices[point_idx].position = (camera_space_to_screen_space * HVector::from_vector3(primitive.vertices[point_idx].position)).to_vector3();
    }
    
    primitives.push_back(primitive);
  }

  return primitives;
}

std::deque<Primitive> VertexShader::process_primitives(std::deque<Primitive> &primitives) const
{
  this->transform_to_view_space(primitives);
  this->clip_to_view_volume(primitives);
  this->transform_to_screen_space(primitives);
  return primitives;
}

void VertexShader::set_screen_dimensions(int screen_x, int screen_y)
{
  assert(screen_x > 0 && screen_y > 0);
  this->_screen_x = screen_x;
  this->_screen_y = screen_y;
  this->_update_viewport_transform();
}

void VertexShader::set_camera(std::shared_ptr<Camera> camera)
{
  this->_camera = camera;
}
