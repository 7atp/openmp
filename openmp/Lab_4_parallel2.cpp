/*
*				In His Exalted Name
*	Title:	Prefix Sum Sequential Code
*	Author: Ahmad Siavashi, Email: siavashi@aut.ac.ir
*	Date:	29/04/2018
*/

// Let it be.
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>
#include <math.h>       /* log2 */
void omp_check();
void fill_array(int *a,int* b, size_t n);
void prefix_sum(int *a, size_t n);
void print_array(int *a, size_t n);
void prefix_sum_parallel(int *a, size_t n, int j);

int Tread_num = 8;
void final_add(int* a, int temp, size_t n, int j);
size_t minfunc(int a, int b) {


	if (a > b) {
		return size_t(b);
	}
	else return size_t(a);


}

int main(int argc, char *argv[]) {
	// Check for correct compilation settings
	omp_check();
	// Input N
	size_t n = 10;
	printf("[-] Please enter N: ");
	//scanf("%uld\n", &n);
	// Allocate memory for array
	int * a = (int *)malloc(n * sizeof a);
	int * b = (int *)malloc(n * sizeof b);
	int * c = (int *)malloc(n * sizeof b);
	int size = int(n / Tread_num);

	// Fill array with numbers 1..n
	fill_array(a, b,n);
	print_array(b, n);

	// Print array


	// Compute prefix sum






	int i = 0;
	int j;

	for (i = 0; i <= int(log2(n)); i++) {
		print_array(b, n);
		a = b;
		b = c;

#pragma omp parallel for num_threads(8)	private(j)
		for (j = 0; j < n; j++) {
			if (j < pow(2,i))
				b[j] = a[j];
			else {
				
				b[j] = a[j] + a[j - ((int)pow(2, i))]; }
		}
	}



	//#pragma omp parallel for num_threads(8) 
	//for (i = 0; i < 8; i++) {
	//	prefix_sum_parallel(a, minfunc((i + 1)*size,int(n)), i*size +1);
	//}
	//int temp[8] = {0,0,0,0,0,0,0,0};
	//for (i = 1; i < 8; i++) {
	//	temp[i] = temp[i - 1] + a[i*size - 1];
	//}

	//#pragma omp parallel for num_threads(7) 
	//for (i = 1; i < 8; i++) {
	//	final_add(a,temp[i],minfunc((i + 1)*size, int(n)), i*size );
	//}
	//
	//prefix_sum(a, n);
	// Print array

	print_array(b, n);
	system("pause");

	//printf("last %d ----- \n %d ",a[n-1],a[n-2]);
	// Free allocated memory
	free(a);
	free(b);
	free(c);

	system("pause");
	return EXIT_SUCCESS;
}




void print_array(int *a, size_t n) {
	int i;
	printf("[-] array: ");
	for (i = 0; i < n; ++i) {
		printf("%d, ", a[i]);
	}
	printf("\b\b  \n");
}

void fill_array(int *a,int *b, size_t n) {
	int i;
#pragma omp parallel for num_threads(8)	
	for (i = 0; i < n; ++i) {
		a[i] = i + 1;
		b[i] = a[i];
	}
}

void omp_check() {
	printf("------------ Info -------------\n");
#ifdef _DEBUG
	printf("[!] Configuration: Debug.\n");
#pragma message ("Change configuration to Release for a fast execution.")
#else
	printf("[-] Configuration: Release.\n");
#endif // _DEBUG
#ifdef _M_X64
	printf("[-] Platform: x64\n");
#elif _M_IX86 
	printf("[-] Platform: x86\n");
#pragma message ("Change platform to x64 for more memory.")
#endif // _M_IX86 
#ifdef _OPENMP
	printf("[-] OpenMP is on.\n");
	printf("[-] OpenMP version: %d\n", _OPENMP);
#else
	printf("[!] OpenMP is off.\n");
	printf("[#] Enable OpenMP.\n");
#endif // _OPENMP
	printf("[-] Maximum threads: %d\n", omp_get_max_threads());
	printf("[-] Nested Parallelism: %s\n", omp_get_nested() ? "On" : "Off");
#pragma message("Enable nested parallelism if you wish to have parallel region within parallel region.")
	printf("===============================\n");
}
