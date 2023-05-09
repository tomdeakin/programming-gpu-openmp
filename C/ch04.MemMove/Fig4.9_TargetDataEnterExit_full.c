
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void initA(int *A, int N);
void initB(int *B, int N);
void use(int *A, int *B, int N);

int main(void) {

  const int N = 1024;
  int *A = malloc(sizeof(int)*N); initA(A,N);
  int *B = malloc(sizeof(int)*N); initB(B,N);
  
  #pragma omp target enter data map(to: A[0:N], B[0:N])
  
  #pragma omp target 
  #pragma omp loop
  for (int i = 0; i < N; ++i)
    A[i] += 1;
  
  #pragma omp target 
  #pragma omp loop
  for (int i = 0; i < N; ++i)
    B[i] += 2;
  
  #pragma omp target 
  #pragma omp loop
  for (int i = 0; i < N; ++i)
    A[i] += B[i];
  
  #pragma omp target exit data map(from: A[0:N], B[0:N])
  
  // Continue using A and B on the host
  use(A, B, N);
}

void initA(int *A, int N) {
  for (int i = 0; i < N; ++i)
    A[i] = 1;
}

void initB(int *B, int N) {
  for (int i = 0; i < N; ++i)
    B[i] = 2;
}

void use(int *A, int *B, int N) {
  for (int i = 0; i < N; ++i)
    assert(A[i] == 1 + 1 + 2 + 2);
  printf("Success\n");
}
