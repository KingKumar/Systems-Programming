//Proc 3
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ssem.h"
#include "sshm.h"

int main() {
	int i, internal_reg; 
	int sem0, sem1, sem2, sem3, sem4;
	int act0, act1, act2;
	int s_wait, s_signal,shm_id;
	int *Account;
	shm_id = shm_get(55, (void**)&Account, 3*sizeof(int));
 
	/* here open all semaphores */ 
	sem0 = sem_open(012345);
      	printf("\nsem0: Semaphore sem0 with key 012345s opened"); 
	sem1 = sem_open(111111); 
	printf("\nsem1: Semaphore sem1 with key 111111 opened"); 
	sem2 = sem_open(222222);
	printf("\nsem2: Semaphore sem2 with key 222222 opened"); 
	sem3 = sem_open(333333);
	printf("\nsem3: Semaphore sem3 with key 333333 opened"); 
	sem4 = sem_open(444444);
	printf("\nsem4: Mutex semaphore sem4 with key 444444 opened"); 
	
	/*synchronize with Proc1, Proc2 and Proc4 (4 process 4 way sync.)*/ 
	s_signal = sem_signal(sem0); 
	printf("\nsem0: Semaphore signaling concluded"); 
	s_signal = sem_signal(sem1);
	printf("\nsem1: Semaphore signaling concluded"); 
	s_signal = sem_signal(sem3); 
	printf("\nsem3: Semaphore signaling concluded"); 
	printf("\nWaiting for Semaphore2 signals to start Proc3");



	s_wait = sem_wait(sem2);
	s_wait = sem_wait(sem2);
	s_wait = sem_wait(sem2);
	printf("\nsem2: Semaphore wait for sem2 concluded, processes synced, initializing Proc3");
	/*---------------------------------------------------------------------*/

	for (i = 0; i < 2000; i++) { 
		sem_wait(sem4);

		 internal_reg = Account[2]; 
		 internal_reg = internal_reg - 200; 
		 Account[2] = internal_reg; 

		 /* same thing, except we're adding $200 to Account[0] now... */ 

		 /*Proc3 adds into Account[0]*/ 
		 internal_reg = Account[0]; 
		 internal_reg = internal_reg + 200; 
		 Account[0] = internal_reg; 

		if(i % 100 == 0 && i != 0){
			act0 = Account[0];
			act1 = Account[1];
			act2 = Account[2];

			printf("\nLoop: %d", i);
			printf("\nAccount0: %d", act0);
			printf("\nAccount1: %d", act1);
			printf("\nAccount2: %d", act2);
			printf("\nSum: %d\n", act0 + act1 + act2);
		}

		sem_signal(sem4);

		if(i == 500 || i == 1500){
		 	usleep(300000);
		}
	 } 

	 /* Add a code that prints contents of each account 
	 and their sum after 100th, 200th, 300th, .... and 1900th 
	 iteration*/ 
} 
/*in the code above include some wait and signal operations on 
semaphores. Do not over-synchronize. */
