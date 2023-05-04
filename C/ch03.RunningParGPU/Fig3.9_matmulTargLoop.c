/*

Name:   matmul_TargLoop  ... Figure 2.14

Description:  This program generates test matrices, A and B,
                     for which the matrix product C+A*B is known 
                      analytically.    These matrices are then used to test
                      the matrix multiplication function in figure 2.8.
                      
                      This function can be tested using the mm_testbed program
                      
                                          
History: Written by Tim Mattson, April 2023

*/
#include<omp.h>
#define N 5000
void init(int M, float A[N][N], float B[N][N], float C[N][N]); // function not shown
int main() 
{
  float A[N][N], B[N][N], C[N][N];
  
  init(N, A, B, C);   // a user written function to fill A, B and C 
  
  #pragma omp target 
  #pragma omp loop 
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      for(int k = 0; k < N; k++) {
	C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
}
