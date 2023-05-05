
#include <cuda_runtime.h>
#include "cublas_v2.h"

#include <omp.h>
#include <assert.h>

void dgemm_cuda(double *A, double *B, double *C, int N, double alpha, double beta, omp_interop_t o) {
  // Initalize cuBLAS Library
  cublasHandle_t handle;
  assert(cublasCreate(&handle) == CUBLAS_STATUS_SUCCESS);

  // Get CUDA stream
  cudaStream_t s = (cudaStream_t)omp_get_interop_ptr(o, omp_ipr_targetsync, NULL);

  // Tell cuBLAS to use the CUDA stream
  assert(cublasSetStream(handle, s) == CUBLAS_STATUS_SUCCESS);

  // Call dgemm from cuBLAS
  assert(cublasDgemm(handle, CUBLAS_OP_N, CUBLAS_OP_N, N, N, N, &alpha, A, N, B, N, &beta, C, N) == CUBLAS_STATUS_SUCCESS);

  cublasDestroy(handle);
}
