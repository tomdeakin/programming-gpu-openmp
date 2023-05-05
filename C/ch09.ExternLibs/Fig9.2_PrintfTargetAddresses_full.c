#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int var = 42;
  
  printf("Host address of var is %p\n", &var);
  
  // Map var to the device
  #pragma omp target data map(var)
  {
  
    // Update var on the device
    #pragma omp target
    var = var + 1;
  
    printf("Address of var in target data region is %p\n", &var);
  
    // Use device address of var
    #pragma omp target data use_device_addr(var)
    {
      printf("Device address of var is %p\n", &var);
    }
  
  }

  return EXIT_SUCCESS;
}
