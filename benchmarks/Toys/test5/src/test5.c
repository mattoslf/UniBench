#include <omp.h>
#include <stdio.h>
#include <sys/time.h>

const int VECTOR_SIZE = 100000;

int main() {
  int i;
  int n = VECTOR_SIZE;
  // Allocate space for vectors A, B and C
  float A[VECTOR_SIZE];
  float B[VECTOR_SIZE];
  float C[VECTOR_SIZE];

  // Initialize vectors A & B
  for (i = 0; i < n; i++) {
    A[i] = (float)i;
    B[i] = (float)(i * 2);
  }

  struct timeval start, middle, stop;
  gettimeofday(&start, NULL);
  for (i = 0; i < n; i++) {
    C[i] = A[i] + B[i];
  }

  // Measure the time of sequential execution
  gettimeofday(&middle, NULL);

  #pragma omp target map (to:A, B) map (from:C) device (0)
  #pragma omp parallel for
  for (i = 0; i < n; i++) {
    C[i] = A[i] + B[i];
  }
  
  // Measure the time of parallel execution
  gettimeofday(&stop, NULL);

  printf("\nExecuted program succesfully.\n");
  printf("Sequential Execution time = %lf (ms)\n", (middle.tv_sec - start.tv_sec) * 1000 + (middle.tv_usec - start.tv_usec)*0.001);
  printf("Parallel (GPU) Execution time = %lf (ms)\n", (stop.tv_sec - middle.tv_sec) * 1000 + (stop.tv_usec - middle.tv_usec)*0.001);
  return 0;
}

