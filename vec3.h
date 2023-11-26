#pragma once

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

  static vec3 random() {
    return vec3(random_double(), random_double(), random_double());
  }

  static vec3 random(double min, double max) {
    return vec3(
      random_double(min, max),
      random_double(min, max),
      random_double(min, max)
    );
  }
};

// Make the class printable
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
  return out << v.x << ' ' << v.y << ' ' << v.z;
}

// Add operation
inline vec3 operator+(const vec3& u, const vec3& v) {
  return vec3(u.x + v.x, u.y + v.y, u.z + v.z);
}

// Substract operation
inline vec3 operator-(const vec3& u, const vec3& v) {
  return vec3(u.x - v.x, u.y - v.y, u.z - v.z);
}

// Multiply operation (vectors)
inline vec3 operator*(const vec3& u, const vec3& v) {
  return vec3(u.x * v.x, u.y * v.y, u.z * v.z);
}

// Multiply by scalar
inline vec3 operator*(double t, const vec3& v) {
  return vec3(t * v.x, t * v.y, t * v.z);
}
inline vec3 operator*(const vec3& v, double t) {
  return t * v;
}

// Divide by scalar
inline vec3 operator/(vec3& v, double t) {
  return (1/t) * v;
}

// Dot product
inline double dot(const vec3& u, const vec3& v) {
  return u.x * v.x
       + u.y * v.y
       + u.z * v.z;
}

// Cross product
inline vec3 cross(const vec3& u, const vec3& v) {
  double x = u.y * v.z - u.z * v.y;
  double y = u.z * v.x - u.x * v.z;
  double z = u.x * v.y - u.y * v.x;
  return vec3(x, y, z);
}

// Unit vector
inline vec3 unit_vector(vec3 v) {
  return v / v.length();
}

// Get a random vector in the unit hemisphere
inline vec3 random_in_unit_sphere() {
  // Just keep trying until we get one in the sphere because the actual math is hard
  while (true) {
    vec3 r = vec3::random(-1, 1);
    if (r.length_squared() < 1) {
      return r;
    }
  }
}

inline vec3 random_unit_vector() {
  return unit_vector(random_in_unit_sphere());
}

inline vec3 random_on_hemisphere(const vec3& normal) {
  vec3 on_unit_sphere = random_unit_vector();
  if (dot(on_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
    return on_unit_sphere;
  else
    return -on_unit_sphere;
}