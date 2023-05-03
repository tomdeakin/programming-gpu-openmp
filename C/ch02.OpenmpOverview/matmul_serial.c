/*

Name:   mm_ijk... a serial version of Figure 2.8 but without OpenMP directives

Description:  This function is called within the mm_testbed program
                     for exploring matrix multiplication functions.
                      
History: Written by Tim Mattson, April 2023

*/
#include "mm_utils.h"

//=========================================================
//  the function from figure 2.8 but without OpenMP pragmas
//========================================================= 

void mm_ijk(int N, int M, int P, TYPE *A, TYPE *B, TYPE *C)
{
   int i, j, k;

   for (i=0; i<N; i++)
      for (j=0; j<M; j++)
	    for(k=0; k<P; k++)
	       *(C+(i*M+j)) += *(A+(i*P+k)) *  *(B+(k*M+j));
}

