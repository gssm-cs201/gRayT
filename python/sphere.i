%module grayt

%{
#define SWIG_FILE_WITH_INIT
#include <grayt/geometry/Sphere.h>
%}
//%ignore Sphere;
%include <grayt/geometry/Sphere.h>

