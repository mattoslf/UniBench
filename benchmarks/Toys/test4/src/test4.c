#include <omp.h>
#include <stdio.h>

#define VECTOR_SIZE 100000
#define THRESHOLD 20000

int main() {
  int i;
  float value;
  // Allocate space for vectors A, B and C
  float A[VECTOR_SIZE];
  float B[VECTOR_SIZE];
  float C[VECTOR_SIZE];
  int n = 10000;

  // Initialize vectors A & B
  for (i = 0; i < n; i++) {
    A[i] = (float)i;
    B[i] = (float)(i * 2);
  }

#pragma omp target device(0)
#pragma omp target data map(to: A, B) map(from: C)
  {
    #pragma omp target
    #pragma omp parallel for
    for (i=0; i<n; ++i) {
      C[i] = A[i] + B[i];
    }

    #pragma omp target update from(C) if (n<=10000)
    value = C[500];
    
    // Re-initialize vectors B
    for (i = 0; i < n; i++) {
      B[i] = (float)(i * 4);
    }

    #pragma omp target
    #pragma omp parallel for
    for (i=0; i<n; ++i) {
      C[i] = A[i] + B[i];
    }

  }

  if ((C[500] - value) == 1000) {
    printf("\nExecuted program succesfully.\n");
  }

  return 0;
}

