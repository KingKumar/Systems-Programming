//Proc 1
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ssem.h"
#include "sshm.h"

int main() {
	int i, internal_reg; 
	int sem0, sem1, sem2, sem3, sem4;
	int act0, act1, act2;
	int s_wait, s_signal, shm_id;
	int *Account;
	int mutex = 1;

	/* here create and initialize all semaphores */ 
	sem0 = sem_create(012345, 0);
	if(sem0 <= 0){
		printf("\nsem0: Semaphore creation failed"); exit(0);
	} else { 
		printf("\nsem0: Semaphore with key 012345 and initial value 0 created"); 
	}
	sem1 = sem_create(111111, 0);
	if(sem1 <= 0){
		printf("\nsem1: Semaphore creation failed."); exit(0);
	} else { 
		printf("\nsem1: Semaphore with key 111111 and initial value 0 created"); 
	}
	sem2 = sem_create(222222, 0);
	if(sem2 <= 0){
		printf("\nsem2: Semaphore creation failed"); exit(0);
	} else { 
		printf("\nsem2: Semaphore with key 222222 and initial value 0 created"); 
	}
	sem3 = sem_create(333333, 0);
	if(sem3 <= 0){
		printf("\nsem3: Semaphore creation failed"); exit(0);
	} else { 
		printf("\nsem3: Semaphore with key 333333 and initial value 0 created"); 
	}
	sem4 = sem_create(444444, mutex);
	if(sem4 <= 0){
		printf("\nsem4: Semaphore creation failed"); exit(0);
	} else { 
		printf("\nsem4: Mutex semaphore with key 444444 and initial value 1 created"); 
	}

	/* here open all semaphores */ 
	sem_open(012345);
    printf("\nsem0: Semaphore sem0 with key 012345 opened"); 
	sem1 = sem_open(111111); 
	printf("\nsem1: Semaphore sem1 with key 111111 opened"); 
	sem2 = sem_open(222222);
	printf("\nsem2: Semaphore sem2 with key 222222 opened"); 
	sem3 = sem_open(333333);
	printf("\nsem3: Semaphore sem3 with key 333333 opened"); 
	sem4 = sem_open(444444);
	printf("\nsem4: Mutex semaphore sem4 with key 444444 opened"); 

	/* here created: shared memory array Account of size 3 */ 
	shm_id = shm_get(55, (void**)&Account, 3*sizeof(int));
	Account[0]=10000; 
	Account[1]=10000; 
	Account[2]=10000; 


	/* synchronize with Proc2, Proc3 and Proc4 (4 process 4 way synch.)*/ 
	sem_signal(sem1); 
	printf("\nsem1: Semaphore signaling concluded"); 
	sem_signal(sem2); 
	printf("\nsem2: Semaphore signaling concluded");
	sem_signal(sem3);
	printf("\nsem3: Semaphore signaling concluded");  
	printf("\nWaiting for Semaphore0 signals to start Proc1");

	

	sem_wait(sem0); 
	sem_wait(sem0); 
	sem_wait(sem0); 
	printf("\nsem0: Semaphore wait for sem0 concluded, processes synched, initializing Proc1");
	/*---------------------------------------------------------------------*/
	 for (i = 0; i < 2000; i++) { 
		sem_wait(sem4);

		internal_reg = Account[0]; 
		internal_reg = internal_reg - 200; 
		Account[0] = internal_reg; 

		/* same thing, except we're adding $200 to account1 now... */ 
		internal_reg = Account[1]; 
		internal_reg = internal_reg + 200; 
		Account[1] = internal_reg; 

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

		if(i == 600 || i == 1200 || i == 1800){
		 	usleep(200000);
		}
	} 

	/* Add a code that prints contents of each account and 
	their sum after 100th, 200th, 300th, .... and 1900th
	iteration*/ 
 } 


/*in the code above include some wait and signal operations on 
semaphores. Do not over-synchronize. */
