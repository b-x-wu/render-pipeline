#ifndef RASTERIZER_H
#define RASTERIZER_H

#include <deque>

#include "fragment.hpp"
#include "primitive.hpp"

class Rasterizer
{
  int _screen_x, _screen_y; // number of pixels of the screen in each dimension

  void _rasterize_point(Primitive point, std::deque<Fragment> &fragments) const;
  void _rasterize_line(Primitive line, std::deque<Fragment> &fragments) const;
  void _rasterize_triangle(Primitive triangle, std::deque<Fragment> &fragments) const;
public:
  void set_screen_dimensions(int screen_x, int screen_y);
  std::deque<Fragment> rasterize(std::deque<Primitive> &primitives) const;  
};

#endif
