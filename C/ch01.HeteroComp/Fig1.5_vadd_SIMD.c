/*

NAME:   vadd_SIMD

Description: Add two vectors using SIMD intrinsics

History: Written by Tim Mattson Feb 2023.

License: Creative Commons with Attribution (CC BY).  See the file ../../License for details

*/
#include <stdio.h>
#include <immintrin.h>
#include <assert.h>
#define N 4000

void init(double *A, double *B, double *C);

int main()
{

     double A[N] , B[N] , C[N] ;

     // 256 bit vector registers to be packed with double precision numbers
      __m256d Avec , Bvec , Cvec ;
      
      init(A,B,C); // initialize arrays 
      
      assert (N%4==0);
      
     for (int i=0; i < N; i=i+4){
           Avec = _mm256_loadu_pd(&A[ i ] ) ; 
           Bvec = _mm256_loadu_pd(&B[ i ] ) ; 
           Cvec = _mm256_add_pd(Avec,Bvec); 
           _mm256_storeu_pd(&C[i],Cvec);
     }
     
     // Test Results
     int nerr = 0;
     for (int i=0; i<N; i++) { 
         if((int)C[i] != 3*i+1) nerr++; 
     }
      printf("program complete with %d errors",nerr);
}

// initialize arrays 
void init (double *A, double*B,   double *C){

      for (int i=0; i<N; i++) { 
          A[ i ] = (double)  i; 
          B[i] =  (double) 2*i; 
          C[i] = 1.0; 
       }

}
