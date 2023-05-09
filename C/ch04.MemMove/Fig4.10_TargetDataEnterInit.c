#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void init_array(int *A, int N) {
  for (int i = 0; i < N; ++i)
    A[i] = i;

  #pragma omp target enter data map(to: A[0:N])
}

int main(void) {

  int N = 1024;
  int *A = malloc(sizeof(int) * N);
  init_array(A, N);

#pragma omp target 
#pragma omp loop
  for (int i = 0; i < N; ++i) {
    A[i] = A[i] * A[i];
  }

  #pragma omp target exit data map(from: A[0:N])

  // Check solution
  for (int i = 0; i < N; ++i)
    assert(A[i] == i * i);
  printf("Success\n");
}
