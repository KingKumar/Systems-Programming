/* gcc class.example.c ‐o xx ‐lpthread ‐lrt*/
     #define _REENTRANT    /* basic 2‐lines for pthreads */
     #include <pthread.h>
     #include <semaphore.h>  /* basic line for pthread semaphores */
     #include <stdlib.h>
     #include <stdio.h>
     #define NUM_THREADS 3
     
     void *threadA (void *);   /* thread routines */
     void *threadB (void *);
     void *threadC (void *);
     pthread_t tid[NUM_THREADS];      /* array of thread IDs */
     sem_t emptyA, emptyB;
	 sem_t fullA, fullB;
     int in, outA, outB; /* Shared variable */

	 struct element1 {int x; char y[2];};
	 struct element2 {int x; char y[3];};

	 /* Shared arrays of structs */
	 struct element1 bufferX[25];
	 struct element2 bufferY[45];
     
     int main(int argc, char *argv[])
     {
	    int i;
	    int sizeX =25;
		int sizeY =45;
         	       
	    i = sem_init(&emptyA, 0, sizeX);
		i = sem_init(&emptyB, 0, sizeY);
		i = sem_init(&fullA, 0, 0);
		i = sem_init(&fullB, 0, 0);                         
	                                
	    i = pthread_create(&tid[0], NULL, threadA, NULL);
		if (i<0) { printf("Thread No. %d: Creation of thread with tid0 = %d failed. Terminating.\n", pthread_self(), tid[0]); exit(0);}
	              
	    i = pthread_create(&tid[1], NULL, threadB, NULL); 
		if (i<0) { printf("Thread No. %d: Creation of thread with tid1 = %d failed. Terminating.\n", pthread_self(), tid[1]); exit(0);}
	     
	    i = pthread_create(&tid[2], NULL, threadC, NULL);
		if (i<0) { printf("Thread No. %d: Creation of thread with tid2 = %d failed. Terminating.\n", pthread_self(), tid[2]); exit(0);}
	    
		printf("\nmain() Thread No. %d: created three threads tid0 = %d, tid1= %d, tid2= %d\n", 
	            pthread_self(), tid[0], tid[1], tid[2]);
	    
	     
	    for (i = 0;i < NUM_THREADS; i++) pthread_join(tid[i],NULL) == 0;
	         
	    printf("\nmain() Thread No.%d: All threads done.", pthread_self());
	    pthread_exit(NULL);
       
     } /* end main */
 
     void * threadA(void *arg)
     {   
		in = 0;
		int count = 1;
		struct element1 bufItem;
		while (count < 1000) 
		{
			bufItem.x = in + 1;
			bufItem.y = "xx";
			sem_wait(&emptyA);
			bufferX[in] = bufItem;
			in = (in + 1) % 25;
			sem_post(&fullA);
		}
		pthread_exit(NULL);
     }

	void * threadB(void *arg)
     {     
        in = 0;
		int count = 1;
		struct element2 bufItem;
		while (count < 1000) 
		{
			bufItem.x = in + 1;
			bufItem.y = "YYY";
			sem_wait(&emptyB);
			bufferX[in] = bufItem;
			in = (in + 1) % 45;
			sem_post(&fullB);
		}
		pthread_exit(NULL);
     }
    
	void * threadC(void *arg)
     {
        outA = 0;
		outB = 0;
		int count = 1;
		struct element1 bufItemX;
		struct element2 bufItemY;
		while (count < 1000) 
		{
			sem_wait(fullA);
			bufItemX = bufferX[outA];
			sem_post(emptyA);
			printf("%d%s ", bufItemX.x, bufItemX.y);

			sem_wait(fullB);
			bufItemY = bufferY[outB];
			sem_post(emptyB);
			printf("%s%d ", bufItemY.y, bufItemY.x);

			outA = (outA + 1) % 25;
			outB = (outB + 1) % 45;
		}
		pthread_exit(NULL);
     }