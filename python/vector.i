%module grayt
%include <std_shared_ptr.i>

%{
#define SWIG_FILE_WITH_INIT
#include <gssmraytracer/math/Vector.h>

%}
%include <gssmraytracer/math/Vector.h>
