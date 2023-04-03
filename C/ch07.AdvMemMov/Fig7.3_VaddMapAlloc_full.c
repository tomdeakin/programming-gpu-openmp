
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

inline double initA(int i) { return 1.0; }
inline double initB(int i) { return 2.0; }

int main(void) {
  int N = 10000;
  double * A = malloc(sizeof(double)*N);
  double * B = malloc(sizeof(double)*N);
  double * C = malloc(sizeof(double)*N);
  
  #pragma omp target enter data map(alloc: A[0:N], B[0:N], C[0:N])
  
  #pragma omp target
  #pragma omp loop
  for (int i = 0; i < N; ++i) {
    A[i] = initA(i);
    B[i] = initB(i);
    C[i] = 0.0;
  }
  
  #pragma omp target
  #pragma omp loop
  for (int i = 0; i < N; ++i)
    C[i] = A[i] + B[i];
  
  #pragma omp target update from(C[0:N])
  
  #pragma omp target exit data map(release: A[0:N], B[0:N], C[0:N])

  for (int i = 0; i < N; ++i) {
    assert(fabs(C[i] - 3.0) < 1.0E-6);
  }
  printf("Success\n");
}

