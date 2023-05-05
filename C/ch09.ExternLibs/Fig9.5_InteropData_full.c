#include <cuda_runtime.h>
#include "cublas_v2.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void check_solution(double *C, int N) {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      assert(C[i*N+j] == 2.0*(double)N);
    }
  }
}

int main(void) {  
  int N = 10000;

  // Initalize cuBLAS Library
  cublasHandle_t handle;
  cublasCreate(&handle);

  double *A = malloc(sizeof(double)*N*N);
  double *B = malloc(sizeof(double)*N*N);
  double *C = malloc(sizeof(double)*N*N);

  #pragma omp target enter data \
               map(alloc: A[0:N*N], B[0:N*N], C[0:N*N])

  #pragma omp target teams loop collapse(2)
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      A[i*N+j] = 1.0;
      B[i*N+j] = 2.0;
      C[i*N+j] = 0.0;
    }
  }
  // Note: Blocking target call to synchronize OpenMP

  #pragma omp target data use_device_addr(A, B, C)
  {
    double alpha = 1.0;  double beta = 0.0;
    cublasDgemm(handle, CUBLAS_OP_N, CUBLAS_OP_N, N, N, N, &alpha, A, N, B, N, &beta, C, N);

    // Synchronize with CUDA device before returning (ensure all work finished)
    cudaDeviceSynchronize();
  }

  #pragma omp target exit data map(from: C[0:N*N]) \
           map(delete: A[0:N*N], B[0:N*N])

  // Check solution
  check_solution(C, N);
  printf("Success\n");

  cublasDestroy(handle);
}
