#include <memory>
#include <assert.h>
#include <deque>
#include <iostream>

#include "vertex-shader.hpp"
#include "camera.hpp"

void test_transform_to_view_space(VertexShader vertex_shader)
{
  std::deque<Primitive> primitives = std::deque<Primitive>();
  primitives.push_back(Primitive({ 1, 1, 2 }));
  primitives.push_back(Primitive({ -1, -1, 4 }, { -1, 1, 4 }));
  primitives.push_back(Primitive({ -1, -1, 6 }, { -1, 1, 6 }, { 2, -1, 6 }));
  std::deque<Primitive> actual = vertex_shader.transform_to_view_space(primitives);

  std::deque<Primitive> expected = std::deque<Primitive>();
  expected.push_back(Primitive({ 0, -1, 0 }));
  expected.push_back(Primitive({ 2, -3, 2 }, { 2, -3, 0 }));
  expected.push_back(Primitive({ 2, -5, 2 }, { 2, -5, 0 }, { -1, -5, 2 }));

  assert(actual == expected);
}

void test_clip_point_to_view_volume(VertexShader vertex_shader)
{
  std::deque<Primitive> primitives = std::deque<Primitive>();
  primitives.push_back(Primitive({ 1, 12, -15 }));
  primitives.push_back(Primitive({ 1, 1, -12}));
  std::deque<Primitive> actual = vertex_shader.clip_to_view_volume(primitives);

  std::deque<Primitive> expected = std::deque<Primitive>();
  expected.push_back(Primitive({ 1, 1, -12 }));

  assert(actual == expected);
}

void test_clip_line_to_view_volume(VertexShader vertex_shader)
{
  std::deque<Primitive> primitives = std::deque<Primitive>();
  primitives.push_back(Primitive({ -1, -1, -15 }, { -15, -1, -15 }));
  primitives.push_back(Primitive({ -12, 0, -15 }, { -12, 10, -15 }));
  primitives.push_back(Primitive({ 0, -20, -15 }, { 0, 20, -15 }));
  primitives.push_back(Primitive({ -8, 5, -15 }, { -4, 6, -15 }));
  std::deque<Primitive> actual = vertex_shader.clip_to_view_volume(primitives);

  std::deque<Primitive> expected = std::deque<Primitive>();
  expected.push_back(Primitive({ -10, -1, -15 }, { -1, -1, -15 }));
  expected.push_back(Primitive({ 0, -10, -15 }, { 0, 10, -15 }));
  expected.push_back(Primitive({ -8, 5, -15 }, { -4, 6, -15 }));

  assert(actual == expected);
}

void test_clip_triangle_quad_to_view_volume(VertexShader vertex_shader)
{
  std::deque<Primitive> primitives = std::deque<Primitive>();
  primitives.push_back(Primitive({ 8, 11, -15 }, { 6, 9, -15 }, { 10, 9, -15 }));
  std::deque<Primitive> actual = vertex_shader.clip_to_view_volume(primitives);

  std::deque<Primitive> expected1 = std::deque<Primitive>();
  expected1.push_back(Primitive({ 7, 10, -15 }, { 9, 10, -15 }, { 6, 9, -15 }));
  expected1.push_back(Primitive({ 9, 10, -15 }, { 6, 9, -15 }, { 10, 9, -15 }));

  std::deque<Primitive> expected2 = std::deque<Primitive>();
  expected2.push_back(Primitive({ 9, 10, -15 }, { 6, 9, -15 }, { 10, 9, -15 }));
  expected2.push_back(Primitive({ 7, 10, -15 }, { 9, 10, -15 }, { 6, 9, -15 }));

  std::deque<Primitive> expected3 = std::deque<Primitive>();
  expected3.push_back(Primitive({ 9, 10, -15 }, { 7, 10, -15 }, { 10, 9, -15 }));
  expected3.push_back(Primitive({ 7, 10, -15 }, { 10, 9, -15 }, { 6, 9, -15 }));
  
  std::deque<Primitive> expected4 = std::deque<Primitive>();
  expected4.push_back(Primitive({ 7, 10, -15 }, { 10, 9, -15 }, { 6, 9, -15 }));
  expected4.push_back(Primitive({ 9, 10, -15 }, { 7, 10, -15 }, { 10, 9, -15 }));

  assert((actual == expected1) || (actual == expected2) || (actual == expected3) || (actual == expected4));
}

void test_clip_triangle_tri_to_view_volume(VertexShader vertex_shader)
{
  std::deque<Primitive> primitives = std::deque<Primitive>();
  primitives.push_back(Primitive({ 8, 9, -15 }, { 10, 11, -15 }, { 6, 11, -15 }));
  std::deque<Primitive> actual = vertex_shader.clip_to_view_volume(primitives);

  std::deque<Primitive> expected = std::deque<Primitive>();
  expected.push_back(Primitive({ 8, 9, -15 }, { 7, 10, -15 }, { 9, 10, -15 }));

  assert(actual == expected);
}

void test_transform_to_screen_space(VertexShader vertex_shader)
{
  std::deque<Primitive> primitives = std::deque<Primitive>();
  primitives.push_back(Primitive({ 1, 1, 2 }));
  primitives.push_back(Primitive({ -1, -1, 4 }, { -1, 1, 4 }));
  primitives.push_back(Primitive({ -1, -1, 6 }, { -1, 1, 6 }, { 2, -1, 6 }));
  std::deque<Primitive> actual = vertex_shader.transform_to_screen_space(primitives);

  std::deque<Primitive> expected = std::deque<Primitive>();
  expected.push_back(Primitive({ 54.5, 54.5, 3.4 }));
  expected.push_back(Primitive({ 44.5, 44.5, 3.8 }, { 44.5, 54.5, 3.8 }));
  expected.push_back(Primitive({ 44.5, 44.5, 4.2 }, { 44.5, 54.5, 4.2 }, { 59.5, 44.5, 4.2 }));

  assert(actual == expected);
}

int main()
{
  // setup
  VertexShader vertex_shader = VertexShader();
  vertex_shader.set_screen_dimensions(100, 100);

  std::shared_ptr<OrthographicCamera> camera = std::shared_ptr<OrthographicCamera>(new OrthographicCamera());
  camera->set_x_bounds(-10, 10);
  camera->set_y_bounds(-10, 10);
  camera->set_z_bounds(-10, -20);
  
  Point eye_position = { 1, 1, 1 };
  Vector3 gaze_direction = { 0, 1, 0 };
  Vector3 view_up_direction = { 0, 0, -1 };

  camera->set_eye_position(eye_position);
  camera->set_gaze_direction(gaze_direction);
  camera->set_view_up_direction(view_up_direction);

  vertex_shader.set_camera(camera);

  test_transform_to_view_space(vertex_shader);
  test_clip_point_to_view_volume(vertex_shader);
  test_clip_line_to_view_volume(vertex_shader);
  test_clip_triangle_quad_to_view_volume(vertex_shader);
  test_clip_triangle_tri_to_view_volume(vertex_shader);
  test_transform_to_screen_space(vertex_shader);
}