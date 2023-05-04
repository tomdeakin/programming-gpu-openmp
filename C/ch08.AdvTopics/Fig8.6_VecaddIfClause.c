
// A, B, C are initialized arrays of length N
void vecadd(double *A, double *B, double *C, int N) {
  int threshold = 10000000;

  #pragma omp target map(to: A[:N], B[:N]) map(from: C[:N]) if(N >= threshold)
  {
    #pragma omp loop
    for (int i = 0; i < N; ++i) {
	    C[i] = A[i] + B[i];
    }
  }
}

