#include <math.h>

#include "rasterizer.hpp"

// Fragment Rasterizer::_plot(int screen_x_idx, int screen_y_idx, double depth, Color color, Vector3 normal, std::deque<Fragment> &fragments) const
// {
//   // Fragment fragment;
//   // fragment.screen_x_idx = screen_x_idx;
//   // fragment.screen_y_idx = screen_y_idx;
//   // fragment.depth = depth;
//   // fragment.color = color;
//   // fragment.normal = normal;
//   // fragments.push_back(fragment);
//   Fragment fragment = {
//     screen_x_idx,
//     screen_y_idx,
//     depth,
//     color,
//     normal
//   };
//   fragments.push_back(fragment);
//   return fragment;
// }

// TODO: add point anti aliasing?
void Rasterizer::_rasterize_point(Primitive point, std::deque<Fragment> &fragments) const
{
  Fragment point_fragment = Fragment();
  
  double right_distance = std::ceil(point.vertices[0].position.get_x()) - point.vertices[0].position.get_x();
  double left_distance = point.vertices[0].position.get_x() - std::floor(point.vertices[0].position.get_x());
  double up_distance = std::ceil(point.vertices[0].position.get_y()) - point.vertices[0].position.get_y();
  double down_distance = point.vertices[0].position.get_y() - std::floor(point.vertices[0].position.get_y());
  
  if (right_distance < left_distance)
  {
    point_fragment.screen_x_idx = std::ceil(point.vertices[0].position.get_x());
    // point_fragment.screen_x_offset = -right_distance;
  }
  else
  {
    point_fragment.screen_x_idx = std::floor(point.vertices[0].position.get_x());
    // point_fragment.screen_x_offset = left_distance;
  }

  if (up_distance < down_distance)
  {
    point_fragment.screen_y_idx = std::ceil(point.vertices[0].position.get_y());
    // point_fragment.screen_y_offset = -up_distance;
  }
  else
  {
    point_fragment.screen_y_idx = std::floor(point.vertices[0].position.get_y());
    // point_fragment.screen_y_offset = down_distance;
  }

  point_fragment.depth = point.vertices[0].position.get_z();
  point_fragment.color = point.vertices[0].color;
  point_fragment.normal = point.vertices[0].normal;

  fragments.push_back(point_fragment);
}

void Rasterizer::_rasterize_line(Primitive line, std::deque<Fragment> &fragments) const
{
  bool steep = std::abs(line.vertices[1].position.get_y() - line.vertices[0].position.get_y()) > std::abs(line.vertices[1].position.get_x() - line.vertices[0].position.get_x());

  if (steep)
  {
    std::swap(line.vertices[0].position.values[0], line.vertices[0].position.values[1]);
    std::swap(line.vertices[1].position.values[0], line.vertices[1].position.values[1]);
  }

  if (line.vertices[0].position.get_x() > line.vertices[1].position.get_x())
  {
    std::swap(line.vertices[0], line.vertices[1]);
  }

  double dx = line.vertices[1].position.get_x() - line.vertices[0].position.get_x();
  double dy = line.vertices[1].position.get_y() - line.vertices[0].position.get_y();
  double gradient = dx == 0.0 ? 1.0 : dy / dx;

  // handle first endpoint
  double x_end = std::round(line.vertices[0].position.get_x());
  double y_end = line.vertices[0].position.get_y() + gradient * (x_end - line.vertices[0].position.get_x());
  double x_gap = right_frac_part(line.vertices[0].position.get_x() + 0.5);
  double x_pxl_start = x_end;
  double y_pxl_start = integer_part(y_end);
  
  if (steep)
  {
    Fragment start_frag1 = Fragment(y_pxl_start, x_pxl_start, line.vertices[0].position.get_z(), {
      line.vertices[0].color.red,
      line.vertices[0].color.green,
      line.vertices[0].color.blue,
      std::round(line.vertices[0].color.alpha * right_frac_part(y_end) * x_gap)
    }, right_frac_part(y_end) * x_gap * line.vertices[0].normal);
    Fragment start_frag2 = Fragment(y_pxl_start + 1, x_pxl_start, line.vertices[0].position.get_z(), {
      line.vertices[0].color.red,
      line.vertices[0].color.green,
      line.vertices[0].color.blue,
      std::round(line.vertices[0].color.alpha * frac_part(y_end) * x_gap)
    }, frac_part(y_end) * x_gap * line.vertices[0].normal);

    fragments.push_back(start_frag1);
    fragments.push_back(start_frag2);
  }
  else
  {
    Fragment start_frag1 = Fragment(x_pxl_start, y_pxl_start, line.vertices[0].position.get_z(), {
      line.vertices[0].color.red,
      line.vertices[0].color.green,
      line.vertices[0].color.blue,
      std::round(line.vertices[0].color.alpha * right_frac_part(y_end) * x_gap)
    }, right_frac_part(y_end) * x_gap * line.vertices[0].normal);
    Fragment start_frag2 = Fragment(x_pxl_start, y_pxl_start + 1, line.vertices[0].position.get_z(), {
      line.vertices[0].color.red,
      line.vertices[0].color.green,
      line.vertices[0].color.blue,
      std::round(line.vertices[0].color.alpha * frac_part(y_end) * x_gap)
    }, frac_part(y_end) * x_gap * line.vertices[0].normal);

    fragments.push_back(start_frag1);
    fragments.push_back(start_frag2);
  }

  double y_intersection = y_end + gradient;

  // handle second endpoint
  x_end = std::round(line.vertices[1].position.get_x());
  y_end = line.vertices[1].position.get_y() + gradient * (x_end - line.vertices[1].position.get_x());
  x_gap = frac_part(line.vertices[1].position.get_x() + 0.5);
  double x_pxl_end = x_end;
  double y_pxl_end = integer_part(y_end);

  if (steep)
  {
    Fragment start_frag1 = Fragment(y_pxl_start, x_pxl_start, line.vertices[0].position.get_z(), {
      line.vertices[0].color.red,
      line.vertices[0].color.green,
      line.vertices[0].color.blue,
      std::round(line.vertices[0].color.alpha * right_frac_part(y_end) * x_gap)
    }, right_frac_part(y_end) * x_gap * line.vertices[0].normal);
    Fragment start_frag2 = Fragment(y_pxl_start + 1, x_pxl_start, line.vertices[0].position.get_z(), {
      line.vertices[0].color.red,
      line.vertices[0].color.green,
      line.vertices[0].color.blue,
      std::round(line.vertices[0].color.alpha * frac_part(y_end) * x_gap)
    }, frac_part(y_end) * x_gap * line.vertices[0].normal);

    fragments.push_back(start_frag1);
    fragments.push_back(start_frag2);

  }
  else
  {

  }

}

void Rasterizer::set_screen_dimensions(int screen_x, int screen_y)
{
  if ((screen_x <= 0) || (screen_y <= 0))
  {
    return;
  }

  this->_screen_x = screen_x;
  this->_screen_y = screen_y;
}

std::deque<Fragment> Rasterizer::rasterize(std::deque<Primitive> &primitives) const
{
  std::deque<Fragment> fragments = std::deque<Fragment>();

  for (Primitive primitive : primitives)
  {
    switch (primitive.type)
    {
    case POINT:
      this->_rasterize_point(primitive, fragments);
      break;
    case LINE:
      this->_rasterize_line(primitive, fragments);
      break;
    case TRIANGLE:
      this->_rasterize_triangle(primitive, fragments);
      break;
    }
  }

  return fragments;
}