#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <omp.h>

int main(void) {

  int N = 1000000;
  double *A, *B, *C;
  // Allocate and initialize A, B, and C
  A = malloc(sizeof(double) * N);
  B = malloc(sizeof(double) * N);
  C = malloc(sizeof(double) * N);
  
  for (int i = 0; i < N; ++i) {
    A[i] = 1.0; B[i] = 2.0; C[i] = 0.0;
  }
  
  int num_devices = omp_get_num_devices();
  assert (num_devices > 0);
  assert (N % num_devices == 0);
  int len = N / num_devices;
  
  #pragma omp parallel num_threads(num_devices)
  {
    #pragma omp single
        if (num_devices != omp_get_num_threads()) exit(EXIT_FAILURE); 
    
    int tid = omp_get_thread_num();
    int start = tid * len;
    int end = start + len;
  
    #pragma omp target map(to: A[start:len], B[start:len]) \
                      map(from: C[start:len]) device(tid)
    {
      #pragma omp loop
      for (int i = start; i < end; ++i) {
              C[i] = A[i] + B[i];
      }
    }
  }

  // Check solution
  for (int i = 0; i < N; ++i) {
    assert(fabs(C[i] - 3.0) < 1.0E-8);
  }
  printf("Success\n");

  free(A);
  free(B);
  free(C);
}

