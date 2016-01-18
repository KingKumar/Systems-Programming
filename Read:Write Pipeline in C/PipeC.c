// PipeC.c
// Ronit Kumar || Babic || 4/10/14
// gcc PipeC.c -o ProcA2
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void main(){
    int i,y,a,b,c;
    int x[2];
    char alpha[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char buffer1[6];
    char buffer2[3];
    char buffer3[100];
    char *arg[1] = {0};

    y = pipe(x);
	a = fork();
	if(a<0){
		printf("\nFork for process A failed."); exit(0);
	}
	if(a == 0){
		close(x[0]);
		execv("ProcB" , arg);
	}
	b = fork();
	if(b<0){
		printf("\nFork for process B failed."); exit(0);
	}
	if(b == 0){
		close(x[0]);
		execv("ProcC" , arg);
	}
	c = fork();
	if(c<0){
		printf("\nFork for process B failed."); exit(0);
	}
	if(c == 0){
		close(x[1]);
		execv("ProcD" , arg);
	}
	exit(0);
}