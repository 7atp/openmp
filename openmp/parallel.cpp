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
		// Work Loop, do some work by looping VERYBIG times
		for (div = 0; div < VERYBIG; div=div+8) {
			omp_set_num_threads(8);
#pragma omp parallel	
			{
				// increment check sum
#pragma omp critical
				{
					sum += 1;
				}
				double temp_total = 0;
				int k;
				double sumx = 0.0, sumy = 0.0;
				int j = omp_get_thread_num()+(div);
				// Calculate first arithmetic series
				sumx = 0.0;
				for (k = 0; k < j; k++)
					sumx = sumx + (double)k;
				// Calculate second arithmetic series
				sumy = 0.0;
				for (k = j; k > 0; k--)
					sumy = sumy + (double)k;
				if (sumx > 0.0)temp_total = temp_total + 1.0 / sqrt(sumx);
				if (sumy > 0.0)temp_total = temp_total + 1.0 / sqrt(sumy);
				#pragma omp critical
				{
					total = total + temp_total;
				}
			}
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