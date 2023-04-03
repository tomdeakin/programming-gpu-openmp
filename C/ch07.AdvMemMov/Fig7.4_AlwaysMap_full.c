
#include <stdio.h>

int main(void) {
  int N = 1;
  #pragma omp target data map(alloc: N)
  {
    #pragma omp target map(always,tofrom: N)
    {
      N += 1;
    }
  
    printf("%d\n", N);
  
    #pragma omp target map(always,from: N)
    {
      N += 1;
    }
  }
  printf("%d\n", N);
}

