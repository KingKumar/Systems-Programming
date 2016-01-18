/*compilation command: gcc -lpthread -lrt ThreadA.c -o Proc1*/
#define _REENTRANT
#include <pthread.h>
#include <stdio.h>
#include <time.h> 
#define NUM_THREADS 6

int A[1200][1000];
int B[1000][500];
int C[1200][500];
int C1[1200][500];

int r1,c1,r2,c2, numThreads, numErrors;

void *threadA (void *);   /* thread routines */
void *threadB (void *);
void *threadC (void *);
void *threadD (void *);
void *threadE (void *);
void *threadF (void *);
pthread_t tid[NUM_THREADS]; /* array of thread IDs */

clock_t begin, end;
double timeMain, timeThreads, timeCompare;

int main()
{  
    int iCount,jCount,kCount;
    numErrors = 0;
    
    printf("\nNumber of Rows For Matrix A: 1200");
    r1 = 1200;
    
    printf("\nNumber of Columns For Matrix A: 1000");
    c1 = 1000;
    
    for(iCount=0; iCount<r1; iCount++)
    {
        for(jCount=0;jCount<c1;jCount++)
        {
            A[iCount][jCount] = r1 + c1;
        }
    }
    
    printf("\n");
    
    printf("\nNumber of Rows For Matrix B: 1000");
    r2 = 1000;
    
    printf("\nNumber of Columns For Matrix B: 500");
    c2 = 500;
    
    for(iCount=0;iCount<r2;iCount++)
    {
        for(jCount=0;jCount<c2;jCount++)
        {
            B[iCount][jCount] = c1;
        }
    }

    printf("\n\nHow many threads do you want to use for the multiplication process? ->  ");
    scanf("%d",&numThreads);
    
    if(c1!=r2)
    {
        printf("Multipication of Matrix not Possible !!!");
    }
    else
    {
        for(iCount=0;iCount<r1;iCount=iCount++)
        {
            for(jCount=0;jCount<c2;jCount=jCount++)
            {
                C1[iCount][jCount]=0;
            }
        }

        for(iCount=0;iCount<r1;iCount=iCount++)
        {
            for(jCount=0;jCount<c2;jCount=jCount++)
            {
                C[iCount][jCount]=0;
            }
        }

        begin = clock();

        for(iCount=0;iCount<r1;iCount=iCount++)
        {
            for(jCount=0;jCount<c2;jCount++)
            {
                for(kCount=0;kCount<c1;kCount++)
                {
                    C1[iCount][jCount]+=A[iCount][kCount] * B[kCount][jCount];
                }
            }
        }
        
        end = clock();

        timeMain = (double)(end - begin); 

        begin = clock();

        switch(numThreads)
        {
            case 0:
                break;
            case 1:
                pthread_create(&tid[0],NULL,threadA,NULL);
                break;
            case 2:
                pthread_create(&tid[0],NULL,threadA,NULL);
                pthread_create(&tid[1],NULL,threadB,NULL);
                break;
            case 3:
                pthread_create(&tid[0],NULL,threadA,NULL);
                pthread_create(&tid[1],NULL,threadB,NULL);
                pthread_create(&tid[2],NULL,threadC,NULL);
                break;
            case 4:
                pthread_create(&tid[0],NULL,threadA,NULL);
                pthread_create(&tid[1],NULL,threadB,NULL);
                pthread_create(&tid[2],NULL,threadC,NULL);
                pthread_create(&tid[3],NULL,threadD,NULL);
                break;
            case 5:
                pthread_create(&tid[0],NULL,threadA,NULL);
                pthread_create(&tid[1],NULL,threadB,NULL);
                pthread_create(&tid[2],NULL,threadC,NULL);
                pthread_create(&tid[3],NULL,threadD,NULL);
                pthread_create(&tid[4],NULL,threadE,NULL);
                break;
            case 6:
                pthread_create(&tid[0],NULL,threadA,NULL);
                pthread_create(&tid[1],NULL,threadB,NULL);
                pthread_create(&tid[2],NULL,threadC,NULL);
                pthread_create(&tid[3],NULL,threadD,NULL);
                pthread_create(&tid[4],NULL,threadE,NULL);
                pthread_create(&tid[5],NULL,threadF,NULL);
                break;
            default:
                printf("Invalid number of threads.");
                break;
        }
        
    int i;
        for (i = 0;i < numThreads; i++) pthread_join(tid[i],NULL) == 0;

        end = clock();

        timeThreads = (double)(end - begin); 
    }
          
    printf("\n Comparing C to C1 for errors ...\n");
    
    begin = clock();
    for(iCount=0;iCount<r1;iCount++)
    {
        for(jCount=0;jCount<c2;jCount++)
        {
      if(C[iCount][jCount] != C1[iCount][jCount]) {numErrors++;};
        }
    }    
    end = clock();

    timeCompare = (double)(end - begin);

    printf("\n Time to multiply with main: %d", &timeMain);
    printf("\n Time to multiply with %d threads: %d", &numThreads, &timeThreads);
    printf("\n Time to compare 2 resultant matrices: %d", &timeCompare);
    printf("\n Number of errors found in comparison: %d", &numErrors);

    return 0;
}

void *threadA(void *arg)
{
    int iCount,jCount,kCount;
    for(iCount=0;iCount<r1;iCount=iCount+numThreads)
        {
            for(jCount=0;jCount<c2;jCount++)
            {
                for(kCount=0;kCount<c1;kCount++)
                {                    
                    C[iCount][jCount]+=A[iCount][kCount] * B[kCount][jCount];
                }
            }
        }
        
    printf("\nthread A finished ...");
    pthread_exit(NULL);
}

void *threadB(void *arg)
{
    int iCount,jCount,kCount;
    for(iCount=1;iCount<r1;iCount=iCount+numThreads)
        {
            for(jCount=0;jCount<c2;jCount++)
            {
                for(kCount=0;kCount<c1;kCount++)
                {                    
                    C[iCount][jCount]+=A[iCount][kCount] * B[kCount][jCount];
                }
            }
        }
        
    printf("\nthread B finished ...");
    pthread_exit(NULL);
}

void *threadC(void *arg)
{
    int iCount,jCount,kCount;
    for(iCount=2;iCount<r1;iCount=iCount+numThreads)
        {
            for(jCount=0;jCount<c2;jCount++)
            {
                for(kCount=0;kCount<c1;kCount++)
                {                    
                   C[iCount][jCount]+=A[iCount][kCount] * B[kCount][jCount];
                }
            }
        }
        
    printf("\nthread C finished ...");
    pthread_exit(NULL);
}

void *threadD(void *arg)
{
    int iCount,jCount,kCount;
    for(iCount=3;iCount<r1;iCount=iCount+numThreads)
        {
            for(jCount=0;jCount<c2;jCount++)
            {
                for(kCount=0;kCount<c1;kCount++)
                {                    
                    C[iCount][jCount]+=A[iCount][kCount] * B[kCount][jCount];
                }
            }
        }
        
    printf("\nthread D finished ...");
    pthread_exit(NULL);
}

void *threadE(void *arg)
{
    int iCount,jCount,kCount;
    for(iCount=4;iCount<r1;iCount=iCount+numThreads)
        {
            for(jCount=0;jCount<c2;jCount++)
            {
                for(kCount=0;kCount<c1;kCount++)
                {                    
                    C[iCount][jCount]+=A[iCount][kCount] * B[kCount][jCount];
                }
            }
        }
        
    printf("\nthread E finished ...");
    pthread_exit(NULL);
}

void *threadF(void *arg)
{
    int iCount,jCount,kCount;
    for(iCount=5;iCount<r1;iCount=iCount+numThreads)
        {
            for(jCount=0;jCount<c2;jCount++)
            {
                for(kCount=0;kCount<c1;kCount++)
                {                    
                    C[iCount][jCount]+=A[iCount][kCount] * B[kCount][jCount];
                }
            }
        }
        
    printf("\nthread F finished ...");
    pthread_exit(NULL);
}
