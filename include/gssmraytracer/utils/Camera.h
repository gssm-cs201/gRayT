#include "gssmraytracer/geometry/Point.h"
#include "gssmraytracer/math/Vector.h"
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
    Camera(const geometry::Point &eye,
           const math::Vector &view,
           const math::Vector &up,
           const float near=1.0,
           const float far = std::numeric_limits<float>::infinity());
    ~Camera();
    void setEyeViewUp(const geometry::Point &eye,
                      const math::Vector &view,
                      const math::Vector &up);
    const math::Vector view(const float x, const float y) const;
    void setFOV(const float fov);
    void setAspectRatio(const float aspect_ratio);
    void render(RenderGlobals &renderGlobals) const;

    private:
    class Impl;
    std::shared_ptr<Impl> mImpl;

    };
}

}
