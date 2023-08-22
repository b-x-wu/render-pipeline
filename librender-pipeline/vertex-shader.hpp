#ifndef VERTEX_SHADER_H
#define VERTEX_SHADER_H

#include <vector>
#include <deque>
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

  std::vector<Primitive> _clip_point_helper(Primitive &point, int plane_idx) const;
  std::vector<Primitive> _clip_line_helper(Primitive &line, int plane_idx) const;
  std::vector<Primitive> _clip_triangle_helper(Primitive &line, int plane_idx) const;
public:
  VertexShader() {};
  ~VertexShader() = default;
  std::deque<Primitive> process_primitives(std::deque<Primitive> &primitives) const;
  std::deque<Primitive> transform_to_view_space(std::deque<Primitive> &primitives) const;
  std::deque<Primitive> clip_to_view_volume(std::deque<Primitive> &primitives) const;
  std::deque<Primitive> transform_to_screen_space(std::deque<Primitive> &primitives) const;
  void set_screen_dimensions(int screen_x, int screen_y);
  void set_camera(std::shared_ptr<Camera> camera);
};

#endif
