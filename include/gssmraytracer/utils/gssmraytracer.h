
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

inline float Lerp(float t, float v1, float v2) {
  return (1.f - t) * v1 + t * v2;
}

inline float Clamp(float val, float low, float high) {
  if (val < low) return low;
  else if (val > high) return high;
  else return val;
}

inline float Radians(float deg) {
  return ((float)M_PI/180.f) * deg;
}

inline float Degrees(float rad) {
  return (180.f/(float)M_PI) * rad;
}
