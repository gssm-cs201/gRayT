#include "gssmraytracer/utils/Camera.h"
#include <OpenEXR/ImathVec.h>
#include "gssmraytracer/utils/RenderGlobals.h"
#include "gssmraytracer/utils/Color.h"
#include "gssmraytracer/utils/Ray.h"
#include "gssmraytracer/geometry/Shape.h"

using namespace gssmraytracer::geometry;

namespace gssmraytracer {
namespace utils {

  class Camera::Impl {
  public:
    Imath::Vec3<float> eye;
    Imath::Vec3<float> view;
    Imath::Vec3<float> up;
    Imath::Vec3<float> axis_view;
    Imath::Vec3<float> axis_up;
    Imath::Vec3<float> axis_right;
    float aspect_ratio;
    float htanfov;
    float vtanfov;
    float fov;
    float near;
    float far;

  };

Camera::Camera(): mImpl(new Impl) {
    setEyeViewUp(Imath::Vec3<float>(0,0,0),
                 Imath::Vec3<float>(0,0,1),
                 Imath::Vec3<float>(0,1,0));
    setAspectRatio(16.0/9.0);
    setFOV(60.0);
    mImpl->near = 0.0;
    mImpl->far = std::numeric_limits<float>::infinity();

}

Camera::Camera(const Imath::Vec3<float> &eye,
               const Imath::Vec3<float> &view,
               const Imath::Vec3<float> &up,
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

void Camera::setEyeViewUp(const Imath::Vec3<float> &eye,
                          const Imath::Vec3<float> &view,
                          const Imath::Vec3<float> & up) {
    mImpl->eye = eye;
    mImpl->axis_view = view.normalized();
    mImpl->axis_up = (up - (up.dot(mImpl->axis_view)) * mImpl->axis_view).normalize();
    mImpl->axis_right = (mImpl->axis_view.cross(mImpl->axis_up)).normalize();
}

void Camera::setFOV(const double fov) {
  mImpl->fov = fov;
  mImpl->htanfov = tan(mImpl->fov * 0.5 * M_PI/180.0);
  mImpl->vtanfov = mImpl->htanfov/mImpl->aspect_ratio;
}

const Imath::Vec3<float> Camera::view(const double x, const double y) const {
  double xx = (2.0 * x - 1.0) * mImpl->htanfov;
  double yy = (2.0 * y - 1.0) * mImpl->vtanfov;
  return (mImpl->axis_up * yy +
          mImpl->axis_right * xx +
          mImpl->axis_view).normalize();
}

void Camera::setAspectRatio(const double aspect_ratio) {
  mImpl->aspect_ratio = aspect_ratio;
  mImpl->vtanfov = mImpl->htanfov/mImpl->aspect_ratio;
}

Camera::~Camera() {

}

void Camera::render(RenderGlobals &renderGlobals) const {
  // try to get image from render globals
  Image image = renderGlobals.getImage();

//  const Scene scene = renderGlobals.getScene();
  for (int r =0; r< image.getHeight(); ++r) {
    for (int c = 0; c < image.getWidth(); ++c) {
      Imath::Vec3<float> direction = view((float)c/image.getWidth(), (float)r/image.getHeight());
      Color color;
      Ray ray(mImpl->eye, direction);
      float t0, t1;
      Imath::Vec3<float> hitpoint, normal;
      if (renderGlobals.hit(ray, t0, t1, hitpoint, normal)) {
        color = renderGlobals.shade(ray);
      }
      else
        color = Color(0,0,0,255);
//      color = scene.getShade(ray);
      image.setPixel(r,c,color);

    }
  }
  renderGlobals.setImage(image);


}
}
}
