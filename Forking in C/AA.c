// AA.c


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void main () {
	int b, c1, c1a, d, c2, ee, f;
	int waitOne, waitOnePID;
	char *arg[1] = {0};

	b = fork();
	if (b < 0) {
		printf("\nFork for process B failed."); exit(0);
	}
	if (b == 0){
		execv("BB" , arg);
	}

	c1 = fork();
	if (c1 < 0) {
		printf("\nFork for process C1 failed."); exit(0);
	}
	if (c1 == 0){
		execv("CC" , arg);
	}

	c1a = fork();
	if (c1a < 0) {
		printf("\nFork for process C1a failed."); exit(0);
	}
	if (c1a == 0){
		execv("CC" , arg);
	}

	printf("\nPid %d Code AA: Created process Pid %d (codeBB), process Pid %d (codeCC) and process Pid %d(codeCC)", getpid(), b, c1, c1a);


	waitOnePID = wait(waitOne);

	printf("\nPid %d Code AA: Process Pid %d terminated." , getpid() ,  waitOnePID);

	d = fork();
	if (d < 0) {
		printf("\nFork for process D failed."); exit(0);
	}
	if (d == 0){
		execv("DD" , arg);
	}

	c2 = fork();
	if (c2 < 0) {
		printf("\nFork for process C2 failed."); exit(0);
	}
	if (c2 == 0){
		execv("CC" , arg);
	}

	ee = fork();
	if (ee < 0) {
		printf("\nFork for process EE failed."); exit(0);
	}
	if (ee == 0){
		execv("EE" , arg);
	}

	printf("\nPid %d Code AA: Created process Pid %d (code DD), process Pid %d (code CC) and process Pid %d (code EE)", getpid(), d, c2, ee);



	int killC1, killC1a, killC2;

	killC1 = kill(c1, SIGKILL);

	killC1a = kill(c1a, SIGKILL);

	killC2 = kill(c2, SIGKILL);

	usleep(250000);

	char read[500];
	printf("\nPlease provide an arbitrary string of characters: \n");
	scanf("%s" , read);

	int intRead;
	printf("\nPlease provide an arbitrary integer: \n");
	scanf("%d" , &intRead);

	char intString[11];
	sprintf(intString, "%ld", intRead);

	char myName[11] = "Ronit Kumar";


	char *passArgs[3] = {read, intString, myName};


	f = fork();
	if (f < 0) {
		printf("\nFork for process B failed."); exit(0);
	}
	if (f == 0){
		execv("FF" , passArgs);
	}

	exit(0);

}