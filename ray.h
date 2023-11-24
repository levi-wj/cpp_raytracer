#ifndef RAY_H
#define RAY_H

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

  vec3 get_color() const {
    double t = intersects_sphere(vec3(0.0, 0.0, -1.0), 0.5);
    if (t > 0.0) {
      return vec3(0.0, 0.0, 1.0);
    }

    vec3 unit_direction = unit_vector(direction);
    double a = 0.5*(unit_direction.y + 1.0);
    return (1.0-a)*vec3(1.0, 1.0, 1.0) + a*vec3(0.5, 0.7, 1.0);
  }
private:
  double intersects_sphere(vec3& sphere_pos, double radius) const {
    // Equation for a sphere is: x^2 + y^2 + z^2 = R^2
    vec3 oc = origin - sphere_pos;
    double a = dot(direction, direction);
    double b = 2.0 * dot(oc, direction);
    double c = dot(oc, oc) - radius*radius;
    
    // Solve using the quadratic formula
    double res = b*b - 4*a*c;

    if (res < 0) {
      return -1.0;
    } else {
      return (-b - sqrt(res)) / (2.0 * a);
    }
  }
};

#endif