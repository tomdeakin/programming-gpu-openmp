/*

Name:   pi_loop

Description:  This program computes numerically compute 
              the integral of

                 4/(1+x*x) 
				  
              from 0 to 1 to produce an estimate of pi
              This version of the program uses the loop
              level parallelism pattern.


History: Written by Tim Mattson, March 2023

*/

#include <stdio.h> 
#include <omp.h>

static long num_steps = 1024*1024*1024; 


int main ()
{
   double x, pi , step , sum = 0.0; 
   int numthreads;
   double start_time, run_time;
   step = 1.0 / (double) num_steps;
    
   start_time = omp_get_wtime(); 

   #pragma omp parallel 
   {

       #pragma omp single
          numthreads = omp_get_num_threads();

       #pragma omp for private(x) reduction(+:sum) 
           for (int i=0; i<num_steps; i++){
               x = (i + 0.5) * step;
               sum = sum + 4.0 / (1.0 + x*x);
           }
    }

    pi = step * sum;
    run_time = omp_get_wtime() - start_time;
    printf("pi = %lf, with %ld steps, in %lf secs\n ", pi, num_steps, run_time);
}
