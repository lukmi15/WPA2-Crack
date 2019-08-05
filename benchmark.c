// benchmark.c
#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char **argv){
        char test[]="./test.out";
        int x;
        char b2[255];
	clock_t y = clock()/CLOCKS_PER_SEC;

//Error-Catch
        if(argc!=2)
        {
                printf("Zu wenig Argumente!\n");
                return 1;
        }

        x=atoi(argv[1]);
        ////printf("flip - argv[1]=%i - PID=%i\n", x ,getpid());
        ////fflush(stdout);
        ////sleep(1);

        sprintf(b2, "%i", --x);
        execl(test, test, b2, (char *)0);
	/*for(int i=0; i<x; i++){
		y = clock()/CLOCKS_PER_SEC;
		printf("Zeit: %ld\n", y);
		usleep(333);
	}*/
        return 0;
}

