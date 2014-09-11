#include <OpenEXR/ImathVec.h>
#include <limits>
#include <memory>

namespace gssmraytracer {
namespace utils {
    class RenderGlobals; // forward declaration
    class Camera {
    public:
    // Default Constructor
    Camera();
    // Set eye, view and up vectors
    Camera(const Imath::Vec3<float> &eye,
           const Imath::Vec3<float> &view,
           const Imath::Vec3<float> &up,
           const float near=1.0,
           const float far = std::numeric_limits<float>::infinity());
    ~Camera();
    void setEyeViewUp(const Imath::Vec3<float> &eye,
                      const Imath::Vec3<float> &view,
                      const Imath::Vec3<float> &up);
    const Imath::Vec3<float> view(const double x, const double y) const;
    void setFOV(const double fov);
    void setAspectRatio(const double aspect_ratio);
    void render(RenderGlobals &renderGlobals) const;

    private:
    class Impl;
    std::shared_ptr<Impl> mImpl;

    };
}

}
