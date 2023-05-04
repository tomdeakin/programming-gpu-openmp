#include <omp.h>
#define N 4000

int main()
{
   float A[N];
   float alpha = 2.0;

   #pragma omp target
   for (int i = 0; i < N; i++) {
      A[i] = A[i] * alpha;
   }
}
