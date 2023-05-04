#include <math.h>
#include <omp.h>
struct complex {
  float real;
  float imag;
};

int main()
{
   struct complex data = {.real = 1.0f, .imag = 2.0f};
   float len[1];

   #pragma omp target
   {
     len[0] = sqrtf(data.real * data.real + data.imag * data.imag);
   }
}	  

