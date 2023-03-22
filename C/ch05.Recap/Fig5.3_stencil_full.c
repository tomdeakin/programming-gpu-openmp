/*
* PROGRAM: heat equation solve
*
* PURPOSE: This program will explore use of an explicit
*          finite difference method to solve the heat
*          equation under a method of manufactured solution (MMS)
*          scheme. The solution has been set to be a simple 
*          function based on exponentials and trig functions.
*
*          A finite difference scheme is used on a 1000x1000 cube.
*          A total of 0.5 units of time are simulated.
*
*          The MMS solution has been adapted from
*          G.W. Recktenwald (2011). Finite difference approximations
*          to the Heat Equation. Portland State University.
*
*
* USAGE:   Run with two arguments:
*          First is the number of cells.
*          Second is the number of timesteps.
*
*          For example, with 100x100 cells and 10 steps:
*
*          ./heat 100 10
*
*
* HISTORY: Written by Tom Deakin, Oct 2018
*
* LICENSE: Creative Commons with Attribution (CC BY).  See the file ../../License for details
*
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define PI acos(-1.0) // Pi

// Sets the mesh to an initial value, determined by a MMS scheme
void initial_values(const int n, const double dx, const double length, double * restrict u) {
  double y = dx;
  for (int j = 0; j < n; ++j) {
    double x = dx; // Physical x position
    for (int i = 0; i < n; ++i) {
      u[i+j*n] = sin(PI * x / length) * sin(PI * y / length);
      x += dx;
    }
    y += dx; // Physical y position
  }
}

// Set the n-by-n array u_tmp to zero
void zero(int n, double *u_tmp) {
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      u_tmp[i+j*n] = 0.0;
}

int main(int argc, char *argv[]) {
  int n = 1000;		// Problem size, forms an nxn grid
  int nsteps = 10;	// Number of timesteps
  double alpha = 0.1;	// heat equation coefficient
  double length = 10000;// physical size of domain: length x length square
  double dx = length/(n+1);// physical size of each cell  
  double dt = 0.5 / nsteps;	// time interval (total time of 0.5s)
  double r = alpha * dt / (dx * dx); // Stability
  if (r > 0.5) printf("WARNING: Unstable!\n");

  // Allocate two nxn grids
  double *u  = malloc(sizeof(double)*n*n);
  double *u_tmp = malloc(sizeof(double)*n*n);
  double *tmp;

  initial_values(n, dx, length, u);
  zero(n, u_tmp);
  
  const double r2 = 1.0 - 4.0*r;
  for (int t = 0; t < nsteps; ++t) {
  
  #pragma omp target map(tofrom: u[0:n*n], u_tmp[0:n*n])
  #pragma omp loop collapse(2)
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        u_tmp[i+j*n] =  r2 * u[i+j*n] +
        r * ((i < n-1) ? u[i+1+j*n] : 0.0) +
        r * ((i > 0)   ? u[i-1+j*n] : 0.0) +
        r * ((j < n-1) ? u[i+(j+1)*n] : 0.0) +
        r * ((j > 0)   ? u[i+(j-1)*n] : 0.0);
      }
    }
    // Pointer swap
    tmp = u;
    u = u_tmp;
    u_tmp = tmp;
  }

  // Check solution against the known solution defined by the MMS
  double l2norm = 0.0;
  double t = dt * (double)nsteps; // total time
  double y = dx;
  for (int i = 0; i < n; ++i) {
    double x = dx;
    for (int j = 0; j < n; ++j) {
      double correct = exp(-2.0*alpha*PI*PI*t/(length*length)) *
        sin(PI*x/length) * sin(PI*y/length);
      double tmp = u[i+j*n] - correct;
      l2norm += tmp * tmp;
      x += dx;
    }
    y += dx;
  }
  l2norm = sqrt(l2norm);

  printf("Error l2norm: %lf\n", l2norm);

  free(u);
  free(u_tmp);

  return EXIT_SUCCESS;
}

