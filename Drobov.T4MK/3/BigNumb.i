%module BigNumb
%{
/* Includes the header in the wrapper code */
#include "BigNumb.h"
%}

/* Parse the header file to generate wrappers */
%include "BigNumb.h"