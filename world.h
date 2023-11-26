#pragma once

#include <vector>
#include <memory>

#include "consts.h"
#include "obj.h"

using std::shared_ptr;
using std::make_shared;

class world : public obj {
public:
  std::vector <shared_ptr<obj>> objects;

  world() {}
  world(shared_ptr<obj> object) { add(object); }

  void clear() { objects.clear(); }
  void add(shared_ptr<obj> object) { objects.push_back(object); }

  bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
      hit_record temp_rec;
      bool hit_anything = false;
      double closest_so_far = ray_t.max;

      for (const auto& object : objects) {
          if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec)) {
              hit_anything = true;
              closest_so_far = temp_rec.t;
              rec = temp_rec;
          }
      }

      return hit_anything;
  }
};