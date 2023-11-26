#pragma once

#include <iostream>
#include "vec3.h"
#include "interval.h"

using color = vec3;

void write_color(std::ostream& out, color col, int samples_per_pixel) {
  double r = col.x;
  double g = col.y;
  double b = col.z;

  double scale = 1.0 / samples_per_pixel;
  r *= scale;
  g *= scale;
  b *= scale;

  const interval intensity(0.000, 0.999);

  out << static_cast<int>(255.9 * intensity.clamp(r)) << ' '
      << static_cast<int>(255.9 * intensity.clamp(g)) << ' '
      << static_cast<int>(255.9 * intensity.clamp(b)) << '\n';
}