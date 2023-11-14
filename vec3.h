#include <cmath>
#include <iostream>

using std::sqrt;

class vec3 {
public:
  double x = 0.0, y = 0.0, z = 0.0;

  vec3() : x(0.0), y(0.0), z(0.0) {};
  vec3(double x, double y, double z) : x(x), y(y), z(z) {};

  // Implement vector3 operations:
  // negation (-)
  // addition (+=)
  // multiplication (*=)
  // division (/=)
  vec3 operator-() const { return vec3(-x, -y, -z); }
  vec3& operator+=(const vec3& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }
  vec3& operator*=(const double t) {
    x *= t;
    y *= t;
    z *= t;
    return *this;
  }
  vec3& operator/=(const double t) {
    return *this *= 1/t;
  }

  double length_squared() const {
    return x*x + y*y + z*z;
  }

  double length() const {
    return sqrt(length_squared());
  }
};