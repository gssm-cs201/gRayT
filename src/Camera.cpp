#include "gssmraytracer/utils/Camera.h"
#include "gssmraytracer/utils/RenderGlobals.h"
#include "gssmraytracer/utils/Color.h"
#include "gssmraytracer/utils/Ray.h"
#include "gssmraytracer/geometry/Shape.h"
#include "gssmraytracer/utils/ProgressMeter.h"
#ifdef _OPENMP
#include <omp.h>
#endif

using namespace gssmraytracer::geometry;

namespace gssmraytracer {
namespace utils {

  class Camera::Impl {
  public:
    geometry::Point eye;
    math::Vector view;
    math::Vector up;
    math::Vector axis_view;
    math::Vector axis_up;
    math::Vector axis_right;
    float aspect_ratio;
    float htanfov;
    float vtanfov;
    float fov;
    float near;
    float far;

  };

Camera::Camera(): mImpl(new Impl) {
    setEyeViewUp(geometry::Point(0,0,0),
                 math::Vector(0,0,1),
                 math::Vector(0,1,0));
    setAspectRatio(16.0/9.0);
    setFOV(60.0);
    mImpl->near = 0.0;
    mImpl->far = std::numeric_limits<float>::infinity();

}

Camera::Camera(const geometry::Point &eye,
               const math::Vector &view,
               const math::Vector &up,
               const float near,
               const float far
              ) : mImpl(new Impl) {
                setEyeViewUp(eye,
                             view,
                             up);
                setAspectRatio(16.0/9.0);
                setFOV(60.0);
                mImpl->near = near;
                mImpl->far = far;

}

void Camera::setEyeViewUp(const geometry::Point &eye,
                          const math::Vector &view,
                          const math::Vector &up) {
    mImpl->eye = eye;
    mImpl->axis_view = view.normalized();
    mImpl->axis_up = (up - (mImpl->axis_view * up.dot(mImpl->axis_view))).normalized();
    mImpl->axis_right = (mImpl->axis_view.cross(mImpl->axis_up)).normalized();
}

void Camera::setFOV(const float fov) {
  mImpl->fov = fov;
  mImpl->htanfov = tan(mImpl->fov * 0.5 * M_PI/180.0);
  mImpl->vtanfov = mImpl->htanfov/mImpl->aspect_ratio;
}

const math::Vector Camera::view(const float x, const float y) const {
  float xx = (2.0 * x - 1.0) * mImpl->htanfov;
  float yy = (2.0 * y - 1.0) * mImpl->vtanfov;

  return (math::Vector((mImpl->axis_up * yy) +
          (mImpl->axis_right * xx) +
          mImpl->axis_view).normalized());
}

void Camera::setAspectRatio(const float aspect_ratio) {
  mImpl->aspect_ratio = aspect_ratio;
  mImpl->vtanfov = mImpl->htanfov/mImpl->aspect_ratio;
}

Camera::~Camera() {

}

void Camera::render(const Scene &scene, Image &image, const int num_width_samples, const int num_height_samples) const {
  // try to get image from render globals
 ProgressMeter meter(image.getHeight(), "Render Time");
//  const Scene scene = renderGlobals.getScene();


  for (int r =0; r< image.getHeight(); ++r) {
    meter.update();
    #pragma omp parallel for
    for (int c = 0; c < image.getWidth(); ++c) {

      Color color;
      // for number of samples
      for (int w = 0; w < num_width_samples; ++w) {
        for (int h = 0; h < num_height_samples; ++h) {
          math::Vector direction = view(((float)c + 0.5 + (float)w/num_width_samples)/image.getWidth(), ((float)r + 0.5 + (float)h/num_height_samples)/image.getHeight());

          Ray ray(mImpl->eye, direction);
          ray.epsilon(0.0005);
          float thit;
          std::shared_ptr<DifferentialGeometry> dg = nullptr;
          std::shared_ptr<Primitive> prim = nullptr;
          if (scene.hit(ray, thit, dg, prim)) {
            // possibly pass in scene data too for lighting and reflections

            color += prim->shade(ray, dg);
          }
          else
            color += Color(0,0,0,1);

        }
      }
      /*
      math::Vector direction = view((float)c/image.getWidth(), (float)r/image.getHeight());
      Color color;
      Ray ray(mImpl->eye, direction);
      ray.epsilon(0.0005);
      float thit;
      std::shared_ptr<DifferentialGeometry> dg;
      std::shared_ptr<Primitive> prim;
      if (scene.hit(ray, thit, dg, prim)) {
        // possibly pass in scene data too for lighting and reflections
        color = prim->shade(dg);
      }
      else
        color = Color(0,0,0,1);

      */
      color *= 1.0/(num_width_samples * num_height_samples);
      image.setPixel(r,c,color);

    }
  }


}
}
}
