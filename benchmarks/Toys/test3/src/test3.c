#include <omp.h>
#include <stdio.h>
#include <sys/time.h>

#define VECTOR_SIZE 100000

int main() {
  int i;
  float value;
  // Allocate space for vectors A, B and C
  float *A = (float*)malloc(sizeof(float)*VECTOR_SIZE);
  float *B = (float*)malloc(sizeof(float)*VECTOR_SIZE);
  float *C = (float*)malloc(sizeof(float)*VECTOR_SIZE);
  int n = VECTOR_SIZE-1;
  
  struct timeval start, stop;
  gettimeofday(&start, NULL);

#pragma omp target device(0)
#pragma omp target data map(to: A[0:n], B[:n]) map(from: C[:n])
  {

  // Initialize vectors A & B
  for (i = 0; i < n; i++) {
    A[i] = (float)i;
    B[i] = (float)(i * 2);
  }
  
  #pragma omp target
  #pragma omp parallel for
  for (i=0; i<n; ++i) {
    C[i] = A[i] + B[i];
  }
  
  value = C[500];
  // Re-initialize vectors A & B
  for (i = 0; i < n; i++) {
    A[i] = (float)(i * 2);
    B[i] = (float)(i * 4);
  }

  #pragma omp target
  #pragma omp parallel for
  for (i=0; i<n; ++i) {
    C[i] = A[i] + B[i];
  }

  gettimeofday(&stop, NULL);

  if (C[500] == (2 * value)) {
    printf("\nExecuted program succesfully.\n");
    printf("Execution time = %lf (ms)\n", (stop.tv_sec - start.tv_sec) * 1000 + (stop.tv_usec - start.tv_usec)*0.001);
  }
  
  }
  return 0;
}

