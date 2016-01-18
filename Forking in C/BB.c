// BB.c



#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

 void main(){
  //Character array used as a buffer for read/ write from x.y
  char buffer1[200];

  //Integer variables to hold return value of various system calls
  int x, y, z, a, b, c, d, e;

  //Integer variables to keep track of bytes read and written
  int readCount, cursor;

  printf("\nPid %d Code BB: Creating file XYZ.txt and write 200 characters from file x.y" , getpid());

  //Creation of XYZ.txt
  x = creat("XYZ.txt" , S_IRWXU);
  if(x<0){
    printf("Error creating file"); exit(0);
  }

  //Opening of x.y for read
  y = open("/usr/class/cis660/x.y" , 0);
  if(y<0){
    printf("Error opening file"); exit(0);
  }

   //Update and initialize counter variables
  readCount = 0;
  
  //Do while loop for file read/ write
  do
  {
    //Read 200 bytes from x.y
  	z = read(y, &buffer1, 200);
  	if(z<0){
    	printf("Error reading file"); exit(0);
  	}
    readCount = readCount + z;
  } while (z > 0);

  cursor = readCount - 200;

  //Reposition cursor for proper read of x.y
  a = lseek(y, cursor, 0);
  if(a<0){
    printf("Error repositioning file cursor"); exit(0);
  }
  
  //Read 200 bytes from x.y
  b = read(y, &buffer1, 200);
  if(b<0){
  	printf("Error reading file"); exit(0);
  }

  //Write 200 bytes to XYZ.txt
  c = write(x, &buffer1, 200);
  if(c<0){
    printf("Error writing to file"); exit(0);
  }

  //Close all open files
  d = close(x);
  if(d<0){
    printf("Error closing file"); exit(0);
  }
  e = close(y);
  if(e<0){
    printf("Error closing file"); exit(0);
  }

  printf("\nPid %d Code BB: Done and terminating" , getpid());

  exit(0);
}