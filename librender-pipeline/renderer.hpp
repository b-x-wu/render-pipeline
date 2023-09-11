#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <memory>
#include "color.hpp"
#include "primitive.hpp"

class Renderer
{
  Renderer();
  ~Renderer() = default;
  std::vector<std::vector<Color>> render(const std::vector<Primitive> &primitives);
private:
  // render pipeline stages
};

#endif
