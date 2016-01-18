// DD.c

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void main () {
	int c3, unixOne;
	int waitTwo, waitTwoPID;
	int killC3;
	char *arg[1] = {0};
	char *comOne[4] = {"ps" , "-u" , "kumarro" , 0};

	c3 = fork();
	if (c3 < 0) {
		printf("\nFork for process C3 failed."); exit(0);
	}
	if (c3 == 0){
		execv("CC" , arg);
	}

	printf("\nPid %d Code DD: Created process Pid %d (code CC) and waiting for 3 seconds" , getpid(), c3);

	usleep(500000);

	unixOne = fork();
	if (unixOne < 0) {
		printf("\nFork for process with Unix command failed."); exit(0);
	}
	if (unixOne == 0){
		execv("Compiler" , comOne);
	}

	waitTwoPID = wait(waitTwo);

	killC3 = kill(c3, SIGKILL);
}