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
  int n = VECTOR_SIZE-1;

  for (i=0; i<=n; ++i) {
    A[i] = i+1;
    B[i] = 2*A[i];
  }

  struct timeval start, stop;
  gettimeofday(&start, NULL);

#pragma omp target device (0)
#pragma omp target map (to:A[0:n],B[0:n]) map (from:C[0:n]) 
 #pragma omp parallel for
  for (i=0; i<=n; ++i) {
    C[i] = alpha * A[i] + B[i];
  }

  gettimeofday(&stop, NULL);

  for (i = 0; i < n; i++) {
    printf("%.2f ", C[i]);
  }
  printf("\nExecuted program succesfully.\n");
  printf("execution time = %lf (ms)\n", (stop.tv_sec - start.tv_sec) * 1000 + (stop.tv_usec - start.tv_usec)*0.001);
  return 0;
									       
}


