
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void initA(int *A, int N);
void initB(int *B, int N);
void initC(int *C, int N);

int main(void) {

  const int N = 1024;
  int *A = malloc(sizeof(int)*N); initA(A,N);
  int *B = malloc(sizeof(int)*N); initB(B,N);
  int *C = malloc(sizeof(int)*N); initC(C,N);
  
  #pragma omp target data map(tofrom: A[0:N], B[0:N], C[0:N])
  {
    //use_A_B_C_on_device(A,B,C);
    #pragma omp target
    {
      for (int i = 0; i < N; ++i) {
        C[i] += A[i] + B[i];
        A[i] += 2;
      }
    }
  
    // Copy A to the host
    #pragma omp target update from(A[0:N])
  
    // Reinitialize the array
    initA(A,N);
  
    // Copy A back to the device
    #pragma omp target update to(A[0:N])
  
    //use_A_C_on_device(A,C);
    #pragma omp target
    {
      for (int i = 0; i < N; ++i)
        C[i] += A[i];
    }
  }

  // Check solution
  for (int i = 0; i < N; ++i) {
    assert(C[i] == (1 + 2 + 3) + 1);
  }
  printf("Success\n");
}

void initA(int *A, int N) {
  for (int i = 0; i < N; ++i)
    A[i] = 1;
}

void initB(int *B, int N) {
  for (int i = 0; i < N; ++i)
    B[i] = 2;
}

void initC(int *C, int N) {
  for (int i = 0; i < N; ++i)
    C[i] = 3;
}

