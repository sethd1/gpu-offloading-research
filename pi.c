/* Estimate pi as twice the area under a semicircle
 Command Lines are OPTIONAL to use: 
 	In order to specify the number of rectangles: -r <value>
	In order to specify the number of threads: -t <value>
*/	
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#ifdef _OPENMP
  #include <omp.h>
#endif


/* parameters that may be overridden on the command-line */
long n_rect = 10485760;         /* default number of rectangles */
int threadct = 1;               /* default number of OpenMP threads to use */

int main(int argc, char** argv) {

clock_t time = clock();
double a = -1.0, b = 1.0;  /* lower and upper interval endpoints */
double h;               /* width of a rectangle subinterval */
double f(double x);     /* declare function that defines curve */
double sum;             /* accumulates areas all rectangles so far */
long i;  /* loop control */
int option; /* used to get the option command from the user */

while ((option = getopt(argc, argv, "r::t::")) != -1)
	switch(option)
	{
		case 'r':
			n_rect = strtol(argv[2], NULL, 10);
			if (n_rect <= 0){
				printf("Number of Rectangles cannot be less than or equal to 0\n");
				exit (1);		
			}
			break;
		case 't':
			if (n_rect == 10485760){
				threadct = strtol(argv[2], NULL, 10);
			}else{
				threadct = strtol(argv[4], NULL, 10);
			}
			if (threadct <= 0){
				printf("Number of Threads cannot be less than or equal to 0\n");
				exit (1);
			}
			break;
		default:
			printf("Error in command-line argument(s)\n");
        		break;
			return 1;  /* indicates error exit */
	}

h = (b - a)/n_rect;

/* compute the estimate */
 sum = 0;
#pragma omp parallel for num_threads(threadct) \
shared (a, n_rect, h) private(i) reduction(+: sum)
#pragma acc parallel reduction(+: sum)
for (i = 0; i < n_rect; i++) {
     sum += f(a + (i+0.5)*h) * h;
}
time = clock() - time;
printf("With n = %d rectangles and %d threads, ", n_rect, threadct);
printf("the estimate of pi is %.20g\n", sum);
//printf("Total run time was: %f seconds\n", end-start);
printf("Total run time was : %f seconds.\n", 
           ((float)time) / CLOCKS_PER_SEC); 
return 0;
}

double f(double x) {
return 2*sqrt(1-x*x);
}
// Copyright © This work is licensed under a Creative Commons Attribution-ShareAlike 3.0 Unported License (St. Olaf College)
// Edits have been made by Dhruv Seth from the University of California, Irvine

