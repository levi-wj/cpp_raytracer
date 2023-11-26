#pragma once


#include "consts.h"
#include "obj.h"

class sphere : public obj {
  public:
    vec3 center;
    double radius;

    sphere(vec3 _center, double _radius) : center(_center), radius(_radius) {}

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        // Algebra I don't really understand to intersect a ray with the equation of a sphere
        vec3 oc = r.origin - center;
        double a = r.direction.length_squared();
        double half_b = dot(oc, r.direction);
        double c = oc.length_squared() - radius * radius;

        double discriminant = half_b * half_b - a * c;
        if (discriminant < 0) { return false; }
        double sqrtd = sqrt(discriminant);

        // Check for roots
        double root = (-half_b - sqrtd) / a;
        if (root <= ray_t.min || ray_t.max <= root) {
            root = (-half_b + sqrtd) / a;
            if (root <= ray_t.min || ray_t.max <= root) {
                return false;
            }
        }

        rec.t = root;
        rec.pos = r.at(rec.t);
        rec.normal = (rec.pos - center) / radius;
        vec3 outward_normal = (rec.pos - center) / radius;
        rec.set_face_normal(r, outward_normal);

        return true;
    }
};