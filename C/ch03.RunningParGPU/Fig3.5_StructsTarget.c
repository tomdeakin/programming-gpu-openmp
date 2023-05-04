struct complex {
  float real;
  float imag;
};

struct complex data = {.real = 1.0f, .imag = 2.0f};

#pragma omp target
{
  data.real *= 2.0f;
  data.imag *= 2.0f;
}

// On the host, data is {.real = 2.0f, .imag = 4.0f}