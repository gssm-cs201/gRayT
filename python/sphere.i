%module grayt

%{
#define SWIG_FILE_WITH_INIT
#include <gssmraytracer/geometry/Sphere.h>
%}
//%ignore Sphere;
%include <gssmraytracer/geometry/Sphere.h>

