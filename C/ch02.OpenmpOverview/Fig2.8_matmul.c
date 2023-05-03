/*

Name:   matmul  ... Figure 2.8

Description:  This program generates test matrices, A and B,
                     for which the matrix product C+A*B is known 
                      analytically.    These matrices are then used to test
                      the matrix multiplication function in figure 2.8.
                      
                      This function can be tested using the mm_testbed program
                      
                                          
History: Written by Tim Mattson, April 2023

*/
#include "mm_utils.h"
//=========================================================
//  the function from figure 2.8
//========================================================= 

void mm_ijk_par(int N, int M, int P, double *A, double *B, double *C)
{
   int i, j, k;

   #pragma omp parallel 
   #pragma omp for collapse(2) private(k) schedule(static,10)  
   for (i=0; i<N; i++)
      for (j=0; j<M; j++)
	    for(k=0; k<P; k++)
	       *(C+(i*M+j)) += *(A+(i*P+k)) *  *(B+(k*M+j));
}
