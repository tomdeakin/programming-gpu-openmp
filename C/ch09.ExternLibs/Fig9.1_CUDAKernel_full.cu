#include <stdio.h>

void use(double *A, double *B, double *C, int N) {
  printf("A[1024]=%d\n", A[1024]);
  printf("B[1024]=%d\n", B[1024]);
  printf("C[1024]=%d\n", C[1024]);
}

// A CUDA kernel
__global__ void init(double *A, int N, double val) {
  const int i = blockDim.x * blockIdx.x + threadIdx.x;
  if (i < N)
    A[i] = val;
}

int main(void) {
  int N = 1024 * 1024;
  double *A, *B, *C;

  cudaMalloc(&A, sizeof(double)*N);
  cudaMalloc(&B, sizeof(double)*N);
  cudaMalloc(&C, sizeof(double)*N);

  // Create a CUDA stream
  cudaStream_t s;
  cudaStreamCreate(&s);

  // Launch three CUDA kernels in the stream
  int blocks = N / 64;
  int threads = 64;
  init<<<blocks, threads, 0, s>>>(A, N, 1.0);
  init<<<blocks, threads, 0, s>>>(B, N, 2.0);
  init<<<blocks, threads, 0, s>>>(C, N, 0.0);

  // Wait for work in stream to finish
  cudaStreamSynchronize(s);

  use(A,B,C,N); // 

  // Destroy stream
  cudaStreamDestroy(s);
  cudaFree(A);
  cudaFree(B);
  cudaFree(C);

  return 0;
}
