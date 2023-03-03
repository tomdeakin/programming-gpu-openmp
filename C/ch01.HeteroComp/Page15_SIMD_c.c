
For example, the sequence over packed doubles with 256 bit vector instructions:

   Cvec = _mm256_add_pd(Avec,Bvec);
   Dvec = _mm256_add_pd(Avec,Cvec);
   Fvec = _mm256_add_pd(Bvec,Dvec);
   
can be considered as four SIMD lanes:

SIMD-Lane0: C[0] = A[0] + B[0]; D[0] = A[0]+C[0]; F[0] = B[0] + D[0];
SIMD-Lane1: C[1] = A[1] + B[1]; D[1] = A[1]+C[1]; F[1] = B[1] + D[1];
SIMD-Lane2: C[2] = A[2] + B[2]; D[2] = A[2]+C[2]; F[2] = B[2] + D[2];
SIMD-Lane3: C[3] = A[3] + B[3]; D[3] = A[3]+C[3]; F[3] = B[3] + D[3];

