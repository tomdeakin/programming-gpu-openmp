
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

struct span {
  int N;
  double *ptr;
};

int main(void) {

  struct span A, B, C;
  int N = 10000;
  A.N = N;
  B.N = N;
  C.N = N;
  A.ptr = malloc(sizeof(double) * A.N);
  B.ptr = malloc(sizeof(double) * B.N);
  C.ptr = malloc(sizeof(double) * C.N);
  
  for (int i = 0; i < N; ++i) {
    A.ptr[i] = 1.0;
    B.ptr[i] = 2.0;
    C.ptr[i] = 0.0;
  }
  
  #pragma omp target map(A.ptr[:A.N], B.ptr[:B.N], C.ptr[:C.N])
  #pragma omp loop 
  for (int i = 0; i < N; ++i) {
    C.ptr[i] = A.ptr[i] + B.ptr[i];
  }

  // Check results
  for (int i = 0; i < N; ++i) {
    assert(fabs(C.ptr[i] - 3.0) < 1.0E-6);
  }

  printf("Success\n");
  return EXIT_SUCCESS;
}
