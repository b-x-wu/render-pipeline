#ifndef CAMERA_H
#define CAMERA_H

#include "vector3.hpp"
#include "transform.hpp"
#include "geometry.hpp"

class Camera
{
  Point _eye_position;
  Vector3 _gaze_direction, _view_up_direction;

  void _update_camera_transform();
  virtual void _update_projection_transform() = 0;
  virtual void _update_view_volume_bounds() = 0;

public:
  Transform camera_transform, projection_transform;
  Plane view_volume_bounds[6];

  void set_eye_position(Point &eye_position);
  void set_gaze_direction(Vector3 &gaze_direction);
  void set_view_up_direction(Vector3 &view_up_direction);
};

class OrthogonalCamera : public Camera
{
  double _left, _right, _bottom, _top, _near, _far;

  void _update_projection_transform();
  void _update_view_volume_bounds();

public:
  void set_x_bounds(double left, double right);
  void set_y_bounds(double bottom, double top);
  void set_z_bounds(double near, double far);
};

// TODO: PerspectiveCamera

#endif
