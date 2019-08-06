#include <stdlib.h>
#include <stdint.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>


int main(int argc, char **argv)
{
	int runs, id, wait_param;
	struct timespec start, end;
	long unsigned delta_us, total_us, HperS;
	char test[]="./test.out";

	if(argc!=2)
	{
		printf("No arguments given!\n");
		return 1;
	}

	wait_param = 0;
	total_us = 0;
	runs = atoi(argv[1]);
	for(int i=0; i<runs; i++)
	{
		clock_gettime(CLOCK_MONOTONIC_RAW, &start);

		//do stuff
		id = fork();
		if (id == -1)
			exit(1);
		if (id == 0)
		{
			printf("child is now executing\n");
			//execl("/usr/bin/mpirun", "mpirun", "--use-hwthread-cpus", "test.out", NULL);
			execl(test, test, (char *)0);
			exit(1);
		}
		printf("waiting for children\n");
		wait(&wait_param);
		clock_gettime(CLOCK_MONOTONIC_RAW, &end);
		delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
		total_us += delta_us;
		printf("It took %lu microseconds\n", delta_us);
	}
	HperS =/*xxx Hashes /*/total_us/runs;
	printf("Success, yay! \\(\")/\n");
	printf("The average time for xxx Hashes was %li microseconds\n", HperS);
	//das folgende printf ist nur zum Vergleich zum time Aufruf gedacht
	printf("Comparision between total_us and the time argument: %lu\n", total_us);
	return 0;
}
