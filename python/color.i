%module grayt
%include <std_shared_ptr.i>

%{
#define SWIG_FILE_WITH_INIT
#include <gssmraytracer/utils/Color.h>
%}
%include <gssmraytracer/utils/Color.h>
