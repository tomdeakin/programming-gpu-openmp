#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <omp.h>

int main(void) {

  int N = 1000000;
  double *A, *B;
  // Allocate and initialize
  A = malloc(sizeof(double)*N);
  B = malloc(sizeof(double)*N);
  for (int i = 0; i < N; ++i) {
    A[i] = 1.0/(double)N;
    B[i] = (double)N;
  }

  double sum = 0.0;
  
  int num_devices = omp_get_num_devices();
  assert (N % num_devices == 0);
  int len = N / num_devices;
  
  #pragma omp taskgroup task_reduction(+:sum)
  {
    for (int dev = 0; dev < num_devices; ++dev) {
      int start = dev * len;
      int end = start + len;
  
      #pragma omp target map(to: A[start:len], B[start:len]) device(dev) in_reduction(+:sum) nowait
      {
        #pragma omp loop reduction(+: sum)
        for (int i = start; i < end; ++i) {
          sum += A[i] * B[i];
        }
      }
    }
  }

  assert(fabs(sum - (double)N) < 1.0E-8);
  printf("Success\n");

  free(A);
  free(B);
}
