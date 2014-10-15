#include "gssmraytracer/geometry/Point.h"
#include "gssmraytracer/math/Vector.h"
#include <limits>
#include <memory>

namespace gssmraytracer {
namespace utils {
    class RenderGlobals; // forward declaration
    /** \example example_camera.cpp
     * This is an example of how to use the Camera class.
     *
     */
    class Camera {
    public:
    /*! \brief initializes a camera class
     *
     * Sets the eye to (0,0,0), the view to (0,0,1) and the up to (0,1,0)
     */
    Camera();

    //! Set eye, view and up vectors, as well as a near and far plane
    Camera(const geometry::Point &eye,
           const math::Vector &view,
           const math::Vector &up,
           const float near=1.0,
           const float far = std::numeric_limits<float>::infinity());

    //! Destructor
    ~Camera();

    //! Sets the eye, view and up for the camera
    void setEyeViewUp(const geometry::Point &eye,
                      const math::Vector &view,
                      const math::Vector &up);

    /*! \brief returns a direction vector based on an x and y position
     *
     * The x and y values must be in a range between 0 and 1
     */
    const math::Vector view(const float x, const float y) const;

    //! Sets the fov for the camera
    void setFOV(const float fov);

    //! Sets the aspect ratio of the camera
    void setAspectRatio(const float aspect_ratio);

    //! Renders the scene using information from renderGlobals
    void render(RenderGlobals &renderGlobals) const;

    private:
    class Impl;
    std::shared_ptr<Impl> mImpl;

    };


}

}
