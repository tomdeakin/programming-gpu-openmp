
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define N 4000

int main()
{

   float A[N], B[N], C[N];
   // initialization
   for (int i = 0; i < N; ++i) {
     A[i] = 1.0f; B[i] = 2.0f; C[i] = 0.0f;
   }

   #pragma omp target
   #pragma omp teams distribute parallel for
   for (int i = 0; i < N; i++) {
      C[i] = A[i] + B[i];
   }

   // Check solution
   for (int i = 0; i < N; i++) {
     assert(fabs(C[i] - 3.0f) < 1.0E-5);
   }
   printf("Success\n");
   return EXIT_SUCCESS;
}
