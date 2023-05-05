#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <omp.h>

void dgemm_cuda(double *A, double *B, double *C, int N, double alpha, double beta, omp_interop_t o);
void dgemm_xehp(double *A, double *B, double *C, int N, double alpha, double beta, omp_interop_t o);

void allocate_arrays(double **A, double **B, double **C, int N) {
  *A = malloc(sizeof(double)*N*N);
  *B = malloc(sizeof(double)*N*N);
  *C = malloc(sizeof(double)*N*N);
}

void check_solution(double *C, int N) {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      assert(C[i*N+j] == 2.0*(double)N);
    }
  }
}

#pragma omp declare variant(dgemm_cuda) match(construct={dispatch}, device={arch(nvptx)}) append_args(interop(targetsync)) adjust_args(need_device_ptr: A, B, C)
#pragma omp declare variant(dgemm_xehp) match(construct={dispatch}, device={arch(XeHP)}) append_args(interop(targetsync)) adjust_args(need_device_ptr: A, B, C)
void dgemm(double *A, double *B, double *C, int N, double alpha, double beta) {
  #pragma omp target nowait depend(inout: C[0:N*N])
  #pragma omp loop collapse(2)
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      C[i*N+j] *= beta;
      for (int k = 0; k < N; ++k) {
        C[i*N+j] += alpha*A[i*N+k] * B[k*N+j];
      }}}
}

int main(void) {
  int N = 10000;

  double *A, *B, *C;
  allocate_arrays(&A, &B, &C, N);

  #pragma omp target enter data map(alloc: A[0:N*N], B[0:N*N], C[0:N*N]) nowait depend(out: C[0:N*N])

  #pragma omp target nowait depend(inout: C[0:N*N])
  #pragma omp teams loop collapse(2)
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      A[i*N+j] = 1.0;
      B[i*N+j] = 2.0;
      C[i*N+j] = 0.0;
    }
  }

  // Asynchronous call to dgemm, substituted by a matching replacement
  #pragma omp dispatch nowait depend(inout: C[0:N*N])
  dgemm(A, B, C, N, 1.0, 0.0);

  #pragma omp target exit data map(from: C[0:N*N]) map(delete: A, B) depend(in: C[0:N*N])

  check_solution(C, N);
  printf("Success\n");
}

