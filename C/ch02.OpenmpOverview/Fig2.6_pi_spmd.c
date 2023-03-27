/*

Name:   pi_spmd

Description:  This program computes numerically compute 
              the integral of

                 4/(1+x*x) 
				  
              from 0 to 1 to produce an estimate of pi
              This version of the program uses the Single 
              Program Multiple Data (SPMD) pattern.


History: Written by Tim Mattson, March 2023

*/

#include <stdio.h> 
#include <omp.h>

static long num_steps = 1024*1024*1024; 


int main ()
{
   int numthreads;
   double pi , step , full_sum = 0.0; 
   double start_time, run_time;
   step = 1.0 / (double) num_steps;
    
   start_time = omp_get_wtime(); 
   #pragma omp parallel 
   {
       int id = omp_get_thread_num(); 
       double x, partial_sum = 0.0;

       #pragma omp single
          numthreads = omp_get_num_threads();

       for (int i = id; i < num_steps; i += numthreads) { 
           x = (i + 0.5) * step;
           partial_sum += 4.0 / (1.0 + x*x);
       }
       #pragma omp critical
          full_sum += partial_sum;
    }
     
    pi = step * full_sum;
    run_time = omp_get_wtime() - start_time;
    printf("pi = %lf, with %ld steps, in %lf secs\n ", pi, num_steps, run_time);
}
