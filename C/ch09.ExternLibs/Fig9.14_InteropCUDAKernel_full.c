#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <cuda_runtime.h>

extern void call_cuda_kernel(int * A, int N, cudaStream_t s);

int main(void) {

  int N = 100000;
  int *A = (int *)malloc(sizeof(int) * N);
  #pragma omp target enter data map(alloc: A[:N])
  
  #pragma omp target nowait depend(out: A)
  for (int i = 0; i < N; ++i)
    A[i] = i;
  
  omp_interop_t iobj = omp_interop_none;
  #pragma omp interop init(targetsync: iobj) nowait depend(inout: A)
  
  // Check we have a CUDA runtime
  int err;
  if (omp_get_interop_int(iobj, omp_ipr_fr_id, &err) != omp_ifr_cuda) {
    printf("Wrong interop runtime\n");
    exit(EXIT_FAILURE);
  }
  
  // Get CUDA stream
  cudaStream_t s = (cudaStream_t) omp_get_interop_ptr(iobj, omp_ipr_targetsync, NULL);
  
  // Asynchronously enqueue CUDA kernel on the stream
  #pragma omp target data use_device_ptr(A)
  call_cuda_kernel(A, N, s);
  
  #pragma omp interop use(iobj) nowait depend(inout: A)
  
  #pragma omp target nowait depend(inout: A)
  for (int i = 0; i < N; ++i)
    A[i] += 1;
  
  #pragma omp interop use(iobj) nowait depend(inout: A)
  
  #pragma omp target data use_device_ptr(A)
  call_cuda_kernel(A, N, s);
  
  #pragma omp interop destroy(iobj) nowait depend(inout: A)
  
  #pragma omp taskwait

  #pragma omp target exit data map(from: A[:N])

  // Check solution
  for (int i = 0; i < N; ++i)
    if (A[i] != i + 3) {
      printf("Incorrect %d\n", A[i]);
      exit(EXIT_FAILURE);
    }

  printf("Success\n");

  free(A);
}

