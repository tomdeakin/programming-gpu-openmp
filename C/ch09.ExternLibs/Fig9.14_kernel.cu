#include <cuda_runtime.h>

__global__ void cuda_kernel(int *A) {
  A[threadIdx.x + blockIdx.x * blockDim.x] += 1;
}

extern "C" {
void call_cuda_kernel(int *A, int N, cudaStream_t s) {
  cuda_kernel<<<N, 16, 0, s>>>(A);
}
}

