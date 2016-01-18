// CC.c


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void main() {
  int x = 1;

  printf("\nPid %d Code CC: Entering an infinite loop.", getpid());

  while(x == 1) {
    usleep(100);
  }
}