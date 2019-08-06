#include <stdlib.h>
#include <stdint.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define HASHES 1800

int runs;
long unsigned delta_us, total_us, HperS, avgHperS;
struct timespec start, end;

void calcHperS()
{
	delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
        total_us += delta_us;
        HperS = HASHES*1000000/delta_us;
        printf("\tThe speed was about %li H/s.\n\n", HperS);
}

void conclusionHperS()
{
	avgHperS =HASHES*1000000/(total_us/runs);
        printf("\nThe average Hashes per Seconds are %li.\n", avgHperS);
        printf("For %i runs the programm needed %lu milliseconds.\n", runs, total_us/1000);
}

int main(int argc, char **argv)
{
	int id, wait_param;
	//struct timespec start, end;
	char test[]="./test.out";

	if(argc!=2)
        {
                printf("Too few parameters!\n");
                return 1;
        }

	wait_param = 0;
	runs = atoi(argv[1]);

	for(int i=0; i<runs; i++)
	{
		clock_gettime(CLOCK_MONOTONIC_RAW, &start);
		id = fork();
		if (id == -1)
			exit(1);
		if (id == 0)
		{
			printf("WPA2 Wrapper is now executing...\n");
			execl(test, test, NULL);
			exit(1);
		}
		wait(&wait_param);
		clock_gettime(CLOCK_MONOTONIC_RAW, &end);
		calcHperS();
	}
	conclusionHperS();
	return 0;
}
