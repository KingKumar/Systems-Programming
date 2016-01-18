// PipeW2.c
// Ronit Kumar || Babic || 4/10/14
// gcc PipeW2.c -o ProcC
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void main(){
    int b,c;
    char alpha[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char buffer2[3];

    b = 0;
	for(i = 0; i<260; i++){
		if(i%10 == 0 && i != 0){
			b++;
		}
        buffer2[0] = alpha[i%26];
        buffer2[1] = 'x';
        buffer2[2] = '0' + b;
		c = write(x[1], &buffer2, 3);
  		if(c<0){
    		printf("\nError writing to pipeline in process B"); exit(0);
  		}
	} 
	exit(0);
}