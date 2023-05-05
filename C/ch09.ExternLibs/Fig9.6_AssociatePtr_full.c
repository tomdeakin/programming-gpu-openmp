#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <cuda_runtime.h>
#include <omp.h>

int main(void) {
  const int N = 1000;
  
  // Allocate array on the host
  double * h_A = malloc(sizeof(double) * N);
  
  double * d_A = NULL;
  
  // Allocate on device using external library
  cudaMalloc((void **)&d_A, sizeof(double)*N);
  
  int dev = omp_get_default_device();
  
  omp_target_associate_ptr(h_A, d_A, sizeof(double)*N, 0, dev);
  
  #pragma omp target device(dev)
  #pragma omp teams loop
  for (int i = 0; i < N; ++i) {
    h_A[i] = (double) i;
  }

  #pragma omp target update from(h_A[:N])
  
  omp_target_disassociate_ptr(h_A, dev);
  cudaFree(d_A);

  // Check solution
  for (int i = 0; i < N; ++i)
    assert(h_A[i] == (double) i);

  printf("Success\n");

  free(h_A);
}

