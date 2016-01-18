// FF.c

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void main (int argc, char *argv[]) {
	printf("\n Arg1: %s \n", argv[0]);
	printf("\n Arg2: %s \n", argv[1]);
	printf("\n Arg3: %s \n", argv[2]);

	exit(0);
}