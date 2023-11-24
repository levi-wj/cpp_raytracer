#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include "vec3.h"

using color = vec3;

void write_color(std::ostream& out, color col) {
  out << static_cast<int>(255.9 * col.x) << ' '
      << static_cast<int>(255.9 * col.y) << ' '
      << static_cast<int>(255.9 * col.z) << '\n';
}

#endif