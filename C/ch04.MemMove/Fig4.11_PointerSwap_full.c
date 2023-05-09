#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define N 100000
#define niters 100

void init_A(float *A_old, float *A_new) {
  for (int i = 0; i < N; ++i) {
    A_old[i] = 1.0f;
    A_new[i] = 1.0f; // With both set to 1, the answer should remain as 1
  }
}

void print_results(float *A_old, float *A_new) {
  for (int i = 1; i < N-1; ++i) {
    assert(fabs(A_old[i] - 1.0f) < 1.0E-6);
  }
  printf("Success\n");
}

int main(void) {

  float *A_old = malloc(sizeof(float)*N);
  float *A_new = malloc(sizeof(float)*N);

  init_A(A_old, A_new); // Initialize the data

  // Loop over a fixed number of iterations
  for (int it = 0; it < niters; ++it) {

    // Loop over the array, computing the average of
    // the neighbouring elements of the array
    #pragma omp parallel for
    for (int i = 1; i < N-1; ++i) {
      A_new[i] = (A_old[i-1] + A_old[i] + A_old[i+1]) / 3.0f;
    }

    // Swap pointers!
    float *temp = A_new;
    A_new = A_old;
    A_old = temp;

  } // End of iteration it loop

  print_results(A_old, A_new);
}
