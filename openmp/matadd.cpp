#define _CRT_SECURE_NO_WARNINGS
#pragma optimize( "2", on )

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include <time.h>
#include <omp.h>

#pragma comment(lib, "winmm.lib")
typedef struct {
	int *A, *B, *C;
	int n, m;
} DataSet;

void fillDataSet(DataSet *dataSet);
void printDataSet(DataSet dataSet);
void closeDataSet(DataSet dataSet);
void add(DataSet dataSet);
void add_row(DataSet dataSet);
void add_col(DataSet dataSet);

void add_row128(DataSet dataSet);
void add_col128(DataSet dataSet);
int nt;
int main(int argc, char *argv[]) {
	double starttime, elapsedtime;
	double col = 0 , row = 0;
	DataSet dataSet;
	if (argc < 3) {
		printf("[-] Invalid No. of arguments.\n");
		printf("[-] Try -> <n> <m> \n");
		printf(">>> ");
		scanf("%d %d", &dataSet.n, &dataSet.m);
	}
	else {
		dataSet.n = atoi(argv[1]);
		dataSet.m = atoi(argv[2]);
	}
	fillDataSet(&dataSet);
	starttime = omp_get_wtime();
	//add(dataSet);
	elapsedtime = omp_get_wtime() - starttime;
	// report elapsed time
	//printf("serial Time Elapsed %f mSecs \n",elapsedtime * 1000);
	nt = 8;
	for (int i = 0; i < 9; i++) {
		starttime = omp_get_wtime();
		add_row128(dataSet);
		row += omp_get_wtime() - starttime;
		// report elapsed time
		
		starttime = omp_get_wtime();
		add_col128(dataSet);
		col += omp_get_wtime() - starttime;
		// report elapsed time
		
		//printDataSet(dataSet);
	}
	printf("row Time Elapsed %f mSecs   for threads %d \n",
		row * 100,nt);
	printf("col Time Elapsed %f mSecs   for threads  %d \n",
		col * 100,nt);

	row = 0;
	col = 0;
	nt = 4;
	for (int i = 0; i < 9; i++) {
		starttime = omp_get_wtime();
		add_row128(dataSet);
		row += omp_get_wtime() - starttime;
		// report elapsed time

		starttime = omp_get_wtime();
		add_col128(dataSet);
		col += omp_get_wtime() - starttime;
		// report elapsed time

		//printDataSet(dataSet);
	}
	printf("row Time Elapsed %f mSecs   for threads %d \n",
		row * 100, nt);
	printf("col Time Elapsed %f mSecs   for threads  %d \n",
		col * 100, nt);


	row = 0;
	col = 0;
	nt = 16;
	for (int i = 0; i < 9; i++) {
		starttime = omp_get_wtime();
		add_row128(dataSet);
		row += omp_get_wtime() - starttime;
		// report elapsed time

		starttime = omp_get_wtime();
		add_col128(dataSet);
		col += omp_get_wtime() - starttime;
		// report elapsed time

		//printDataSet(dataSet);
	}
	printf("row Time Elapsed %f mSecs   for threads %d \n",
		row * 100, nt);
	printf("col Time Elapsed %f mSecs   for threads  %d \n",
		col * 100, nt);


	row = 0;
	col = 0;
	nt = 1;
	for (int i = 0; i < 9; i++) {
		starttime = omp_get_wtime();
		add_row128(dataSet);
		row += omp_get_wtime() - starttime;
		// report elapsed time

		starttime = omp_get_wtime();
		add_col128(dataSet);
		col += omp_get_wtime() - starttime;
		// report elapsed time

		//printDataSet(dataSet);
	}
	printf("row Time Elapsed %f mSecs   for threads %d \n",
		row * 100, nt);
	printf("col Time Elapsed %f mSecs   for threads  %d \n",
		col * 100, nt);
	closeDataSet(dataSet);
	system("PAUSE");
	return EXIT_SUCCESS;
}

void fillDataSet(DataSet *dataSet) {
	int i, j;

	dataSet->A = (int *)malloc(sizeof(int) * dataSet->n * dataSet->m);
	dataSet->B = (int *)malloc(sizeof(int) * dataSet->n * dataSet->m);
	dataSet->C = (int *)malloc(sizeof(int) * dataSet->n * dataSet->m);

	srand(time(NULL));

	for (i = 0; i < dataSet->n; i++) {
		if(i%100==0){
			printf("one loop %d\n",i);
		}
		for (j = 0; j < dataSet->m; j++) {
			dataSet->A[i*dataSet->m + j] = rand() % 100;
			dataSet->B[i*dataSet->m + j] = rand() % 100;
		}
	}
}

void printDataSet(DataSet dataSet) {
	int i, j;

	printf("[-] Matrix A\n");
	for (i = 0; i < dataSet.n; i++) {
		for (j = 0; j < dataSet.m; j++) {
			printf("%-4d", dataSet.A[i*dataSet.m + j]);
		}
		putchar('\n');
	}

	printf("[-] Matrix B\n");
	for (i = 0; i < dataSet.n; i++) {
		for (j = 0; j < dataSet.m; j++) {
			printf("%-4d", dataSet.B[i*dataSet.m + j]);
		}
		putchar('\n');
	}

	printf("[-] Matrix C\n");
	for (i = 0; i < dataSet.n; i++) {
		for (j = 0; j < dataSet.m; j++) {
			printf("%-8d", dataSet.C[i*dataSet.m + j]);
		}
		putchar('\n');
	}
}

void closeDataSet(DataSet dataSet) {
	free(dataSet.A);
	free(dataSet.B);
	free(dataSet.C);
}

void add(DataSet dataSet) {
	int i, j;
	for (i = 0; i < dataSet.n; i++) {
		for (j = 0; j < dataSet.m; j++) {
			dataSet.C[i * dataSet.m + j] = dataSet.A[i * dataSet.m + j] + dataSet.B[i * dataSet.m + j];
		}
	}
}


void add_row(DataSet dataSet) {
	int i, j;
	omp_set_num_threads(nt);
	#pragma omp parallel 
	{
	#pragma omp for 
		for (i = 0; i < dataSet.n; i++) {
			for (j = 0; j < dataSet.m; j++) {
				dataSet.C[i * dataSet.m + j] = dataSet.A[i * dataSet.m + j] + dataSet.B[i * dataSet.m + j];
			}
		}
	}
}



void add_col(DataSet dataSet) {
	int i, j;

		for (i = 0; i < dataSet.n; i++) {
		omp_set_num_threads(nt);
		#pragma omp parallel 
			{
			#pragma omp for 
			for (j = 0; j < dataSet.m; j++) {
				dataSet.C[i * dataSet.m + j] = dataSet.A[i * dataSet.m + j] + dataSet.B[i * dataSet.m + j];
			}
		}
	}
}




void add_row128(DataSet dataSet) {
	int i, j,k;
	omp_set_num_threads(nt);
#pragma omp parallel 
	{
#pragma omp for 
		for (k = 0; k < dataSet.n; k=k+128) {
			//printf("number of threads %d     %d \n", omp_get_num_threads(),nt);
			for (i = k; i < k + 128 && i < dataSet.n; i++) {
				for (j = 0; j < dataSet.m; j++) {
					dataSet.C[i * dataSet.m + j] = dataSet.A[i * dataSet.m + j] + dataSet.B[i * dataSet.m + j];
				}
			}
		}
	}
}



void add_col128(DataSet dataSet) {
	int i, j,k;

	for (i = 0; i < dataSet.n; i++) {
		omp_set_num_threads(nt);
#pragma omp parallel 
		{
#pragma omp for 
			for (k = 0; k < dataSet.m; k = k + 128) {
				for (j = k; j < k + 128 && j < dataSet.m; j++) {
					dataSet.C[i * dataSet.m + j] = dataSet.A[i * dataSet.m + j] + dataSet.B[i * dataSet.m + j];
				}
			}
		}
	}
}