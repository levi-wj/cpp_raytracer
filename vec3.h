#ifndef VEC3_H
#define VEC3_H

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

#endif