#include <assert.h>

#include "vertex-shader.hpp"
#include "primitive.hpp"

void VertexShader::_update_viewport_transform()
{
  double viewport_transform_values[4][4] = {
    { this->_screen_x / 2, 0, 0, (this->_screen_x - 1) / 2 },
    { 0, this->_screen_y / 2, 0, (this->_screen_y - 1) / 2 },
    { 0, 0, 1, 0 },
    { 0, 0, 0, 1 },
  };
  this->_viewport_transform = Transform(viewport_transform_values);
}

std::vector<Primitive> VertexShader::process_primitives(const std::vector<Primitive> &primitives)
{
  std::vector<Primitive> screen_space_primitives = std::vector<Primitive>();
  Transform vertex_transform = this->_viewport_transform * this->_camera->projection_transform * this->_camera->camera_transform;

  for (Primitive primitive : primitives)
  {
    switch (primitive.type)
    {
    case POINT:
      Vertex v1 = {
        (vertex_transform * HVector::from_vector3(primitive.vertices[0].position)).get_normalized_vector3(),
        primitive.vertices[0].color,
        primitive.vertices[0].normal,
      };
      screen_space_primitives.push_back(Primitive(v1));
      break;
    case LINE:
      Vertex v1 = {
        (vertex_transform * HVector::from_vector3(primitive.vertices[0].position)).get_normalized_vector3(),
        primitive.vertices[0].color,
        primitive.vertices[0].normal,
      };
      Vertex v2 = {
        (vertex_transform * HVector::from_vector3(primitive.vertices[1].position)).get_normalized_vector3(),
        primitive.vertices[1].color,
        primitive.vertices[1].normal,
      };
      screen_space_primitives.push_back(Primitive(v1, v2));
      break;
    case TRIANGLE:
      Vertex v1 = {
        (vertex_transform * HVector::from_vector3(primitive.vertices[0].position)).get_normalized_vector3(),
        primitive.vertices[0].color,
        primitive.vertices[0].normal,
      };
      Vertex v2 = {
        (vertex_transform * HVector::from_vector3(primitive.vertices[1].position)).get_normalized_vector3(),
        primitive.vertices[1].color,
        primitive.vertices[1].normal,
      };
      Vertex v3 = {
        (vertex_transform * HVector::from_vector3(primitive.vertices[2].position)).get_normalized_vector3(),
        primitive.vertices[2].color,
        primitive.vertices[2].normal,
      };
      screen_space_primitives.push_back(Primitive(v1, v2, v3));
      break;
    }
  }

  return screen_space_primitives;
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
