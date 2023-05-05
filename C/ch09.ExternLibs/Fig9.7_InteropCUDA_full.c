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

  // Device pointers, allocated by CUDA
  double *d_A, *d_B, *d_C;
  cudaMalloc((void**)&d_A, sizeof(double)*N*N);
  cudaMalloc((void**)&d_B, sizeof(double)*N*N);
  cudaMalloc((void**)&d_C, sizeof(double)*N*N);

  // Host pointers -- must allocate space for all variables
  double *A = malloc(sizeof(double)*N*N);
  double *B = malloc(sizeof(double)*N*N);
  double *C = malloc(sizeof(double)*N*N);

  // Get the default OpenMP target device
  int dev = omp_get_default_device();

  // Associate external device pointers
  omp_target_associate_ptr(A, d_A, sizeof(double)*N*N, 0, dev);
  omp_target_associate_ptr(B, d_B, sizeof(double)*N*N, 0, dev);
  omp_target_associate_ptr(C, d_C, sizeof(double)*N*N, 0, dev);

  // Use blocking OpenMP target task to initalize CUDA arrays
  // Notice implicit mapping of host pointers to device pointers
  #pragma omp target
  #pragma omp loop collapse(2)
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      A[i*N+j] = 1.0; B[i*N+j] = 2.0; C[i*N+j] = 0.0;
    }
  }

  // Use cuBLAS for DGEMM, using the device pointers directly
  double alpha = 1.0; double beta = 0.0;
  cublasDgemm(handle, CUBLAS_OP_N, CUBLAS_OP_N, N, N, N, &alpha, d_A, N, d_B, N, &beta, d_C, N);

  // Copy back with *blocking* operation to ensure DGEMM completes
  cudaMemcpy(C, d_C, sizeof(double)*N*N, cudaMemcpyDeviceToHost);

  // Release pointers, invalidating the device memory
  omp_target_disassociate_ptr(A, dev);
  omp_target_disassociate_ptr(B, dev);
  omp_target_disassociate_ptr(C, dev);

  check_solution(C, N);
  printf("Success\n");

  cudaFree(d_A); cudaFree(d_B); cudaFree(d_C);
  free(A); free(B); free(C);
  cublasDestroy(handle);

}

