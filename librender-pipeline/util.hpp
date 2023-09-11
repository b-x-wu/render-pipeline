#ifndef UTIL_H
#define UTIL_H

#include "math.h"

template <typename T>
inline T lerp(const double &t, const T &a, const T &b)
{
  return a + t * (b - a);
}

template <typename T>
inline T clamp(const T &val, const T &low, const T &high)
{
  if (val < low)
  {
    return low;
  }

  if (val > high)
  {
    return high;
  }

  return val;
}

// returns the integer part of the number. will be negative if val < 0
inline double integer_part(double val)
{
  if (val < 0) { return std::ceil(val); }
  return std::floor(val);
}

// returns the fractional part of the number. will be negative if val < 0
// ensures that val == integer_part(val) + frac_part(val)
inline double frac_part(double val)
{
  return val - integer_part(val);
}

// returns the right fractional part of the number
inline double right_frac_part(double val)
{
  if (val < 0) { return 1 + frac_part(val); }
  return 1 - frac_part(val);
}

#endif
