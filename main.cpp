#include "camera.h"
#include "sphere.h"
#include "world.h"

int main() {
  camera cam = camera(16.0/9.0, 400);

  world w;
  w.add(make_shared<sphere>(vec3(0, 0, -1), 0.5)); // Sphere
  w.add(make_shared<sphere>(vec3(1.3, -.2, -1.4), 0.3)); // Sphere
  w.add(make_shared<sphere>(vec3(-1.3, -.1, -1.3), .4)); // Sphere
  w.add(make_shared<sphere>(vec3(0, -100.5, -1), 100)); // Ground

  cam.render(w);
}