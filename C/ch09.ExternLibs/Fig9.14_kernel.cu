#include <cuda_runtime.h>
#include <cstdio>

__global__ void cuda_kernel(int *A, int N) {
  const int tid = threadIdx.x + blockIdx.x * blockDim.x;
  if (tid < N)
    A[tid] += 1;
}

extern "C" {
void call_cuda_kernel(int *A, int N, cudaStream_t s) {
  cuda_kernel<<<N, 1, 0, s>>>(A, N);
}
}

