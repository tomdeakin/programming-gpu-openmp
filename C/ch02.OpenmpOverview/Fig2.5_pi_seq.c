/*

Name:   pi_seq

Description:  This is a sequential program to 
              numerically compute the integral of

                 4/(1+x*x) 
				  
              from 0 to 1.  The value of this integral 
              is pi -- which is great since it gives us 
              an easy way to check the answer.


History: Written by Tim Mattson, March 2023

*/

#include <stdio.h>
#include <omp.h>
static long num_steps = 1024*1024*1024;
double step;
int main()
{
   int i;
   double x, pi, sum = 0.0;
   double start_time, run_time;

   step = 1.0 / (double) num_steps;

   start_time = omp_get_wtime();

   for (i = 0; i < num_steps; i++) {
      x = (i + 0.5) * step;
      sum += 4.0 / (1.0 + x * x);
   }

   pi = step * sum;
   run_time = omp_get_wtime() - start_time;
   printf("pi = %lf, with %ld steps, in %lf secs\n ", pi, num_steps, run_time);
}
