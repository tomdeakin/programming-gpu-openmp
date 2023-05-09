
#include <omp.h>
#include <stdio.h>
static long num_steps = 100000000;
int main() {
  double sum = 0.0;
  double step = 1.0 / (double)num_steps;

  #pragma omp target map(tofrom:sum)
  #pragma omp loop reduction(+:sum)
  for (int i = 0; i < num_steps; i++) {
    double x = (i + 0.5) * step;
    sum += 4.0 / (1.0 + x * x);
  }

  double pi = step * sum;
  printf(" pi with %ld steps is %lf\n", num_steps, pi);
}

