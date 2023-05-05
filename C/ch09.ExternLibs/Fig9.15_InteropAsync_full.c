#include <cuda_runtime.h>
#include "cublas_v2.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <omp.h>

void check_solution(double *C, int N) {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      assert(C[i*N+j] == 2.0*(double)N);
    }
  }
}


int main(void) {
  int N = 10000;
  cublasHandle_t handle; cublasCreate(&handle);

  double *A = malloc(sizeof(double)*N*N);
  double *B = malloc(sizeof(double)*N*N);
  double *C = malloc(sizeof(double)*N*N);

  #pragma omp target enter data \ 
             map(alloc: A[0:N*N], B[0:N*N], C[0:N*N]) \
             nowait depend(out: C[0:N*N])

  #pragma omp target nowait depend(inout: C[0:N*N])
  #pragma omp teams loop collapse(2)
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      A[i*N+j] = 1.0;
      B[i*N+j] = 2.0;
      C[i*N+j] = 0.0;
    }
  }

  omp_interop_t o = omp_interop_none; // interop object

  #pragma omp interop init(targetsync: o) nowait \
        depend(inout: C[0:N*N])

  // Get and set CUDA stream (assuming it's a CUDA backend)
  cudaStream_t s = omp_get_interop_ptr(o, omp_ipr_targetsync, NULL);
  cublasSetStream(handle, s);

  // Replace pointers with device pointers
  #pragma omp target data use_device_ptr(A, B, C)
  {
    // Call DGEMM
    double alpha = 1.0; double beta = 0.0;
    cublasDgemm(handle, CUBLAS_OP_N, CUBLAS_OP_N, N, N, N, 
                     &alpha, A, N, B, N, &beta, C, N);
  } 

  #pragma omp interop destroy(o) nowait depend(out: C[0:N*N])
  // NB: If I wanted to reuse the stream, I would instead have
  // #pragma omp interop use(o) nowait depend(out: C[0:N*N])

  // Copy C back to the host, blocking to ensure host 
  // waits for previous tasks
  #pragma omp target update from(C[0:N*N]) depend(in: C[0:N*N])

  check_solution(C, N);
  printf("Success\n");

  #pragma omp target exit data \
          map(delete: A[0:N*N], B[0:N*N], C[0:N*N])

  cublasDestroy(handle);

}

