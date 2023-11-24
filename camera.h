#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"

class camera {
public:
  vec3 position = vec3(0.0, 0.0, 0.0);
  double aspect_ratio;
  int img_width;
  int img_height;
  double viewport_height = 2.0;
  double viewport_width;
  double focal_length = 1.0;

  camera(double aspect_ratio, int img_width) : aspect_ratio(aspect_ratio), img_width(img_width) {
    camera::img_height = static_cast<int>(img_width / aspect_ratio);
    camera::viewport_width = viewport_height * (static_cast<double>(img_width)/img_height);
  }
};

#endif