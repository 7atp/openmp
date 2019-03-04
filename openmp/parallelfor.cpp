// Example Program
// Optimizes code for maximum speed
#pragma optimize( "2", on )
#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include <math.h>
#include <omp.h>
// Adds an additional library so that timeGetTime() can be used
#pragma comment(lib, "winmm.lib")
const long int VERYBIG = 10000;
// ***********************************************************************
int main(void)
{
	int i;
	long int  sum;
	double  total;
	DWORD starttime, elapsedtime;
	// -----------------------------------------------------------------------
	// Output a start message
	printf("None Parallel Timings for %d iterations\n\n", VERYBIG);
	// repeat experiment several times

	for (i = 0; i < 6; i++)
	{
		// get starting time56 x CHAPTER 3 PARALLEL STUDIO XE FOR THE IMPATIENT
		starttime = timeGetTime();
		// reset check sum & running total
		sum = 0;
		total = 0.0;
		float div = 0;
		int j =0;
		double temp_total[8];
		int k[8];
		double sumx[8], sumy[8];
		// Work Loop, do some work by looping VERYBIG times
		for (div = 0; div < VERYBIG; div = div + 8) {
			#pragma omp parallel 
			{
				#pragma omp for 
				for (j = 0; j < 8; j++) {

					// increment check sum
#pragma omp critical
					{
						sum += 1;
					}
					int l = j + div;
					temp_total[j]= 0;
					
					sumx[j] = 0.0;
					sumy[j] = 0.0;

					// Calculate first arithmetic series
					for (k[j] = 0; k[j] < l; k[j]++)
						sumx[j] = sumx[j] + (double)k[j];
					// Calculate second arithmetic series
					sumy[j] = 0.0;
					for (k[j] = l; k[j] > 0; k[j]--)
						sumy[j] = sumy[j] + (double)k[j];
					if (sumx[j] > 0.0)temp_total[j] = temp_total[j] + 1.0 / sqrt(sumx[j]);
					if (sumy[j] > 0.0)temp_total[j] = temp_total[j] + 1.0 / sqrt(sumy[j]);
#pragma omp critical
					{
						total = total + temp_total[j];
					}
				}}
		}
		// get ending time and use it to determine elapsed time
		elapsedtime = timeGetTime() - starttime;
		// report elapsed time
		printf("Time Elapsed % 10d mSecs Total = %lf Check Sum = %ld\n",
			(int)elapsedtime, total, sum);
	}
	system("pause");	// return integer as required by function header
	return 0;
}
// **********************************************************************