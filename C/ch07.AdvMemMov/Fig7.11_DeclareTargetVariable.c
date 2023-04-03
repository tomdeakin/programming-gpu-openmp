
#include <stdlib.h>

#define N 10000
int A[N];

#pragma omp declare target (A)

int main(void) {
  #pragma omp target
  for (int i = 0; i < N; ++i)
    A[i] = i;

  // etc

  return EXIT_SUCCESS;
}

