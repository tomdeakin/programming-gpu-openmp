#include <omp.h>
#include <cuda_runtime.h>
#include <assert.h>

extern void call_kernel(cudaStream_t s);

int main(void) {
omp_interop_t iobj = omp_interop_none;
#pragma omp interop init(targetsync: iobj)

// Check we have a CUDA runtime
int err;
assert(omp_get_interop_int(iobj, omp_ipr_fr_id, &err) == omp_ifr_cuda);

// Get CUDA stream
cudaStream_t s = (cudaStream_t) omp_get_interop_ptr(iobj, omp_ipr_targetsync, NULL);

// Enqueue a CUDA kernel, a non-blocking operation
//kernel<<<32, 32, 0, s>>>(/* args */);
call_kernel(s);

#pragma omp interop destroy(iobj)
// kernel will be finished here
}
