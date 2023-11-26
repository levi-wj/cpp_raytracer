#pragma once

#include "consts.h"

class hit_record {
public:
  double t;
  vec3 pos;
  vec3 normal;
  bool front_face;

  inline void set_face_normal(const ray& r, const vec3& outward_normal) {
    front_face = dot(r.direction, outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
  }
};

class obj {
public:
  // Create default destructor, since this class is used polymorphically.
  // This allows derived classes like sphere to be properly destroyed
  virtual ~obj() = default;

  virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};