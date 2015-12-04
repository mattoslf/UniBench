// ----------------------------------------------------------------------------------------
// Implementation of Example target.3c (Section 52.3, page 196) from Openmp 4.0.2 Examples 
// on the document http://openmp.org/mp-documents/openmp-examples-4.0.2.pdf
//
// 
//
//
// ----------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

void init(float* a, float* b, int n) {
	int i;

	for(i=0;i<n;i++) {
		a[i] = i/2.0;
		b[i] = ((n-1)-i)/3.0;
	}

	return;
}

void output(float* a, int n) {
	int i;

	for(i=0;i<n;i++) printf("%f ", a[i]);
	printf("\n");

	return;
}

void vec_mult(int n) {
	int i;
	float p[n], v1[n], v2[n];

	init(v1, v2, n);

	#pragma omp target map(to: v1[:n], v2[:n]) map(from: p[:n]) device(0)
	#pragma omp parallel for
	for (i=0; i<n; i++)
		p[i] = v1[i] * v2[i];

	output(p, n);
}

int main(int argc, char * argv[]) {
	vec_mult(1000);
	return 0;
}
