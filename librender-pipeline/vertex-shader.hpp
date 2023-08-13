#ifndef VERTEX_SHADER_H
#define VERTEX_SHADER_H

#include <vector>
#include <memory>

#include "primitive.hpp"
#include "camera.hpp"
#include "transform.hpp"

class VertexShader
{
  std::shared_ptr<Camera> _camera;
  int _screen_x, _screen_y;
  Transform _viewport_transform;

  void _update_viewport_transform();
public:
  VertexShader() {};
  ~VertexShader() = default;
  std::vector<Primitive> process_primitives(const std::vector<Primitive> &primitives);
  void set_screen_dimensions(int screen_x, int screen_y);
  void set_camera(std::shared_ptr<Camera> camera);
};

#endif
