#include <omp.h>
#include <stdio.h>
#include <sys/time.h>

#define VECTOR_SIZE 1000

int main() {
  int i;
  float alpha = 2.0;
  // Allocate space for vectors A, B and C
  float *A = (float*)malloc(sizeof(float)*VECTOR_SIZE);
  float *B = (float*)malloc(sizeof(float)*VECTOR_SIZE);
  float *C = (float*)malloc(sizeof(float)*VECTOR_SIZE);
  int n = 1000;

  // Initialize vectors A & B
  for (i = 0; i < n; i++) {
    A[i] = (float)i;
    B[i] = (float)(i * 2);
  }

  struct timeval start, stop;
  gettimeofday(&start, NULL);

#pragma omp target map(to: A[0:n], B[:n]) map(from: C[:n]) device (0)
  {
    #pragma omp parallel for
    for (i=0; i<n; ++i)
      C[i] = alpha * A[i] + B[i];
  }

  gettimeofday(&stop, NULL);

  for (i = 0; i < n; i++)
    {
      printf("%.2f ", C[i]);
    }
  printf("\nExecuted program succesfully.\n");
  printf("Execution time = %lf (ms)\n", (stop.tv_sec - start.tv_sec) * 1000 + (stop.tv_usec - start.tv_usec)*0.001);

  return 0;
}

