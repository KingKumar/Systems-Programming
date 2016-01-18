// ProcZ
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ssem.h"
#include "sshm.h"

int main() {
	int i, k;
	int BUFFER_SIZE = 25;
	int fillCount = 0; // items produced
	int elementCount;
	int emptyCount = BUFFER_SIZE; // remaining space
	int m_sem, mutex = 1;
	int shm_id;
	int sem1, sem2;


	/* Buffer struct elements */
	typedef struct {
	   int integer;
	   char characters[5];
	} element;

	/* Declare temp element for data retrieval*/
	element temp = {0, 's', 't', 'r', 'i', 'n'};


	/* here created: shared memory array buffer of size 25*(struct element) */ 
	element *buffer;
	shm_id = shm_get(255, (void**)&buffer, 25*sizeof(temp));

	/* here create and initialize all semaphores */ 
	fillCount = sem_create(999999, 0);
	if(fillCount <= 0){
		printf("\nfillCount_sem: Semaphore creation failed"); exit(0);
	} else { 
		printf("\nfillCount_sem: Semaphore with key 999999 and initial value 0 created"); 
	}
	emptyCount = sem_create(888888, emptyCount);
	if(emptyCount <= 0){
		printf("\nemptyCount_sem: Semaphore creation failed."); exit(0);
	} else { 
		printf("\nemptyCount_sem: Semaphore with key 888888 and initial value 25 created"); 
	}
	m_sem = sem_create(777777, mutex);
	if(m_sem <= 0){
		printf("\nmutex_sem: Semaphore creation failed."); exit(0);
	} else { 
		printf("\nmutex_sem: Mutex semaphore with key 777777 and initial value 1 created"); 
	}
	sem1 = sem_create(888999, 0);
	if(sem1 <= 0){
		printf("\nsem1: Semaphore creation failed."); exit(0);
	} else { 
		printf("\nsem1: Sync semaphore with key 888999 and initial value 0 created"); 
	}
	sem2 = sem_create(999888, 0);
	if(sem2 <= 0){
		printf("\nsem2: Semaphore creation failed."); exit(0);
	} else { 
		printf("\nsem2: Sync semaphore with key 999888 and initial value 0 created"); 
	}

	/* here open all semaphores */ 
	sem_open(999999);
    printf("\nfillCount_sem: Semaphore fillCount with key 999999 opened"); 
	sem_open(888888); 
	printf("\nemptyCount_sem: Semaphore emptyCount with key 888888 opened");
	sem_open(777777); 
	printf("\nmutex_sem: Mutex semaphore with key 777777 opened");


	/*---------------------------------------------------------------------*/

	 for (i = 0; i < 1000; i++) { 

		sem_wait(fillCount);
		sem_wait(fillCount);

		sem_wait(mutex);

		k = 24;
		while (buffer[k].integer < 0) {
			k--;
			if(k < 0){
				printf("\nError, no produced item. Terminating."); exit(0);
			}
		}

		printf("\nItem number of element: %d", buffer[k].integer);
		printf("\nCharacters of element: %s\n", &buffer[k].characters);

		k = 24;
		while (buffer[k].integer < 0) {
			k--;
			if(k < 0){
				printf("\nError, no produced item. Terminating."); exit(0);
			}
		}
		printf("\nItem number of element: %d", buffer[k].integer);
		printf("\nCharacters of element: %s\n", &buffer[k].characters);

		sem_signal(mutex);

		sem_signal(emptyCount);
		sem_signal(emptyCount);
		if(i % 100 == 0 && i != 0){
			usleep(50000);
		}
	} 

	/* Add a code that prints contents of each account and 
	their sum after 100th, 200th, 300th, .... and 1900th
	iteration*/ 
 } 