// PipeW1.c
// Ronit Kumar || Babic || 4/10/14
// gcc PipeW1.c -o ProcB
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void main(){
    int i,c;
    char buffer1[6];

	for(i = 0; i<500; i++){
		buffer1[0] = '0' + i;
	    buffer1[3] = 'a';
	    buffer1[4] = 'a';
	    buffer1[5] = 'a';
		c = write(x[1], &buffer1, 6);
	  	if(c<0){
	    	printf("\nError writing to pipeline in process A"); exit(0);
	  	}	
		exit(0);
	}
}