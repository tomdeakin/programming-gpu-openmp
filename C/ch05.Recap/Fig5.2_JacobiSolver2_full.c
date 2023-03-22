/*

NAME: Jacobi Solver with target data region

Description: Solves the linear system Ax=b using the Jacobi method

History: Written by Tom Deakin and Tim Mattson March 2023.

License: Creative Commons with Attribution (CC BY).  See the file ../../License for details
*/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TOLERANCE 0.001
#define MAX_ITERS 100000

void initializeProblem(int N, double *A, double *b, double *xold, double *xnew) {

  // Create a random, diagonally dominant matrix
  // After randomly initalizing the matrix, add the sum of 
  // the row to the diagonal element on that row,
  // then scale by that sum
  for (int i = 0; i < N; i++) {
    double sum = 0.0;
    for (int j = 0; j < N; j++) {
      A[i * N + j] = (rand() % 23) / 1000.0;
      sum += A[i * N + j];
    }
    A[i * N + i] += sum;

    // scale the row so the final matrix is almost an identity matrix
    for (int j = 0; j < N; j++)
      A[i * N + i] /= sum;
  }
}

int main() {
  int iters = 0,   N = 1000; // A[N][N]
  double conv=100000.0, err, *A, *b, *xold, *xnew;
  A = (double *)malloc(N * N * sizeof(double));
  b = (double *)malloc(N * sizeof(double));
  xold = (double *)malloc(N * sizeof(double));
  xnew = (double *)malloc(N * sizeof(double));
  initializeProblem(N,A,b,xold,xnew);

#pragma omp target data map(to: xold[0:N], A[0:N*N], b[0:N]) \
                                         map(to:xnew[0:N])
{
  while ((conv > TOLERANCE) && (iters < MAX_ITERS)) {
    iters++;
    
    #pragma omp target 
    #pragma omp loop 
    for (int i = 0; i < N; i++) {
      xnew[i] = (double)0.0;
      for (int j = 0; j < N; j++) 
        if (i != j)   xnew[i] += A[i * N + j] * xold[j];
      xnew[i] = (b[i] - xnew[i]) / A[i * N + i];
    }
    // test convergence
    conv = 0.0;
    
  #pragma omp target map(tofrom: conv)
  #pragma omp loop reduction(+ : conv)
   for (int i = 0; i < N; i++) {
     double tmp = xnew[i] - xold[i];
     conv += tmp * tmp;
    }
    conv = sqrt(conv);

    // pointer swap
    double* tmp = xold;
    xold = xnew;
    xnew = tmp;
  }
  #pragma omp target update from(xnew[0:N])
} // end of target data region

  // Check solution by multiplying xnew by A and comparing to b
  // reuse xold to store the result
  err = 0.0;
  for (int i = 0; i < N; ++i) {
    xold[i] = 0.0;
    for (int j = 0; j < N; ++j) {
      xold[i] += A[i * N + j] * xnew[j];
    }
    double tmp = xold[i] - b[i];
    err += tmp * tmp;
  }
  err = sqrt(err);

  printf("Jacobi Solver: err = %lf\n", err);

  free(A);
  free(b);
  free(xold);
  free(xnew);

  if (err > TOLERANCE) {
    printf("\nWARNING: final solution error > %g\n\n", TOLERANCE);
    return EXIT_FAILURE;
  }
  else
    return EXIT_SUCCESS;
}
