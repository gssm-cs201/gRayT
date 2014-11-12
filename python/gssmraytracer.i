%module grayt
%include <std_shared_ptr.i>
%include "color.i"
%include "vector.i"
%include "point.i"
%include "ray.i"
%include "transform.i"
%include "bbox.i"
%include "image.i"
%include "scene.i"
%include "camera.i"
%include "differentialgeometry.i"
%include "shape.i"
%include "perlinnoise.i"
%include "sphere.i"

%{
#define SWIG_FILE_WITH_INIT
%}
