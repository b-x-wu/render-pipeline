#include <assert.h>
#include <iostream>

#include "camera.hpp"

class TestCamera : public Camera
{
  void _update_projection_transform() {}
  void _update_view_volume_bounds() {}
};

void test_update_camera_transform()
{
  TestCamera camera = TestCamera();

  Point eye_position = { 1, 1, 1 };
  Vector3 gaze_direction = { 1, 0, 0 };
  Vector3 view_up_direction = { 0, 1, 0 };

  camera.set_eye_position(eye_position);
  camera.set_gaze_direction(gaze_direction);
  camera.set_view_up_direction(view_up_direction);

  Transform actual = camera.camera_transform;
  double expected_values[4][4] = {
    {  0, 0, 1, -1 },
    {  0, 1, 0, -1 },
    { -1, 0, 0,  1 },
    {  0, 0, 0,  1 },
  };
  Transform expected = Transform(expected_values);

  assert(actual == expected);
}

void test_update_orthogonal_projection_transform()
{
  OrthogonalCamera camera = OrthogonalCamera();

  camera.set_x_bounds(-10, 10);
  camera.set_y_bounds(-10, 10);
  camera.set_z_bounds(-10, -20);

  Transform actual = camera.projection_transform;
  double expected_values[4][4] = {
    { 0.1,   0,   0, 0 },
    {   0, 0.1,   0, 0 },
    {   0,   0, 0.2, 3 },
    {   0,   0,   0, 1 },
  };
  Transform expected = Transform(expected_values);

  // test to see that points in the viewport map to the cannonical view volume
  HVector inside_camera_space_point = { -5, 5, -15, 1 };
  Vector3 inside_cannonical_point = (camera.projection_transform * inside_camera_space_point).to_vector3();
  assert(-1 <= inside_cannonical_point.get_x() && inside_cannonical_point.get_x() <= 1);
  assert(-1 <= inside_cannonical_point.get_y() && inside_cannonical_point.get_y() <= 1);
  assert(-1 <= inside_cannonical_point.get_z() && inside_cannonical_point.get_z() <= 1);

  // test to see that points outside the viewport don't map to the cannonical view volume
  HVector outside_camera_space_point = { -11, 15, -15, 1 };
  Vector3 outside_cannonical_point = (camera.projection_transform * outside_camera_space_point).to_vector3();
  assert(
    -1 > outside_cannonical_point.get_x() || outside_cannonical_point.get_x() > 1 || 
    -1 > outside_cannonical_point.get_y() || outside_cannonical_point.get_y() > 1 || 
    -1 > outside_cannonical_point.get_z() || outside_cannonical_point.get_z() > 1
  );
}

void test_update_orthogonal_view_volume_bounds()
{
  OrthogonalCamera camera = OrthogonalCamera();

  camera.set_x_bounds(-10, 10);
  camera.set_y_bounds(-10, 10);
  camera.set_z_bounds(-10, -20);

  Vector3 inside_point = { 0, 0, -15 };
  assert(dot(camera.view_volume_bounds[0].normal, inside_point) + camera.view_volume_bounds[0].offset < 0);
  assert(dot(camera.view_volume_bounds[1].normal, inside_point) + camera.view_volume_bounds[1].offset < 0);
  assert(dot(camera.view_volume_bounds[2].normal, inside_point) + camera.view_volume_bounds[2].offset < 0);
  assert(dot(camera.view_volume_bounds[3].normal, inside_point) + camera.view_volume_bounds[3].offset < 0);
  assert(dot(camera.view_volume_bounds[4].normal, inside_point) + camera.view_volume_bounds[4].offset < 0);
  assert(dot(camera.view_volume_bounds[5].normal, inside_point) + camera.view_volume_bounds[5].offset < 0);
  assert(is_bounded(inside_point, camera.view_volume_bounds, 6));

  Vector3 outside_point = { -12, 0, 0 };
  assert(
    dot(camera.view_volume_bounds[0].normal, outside_point) + camera.view_volume_bounds[0].offset > 0 ||
    dot(camera.view_volume_bounds[1].normal, outside_point) + camera.view_volume_bounds[1].offset > 0 ||
    dot(camera.view_volume_bounds[2].normal, outside_point) + camera.view_volume_bounds[2].offset > 0 ||
    dot(camera.view_volume_bounds[3].normal, outside_point) + camera.view_volume_bounds[3].offset > 0 ||
    dot(camera.view_volume_bounds[4].normal, outside_point) + camera.view_volume_bounds[4].offset > 0 ||
    dot(camera.view_volume_bounds[5].normal, outside_point) + camera.view_volume_bounds[5].offset > 0
  );
  assert(!is_bounded(outside_point, camera.view_volume_bounds, 6));
}


int main()
{
  test_update_camera_transform();
  test_update_orthogonal_projection_transform();
  test_update_orthogonal_view_volume_bounds();
}
