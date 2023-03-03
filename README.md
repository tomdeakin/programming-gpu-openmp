 
 For any code we use in the book, we need to have a program we can run that tests it.  This is the directory where we put that code.
 
 We'll work out naming conventions later.  I suggest we use the following:
 
The naming conventions are:Fig_x.x_name.c, and the corresponding _Fortran, or *.f, or *.f90, such as Fig_1.1_helloworld.c and Fig_1.1_helloworld.f90. "x.x" is the figure number in the�book, and "name" is the label used in the latex source file of the book for this figure.

We can use the suffix _C or _Fortran means the code is not complete, thus could not be compiled.

*.c, *.f90, *.f are codes that are complete and could be compiled. If a code has external functions that are not defined, or is just a subroutine, then it can only be built with the "-c" flag to generate an object�file, and I add a comment in the source code for these.

A few codes also have Fig_x.x_name_full.c and Fig_x.x_name_full.f90. This is to provide full codes (more than what we show in the book).

There are a few extra Chxx_pgyy_code_C or Chxx_pgyy_code_Fortran codes. These are code segments in the book in Chapter xx, Page yy, that are not a figure.

