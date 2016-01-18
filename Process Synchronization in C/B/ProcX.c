// ProcX
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ssem.h"
#include "sshm.h"

int main() {
	int i, k;
	int fillCount; // items produced
	int emptyCount;// remaining space
	int elementCount;
	int sem1, sem2;
	int m_sem, s_rm;
	int shm_id;

	/* Buffer struct elements */
	typedef struct {
	   int integer;
	   char characters[5];
	} element;

	/* Declare temp element for data writing*/
	element temp = {0, 's', 't', 'r', 'i', 'n'};

	/* here created: shared memory array buffer of size 25*(struct element) */ 
	element *buffer;
	shm_id = shm_get(255, (void**)&buffer, 25*sizeof(temp));
	printf("\nsize of temp: %d", sizeof(temp)); 

	/* here open all semaphores */ 
	fillCount = sem_open(999999);
    printf("\nfillCount_sem: Semaphore fillCount with key 999999 opened"); 
	emptyCount = sem_open(888888); 
	printf("\nemptyCount_sem: Semaphore emptyCount with key 888888 opened");
	m_sem = sem_open(777777); 
	printf("\nmutex_sem: Mutex semaphore with key 777777 opened");
	sem1 = sem_open(888999); 
	printf("\nmutex_sem: Sync semaphore with key 888999 opened");
	sem2 = sem_open(999888); 
	printf("\nmutex_sem: Sync semaphore with key 999888 opened");

	sem_signal(sem2);
	sem_wait(sem1);
	/*---------------------------------------------------------------------*/
	 for (i = 0; i < 1000; i++) { 
		
		sem_wait(emptyCount);
		
		sem_wait(m_sem);

		k = i;
		if(k > 24){
			k = k % i;
		}

		buffer[k].integer = i;
		buffer[k].characters[0] = "ProcX";
		printf("\nItem number %d added to buffer", buffer[k].integer);
		printf("\nCharacters of element: %s\n", &buffer[k].characters);

		sem_signal(m_sem);

		sem_signal(fillCount);
		if(i % 100 == 0 && i != 0){
			usleep(50000);
		}

	} 

	s_rm = sem_rm(fillCount);
	if(s_rm < 0){
		printf("\nfillCount: Semaphore remove failed."); exit(0);
	} else {
		printf("\nfillCount_sem: Semaphore removed");
	}
	s_rm = sem_rm(emptyCount);
	if(s_rm < 0){
		printf("\nemptyCount: Semaphore remove failed."); exit(0);
	} else {
		printf("\nemptyCount: Semaphore removed");
	}
	s_rm = sem_rm(m_sem);
	if(s_rm < 0){
		printf("\nm_sem: Semaphore remove failed."); exit(0);
	} else {
		printf("\nm_sem: Semaphore removed");
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
	s_rm = shm_rm(shm_id);
	if(s_rm < 0){
		printf("\nShared memory-space 'Account' deletion failed."); exit(0);
	} else {
		printf("\nShared memory-space 'Account' deleted\n");
	}

	/* Add a code that prints contents of each account and 
	their sum after 100th, 200th, 300th, .... and 1900th
	iteration*/ 
 } 