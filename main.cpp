#include <iostream>

#include "vec3.h"
#include "ray.h"
#include "color.h"
#include "camera.h"

int main() {
  camera cam = camera(16.0/9.0, 400);

  // Used to define the viewport grid (linear algebra stuff fr)
  vec3 viewport_u = vec3(cam.viewport_width, 0.0, 0.0);
  vec3 viewport_v = vec3(0.0, cam.viewport_height, 0.0);

  // Define the pixel grid
  vec3 pixel_delta_u = viewport_u / cam.img_width;
  vec3 pixel_delta_v = viewport_v / cam.img_height;

  // Get the top left pixel position
  vec3 top_left_pixel = cam.position - vec3(0.0, 0.0, cam.focal_length) - viewport_u/2 - viewport_v/2;
  // Offset by half a pixel to get the center of the pixel
  vec3 first_pixel_center = top_left_pixel + (0.5 * (pixel_delta_u + pixel_delta_v));

  //
  // Render
  //

  // Header line for ppm images
  std::cout << "P3\n" << cam.img_width << ' ' << cam.img_height << "\n255\n";

  for (int j = 0; j < cam.img_height; j++) {
    std::clog << "\r Lines left: " << (cam.img_height - j) << ' ' << std::flush;

    for (int i = 0; i < cam.img_width; i++) {
      // Calculate position of next pixel. Then create a ray for each pixel
      vec3 pixel_pos = first_pixel_center + (i * pixel_delta_u) + (j * pixel_delta_v);
      auto ray_direction = pixel_pos - cam.position;
      ray r = ray(cam.position, ray_direction);

      write_color(std::cout, r.get_color());
    }
  }
}