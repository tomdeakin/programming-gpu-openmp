#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

int N = 4000; 

void init(float *A, float *B, float *C, int N) {
  for (int i = 0; i < N; ++i) {
    A[i] = 1.0; B[i] = 2.0; C[i] = 0.0;
  }
}

int main()
{

   float * A = malloc(sizeof(float) * N);
   float * B = malloc(sizeof(float) * N);
   float * C = malloc(sizeof(float) * N);

   init(A,B,C,N); // Set initial values

   #pragma omp target map(to: A[0:N], B[0:N]) map(from: C[0:N])
   #pragma omp loop
   for (int i = 0; i < N; i++) {
      C[i] = A[i] + B[i];
   }

   // Check solution
   for (int i = 0; i < N; ++i) {
     assert(fabs(C[i] - 3.0) < 1.0E-8);
   }
   printf("Success\n");
}	  
