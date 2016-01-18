// PipeRW.c
// Ronit Kumar || Babic || 4/10/14
// gcc PipeRW.c -o ProcA
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
    y = pipe(x);
	a = fork();
	if(a<0){
		printf("\nFork for process A failed."); exit(0);
	}
	if(a == 0){
		close(x[0]);
		for(i = 0; i<500; i++){
			buffer1[0] = '0' + i;
            buffer1[3] = 'a';
            buffer1[4] = 'a';
            buffer1[5] = 'a';
			c = write(x[1], &buffer1, 6);
  			if(c<0){
    			printf("\nError writing to pipeline in process A"); exit(0);
  			}	
		} 
		exit(0);
	}
	b = fork();
	if(b<0){
		printf("\nFork for process B failed."); exit(0);
	}
	if(b == 0){
		close(x[0]);
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
	close(x[1]);
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