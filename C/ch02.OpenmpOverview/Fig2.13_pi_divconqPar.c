/*

Name:   pi_divconqPar ....  figure 2.13

Description:  This program computes numerically compute 
              the integral of

                 4/(1+x*x) 
				  
              from 0 to 1 to produce an estimate of pi
              
              This version of the program uses a serial divide
              and conquer algorithm


History: Written by Tim Mattson, April 2023

*/

#include <omp.h>
static long num_steps = 1024*1024*1024;
#define MIN_BLK 1024*256

double pi_comp(int Nstart,int Nfinish,double step)
{ 
   double x, sum = 0.0, sum1, sum2;
   if (Nfinish - Nstart < MIN_BLK) {
      for (int i = Nstart; i < Nfinish; i++){
         x = (i + 0.5) * step;
         sum = sum + 4.0 / (1.0 + x*x); 
      }
   }
   else {
      int iblk = Nfinish - Nstart;
      #pragma omp task shared(sum1)
          sum1 = pi_comp(Nstart, Nfinish - iblk/2, step);
      #pragma omp task shared(sum2)
          sum2 = pi_comp(Nfinish - iblk/2, Nfinish, step);
      #pragma omp taskwait
           sum = sum1 + sum2;
   }
   return sum;
}

int main ()
{
   double step, pi, sum;
   step = 1.0 / (double) num_steps;

    #pragma omp parallel 
         #pragma omp single
              sum = pi_comp(0, num_steps, step);

      pi = step * sum;
}  

