//Proc 4
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ssem.h"
#include "sshm.h"

int main() {
	int i, sums_count, nack;
	int sem0, sem1, sem2, sem3, sem4;
	int act0, act1, act2;
	int s_wait, s_signal, s_rm, shm_id;
	int *Account;
	shm_id = shm_get(55, (void**)&Account, 3*sizeof(int));

	/* here open all semaphores */ 
	sem0 = sem_open(012345);
      	printf("\nsem0: Semaphore sem0 with key 012345 opened"); 
	sem1 = sem_open(111111); 
	printf("\nsem1: Semaphore sem1 with key 111111 opened"); 
	sem2 = sem_open(222222);
	printf("\nsem2: Semaphore sem2 with key 222222 opened"); 
	sem3 = sem_open(333333);
	printf("\nsem3: Semaphore sem3 with key 333333 opened"); 
	sem4 = sem_open(444444);
	printf("\nsem4: Mutex semaphore sem4 with key 444444 opened"); 
	

	sums_count = 0;
	nack = 0;

	/*synchronize with Proc1, Proc2 and Proc3 (4 process 4 way sync.)*/ 
    s_signal = sem_signal(sem0); 
	printf("\nsem0: Semaphore signaling concluded"); 
	s_signal = sem_signal(sem1);
	printf("\nsem1: Semaphore signaling concluded"); 
	s_signal = sem_signal(sem2); 
	printf("\nsem2: Semaphore signaling concluded"); 
	printf("\nWaiting for Semaphore3 signals to begin Proc4");



	s_wait = sem_wait(sem3);
	s_wait = sem_wait(sem3);
	s_wait = sem_wait(sem3);
	printf("\nsem3: Semaphore wait for sem3 concluded, processes synced, initializing Proc4");
	/*---------------------------------------------------------------------*/

	for (i = 0; i < 5000; i++) { 
		sem_wait(sem4);

		 act0 = Account[0];
		 act1 = Account[1];
		 act2 = Account[2];

		 printf("\nLoop: %d", i);
		 printf("\nAccount0: %d", act0);
		 printf("\nAccount1: %d", act1);
		 printf("\nAccount2: %d", act2);
		 printf("\nSum: %d\n", act0 + act1 + act2);

		 sums_count++;

		 if((act0 + act1 + act2) != 30000){
		 	nack++;
		 }

		 sem_signal(sem4);

		 if(i % 1000 == 0 && i != 0){
		 	usleep(50000);
		 }
	}

	printf("\nSum calculated %d times", sums_count);
	printf("\nIncorrect sum calculated %d times", nack);

	s_rm = sem_rm(sem0);
	if(s_rm < 0){
		printf("\nsem0: Semaphore remove failed."); exit(0);
	} else {
		printf("\nsem0: Semaphore removed");
	}
	s_rm = sem_rm(sem1);
	if(s_rm < 0){
		printf("\nsem1: Semaphore remove failed."); exit(0);
	} else {
		printf("\nsem1: Semaphore removed");
	}
	s_rm = sem_rm(sem2);
	if(s_rm < 0){
		printf("\nsem2: Semaphore remove failed."); exit(0);
	} else {
		printf("\nsem2: Semaphore removed");
	}
	s_rm = sem_rm(sem3);
	if(s_rm < 0){
		printf("\nsem3: Semaphore remove failed."); exit(0);
	} else {
		printf("\nsem3: Semaphore removed");
	}
	s_rm = sem_rm(sem4);
	if(s_rm < 0){
		printf("\nsem4: Semaphore remove failed."); exit(0);
	} else {
		printf("\nsem4: Semaphore removed");
	}
	s_rm = shm_rm(shm_id);
	if(s_rm < 0){
		printf("\nShared memory-space 'Account' deletion failed."); exit(0);
	} else {
		printf("\nShared memory-space 'Account' deleted\n");
	}
	

}
