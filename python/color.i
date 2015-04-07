%module grayt
%include <std_shared_ptr.i>

%{
#define SWIG_FILE_WITH_INIT
#include <grayt/utils/Color.h>
%}
%include <grayt/utils/Color.h>
