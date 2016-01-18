// EE.c

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void main() {
	//Buffer to transfer read bytes
	char buffer = 'a';

	//Integer variables to hold return value of various system calls
  	int x, y, z, a;

  	//Opening of x.y for read
  	x = open("XYZ.txt" , 0);
  	if(x<0){
    	printf("Error opening file"); exit(0);
  	}
  
    printf("\nPid %d Code EE: This is what I have read from XYZ.txt: " , getpid()); 


	  //While loop to print byte by byte from XYZ.txt
  	do
  	{
  		//Read bytes from XYZ.txt
  	  	y = read(x, &buffer, 1);
  	  	if(y<0){
  	    	printf("Error reading file"); exit(0);
  	  	}
  	  	printf("%c", buffer);
  	} while (y > 0);

	  //Close XYZ.txt  
  	z = close(x);
  	if(z<0){
    	printf("Error closing file"); exit(0);
  	}


  	//Delete XYZ.txt
  	a = unlink("XYZ.txt");
  	if(a<0){
    	printf("Error deleting file"); exit(0);
  	}

    printf("\nPid %d Code EE: Deleted XYZ.txt and terminating." , getpid());

  	exit(0);

}