%module grayt
%include <std_shared_ptr.i>

%{
#define SWIG_FILE_WITH_INIT
#include <grayt/math/Vector.h>

%}
%include <grayt/math/Vector.h>
