#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

void init(float *A, float *B, float *C, int Ndim, int Mdim, int Pdim) {
  for (int i = 0; i < Ndim; ++i) {
    for (int j = 0; j < Mdim; ++j) {
      C[i*Mdim+j] = 0.0;
    }
  }
  for (int k = 0; k < Pdim; ++k) {
    for (int j = 0; j < Mdim; ++j) {
      B[k*Ndim+j] = 2.0;
    }
  }
  for (int i = 0; i < Ndim; ++i) {
    for (int k = 0; k < Pdim; ++k) {
      A[i*Pdim+k] = 1.0;
    }
  }
}

void matmul(int Ndim, int Mdim, int Pdim,
            float *A, float *B, float *C) {
            
   
   init(A,B,C, Ndim, Mdim, Pdim);  // initialize the matrices
   
  #pragma omp target map(tofrom: A[0:Ndim*Pdim], B[0:Pdim*Mdim], C[0:Ndim*Mdim])
  #pragma omp loop collapse(2)
  for (int i = 0; i < Ndim; i++) {
    for (int j = 0; j < Mdim; j++) {
      for(int k = 0; k < Pdim; k++) {
	C[i*Mdim+j] += A[i*Pdim+k] * B[k*Mdim+j];
      }
    }
  }
}


int main(void) {
  int Ndim = 1024;
  int Mdim = 1024;
  int Pdim = 1024;

  float *A, *B, *C;
  A = (float *) malloc(Ndim*Pdim*sizeof(float));
  B = (float *) malloc(Pdim*Mdim*sizeof(float));
  C = (float *) malloc(Ndim*Mdim*sizeof(float));

  matmul(Ndim, Mdim, Pdim, A, B, C);

  // Check solution
  for (int i = 0; i < Ndim; ++i)
    for (int j = 0; j < Mdim; ++j)
      assert(fabs(C[i*Mdim+j] - 2.0*Pdim) < 1.0E-8);
  printf("Success\n");
}

