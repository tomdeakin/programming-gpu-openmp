#include <cuda_runtime.h>
__global__ void kernel() {}

extern "C" { 
void call_kernel(cudaStream_t s) {
  kernel<<<32, 32, 0, s>>>();
}
}
