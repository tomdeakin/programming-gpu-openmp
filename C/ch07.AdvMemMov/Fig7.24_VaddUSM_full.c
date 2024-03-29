
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

void init(double *A, double *B, double *C, const int N) {
  for (int i = 0; i < N; ++i) {
    A[i] = 1.0; B[i] = 2.0; C[i] = 0.0;
  }
}

int main(void) {

  int N = 1000000;
  double *A, *B, *C;

  // Notice *host* allocation
  A = malloc(N*sizeof(double));
  B = malloc(N*sizeof(double));
  C = malloc(N*sizeof(double));
  init(A, B, C, N);

  #pragma omp requires unified_shared_memory
  
  #pragma omp target
  #pragma omp loop
  for (int i = 0; i < N; ++i)
    C[i] = A[i] + B[i];
  
  // check solution
  for (int i = 0; i < N; ++i) {
    assert(fabs(C[i] - 3.0) < 1.0E-6);
  }
  printf("Success\n");
  return EXIT_SUCCESS;
}

