#pragma once

#include "vec3.h"

class ray {
public:
  vec3 origin;
  vec3 direction;

  ray() {}
  ray(const vec3& origin, const vec3& direction) : origin(origin), direction(direction) {}

  vec3 at(double t) const {
    return origin + t * direction;
  } 
};