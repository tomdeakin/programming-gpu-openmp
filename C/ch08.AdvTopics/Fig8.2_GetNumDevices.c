#include <stdio.h>
#include <omp.h>

int main() {
  printf("There are %d devices\n", omp_get_num_devices());
}

