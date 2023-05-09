#include <stdlib.h>
#include <stdio.h>

int main(void) {
  int N = 1024;
  int *A = malloc(sizeof(int)*N);

  // Take a copy of the A pointer
  int *orig_A = A;

  #pragma omp target data map(from: A[0:N])
  {
    #pragma omp target 
    #pragma omp loop
    for (int i = 0; i < N; ++i) {
      A[i] = i;
    }

    // Set A to NULL before end of target data region
    A = NULL;
  }

  // Notice how the array is copied to the old location,
  // now only available at orig_A
  printf("orig_A[%d] = %d\n", N/2, orig_A[N/2]);

}
