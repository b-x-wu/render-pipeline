#ifndef UTIL_H
#define UTIL_H

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

#endif
