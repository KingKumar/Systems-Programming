// PipeR.c
// Ronit Kumar || Babic || 4/10/14
// gcc PipeR.c -o ProcD
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void main(){
    int c;
    char buffer3[100];

	do
	{
	  //Read 100 bytes from pipeline
	  c = read(x[0], &buffer3, 100);
	  if(c<0){
	    printf("\nError reading from pipeline"); exit(0);
	  }
	  printf("\n%s", buffer3);
	} while (c > 0);
    printf("\nterminating\n");
	exit(0);
}