#pragma once

#include "obj.h"
#include "color.h"

class camera {
public:
  vec3 position = vec3(0.0, 0.0, 0.0);
  double aspect_ratio;
  int img_width;
  int img_height;
  double viewport_height = 2.0;
  double viewport_width;
  double focal_length = 1.0;
  vec3 viewport_u;
  vec3 viewport_v;
  vec3 pixel_delta_u;
  vec3 pixel_delta_v;
  vec3 top_left_pixel;
  vec3 first_pixel_center;
  int max_bounces = 60;
  int samples_per_pixel = 150;

  camera(double aspect_ratio, int img_width) : aspect_ratio(aspect_ratio), img_width(img_width) {
    img_height = static_cast<int>(img_width / aspect_ratio);
    viewport_width = viewport_height * (static_cast<double>(img_width)/img_height);

    viewport_u = vec3(viewport_width, 0.0, 0.0);
    viewport_v = vec3(0.0, viewport_height, 0.0);

    // Define the pixel grid
    pixel_delta_u = viewport_u / img_width;
    pixel_delta_v = viewport_v / img_height;

    // Get the top left pixel position
    top_left_pixel = position - vec3(0.0, 0.0, focal_length) - viewport_u/2 - viewport_v/2;
    // Offset by half a pixel to get the center of the pixel
    first_pixel_center = top_left_pixel + (0.5 * (pixel_delta_u + pixel_delta_v));
  }

  void render(const obj& world) {
    std::cout << "P3\n" << img_width << ' ' << img_height << "\n255\n"; // Header line for PPM image

    for (int j = img_height; j > 0; j--) {
      std::clog << "\r Lines completed: " << (img_height - j) << '/' << img_height << ' ' << std::flush;

      for (int i = 0; i < img_width; i++) {
        // Calculate position of next pixel. Then create a ray for each pixel
        vec3 pixel_color = vec3(0, 0, 0);
        for (int sample = 0; sample < samples_per_pixel; sample++) {
          ray r = get_ray(i, j);
          pixel_color += ray_color(r, world, max_bounces);
        }

        write_color(std::cout, pixel_color, samples_per_pixel);
      }
    }

    std::clog << "\rDone.                 \n";
  }
private:
  vec3 ray_color(const ray& r, const obj& w, int bounces_left) {
    hit_record rec;

    if (bounces_left <= 0) { return vec3(0, 0, 0); }

    if (w.hit(r, viewport, rec)) {
      vec3 reflection = random_on_hemisphere(rec.normal);
      return 0.5 * ray_color(ray(rec.pos, reflection), w, bounces_left - 1);
    }

    // No object hit, ray is sky color
    vec3 unit_direction = unit_vector(r.direction);
    double a = 0.5*(unit_direction.y + 1.0);
    return (1.0-a)*vec3(1.0, 1.0, 1.0) + a*vec3(0.5, 0.7, 1.0);
  }

  // Get a random camera ray for the pixel at i, j
  ray get_ray(int i, int j) {
    vec3 pixel_center = first_pixel_center + (i * pixel_delta_u) + (j * pixel_delta_v);
    vec3 pixel_sample = pixel_center + pixel_sample_square();

    vec3 ray_origin = position;
    vec3 ray_direction = pixel_sample - ray_origin;

    return ray(ray_origin, ray_direction);
  }

  vec3 pixel_sample_square() const {
    double px = -0.5 + random_double();
    double py = -0.5 + random_double();
    return (px * pixel_delta_u) + (py * pixel_delta_v);
  }
};