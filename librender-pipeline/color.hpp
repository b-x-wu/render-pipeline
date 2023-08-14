#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>
#include <math.h>

#include "util.hpp"

struct Color
{
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  uint8_t alpha;
};

inline bool operator==(const Color &color1, const Color &color2)
{
  return color1.red == color2.red && color1.green == color2.green && color1.blue == color2.blue && color1.alpha == color2.alpha;
}

inline Color operator+(const Color &color1, const Color &color2)
{
  return {
    (uint8_t) clamp<int>(color1.red + color2.red, 0, 255),
    (uint8_t) clamp<int>(color1.green + color2.green, 0, 255),
    (uint8_t) clamp<int>(color1.blue + color2.blue, 0, 255),
    (uint8_t) clamp<int>(color1.alpha + color2.alpha, 0, 255),
  };
}

inline Color operator-(const Color &color1, const Color &color2)
{
  return {
    (uint8_t) clamp<int>(color1.red - color2.red, 0, 255),
    (uint8_t) clamp<int>(color1.green - color2.green, 0, 255),
    (uint8_t) clamp<int>(color1.blue - color2.blue, 0, 255),
    (uint8_t) clamp<int>(color1.alpha - color2.alpha, 0, 255),
  };
}

inline Color operator*(const double &t, const Color &color)
{
  return {
    (uint8_t) clamp<int>(std::floor(t * color.red), 0, 255),
    (uint8_t) clamp<int>(std::floor(t * color.green), 0, 255),
    (uint8_t) clamp<int>(std::floor(t * color.blue), 0, 255),
    (uint8_t) clamp<int>(std::floor(t * color.alpha), 0, 255),
  };
}

#endif
