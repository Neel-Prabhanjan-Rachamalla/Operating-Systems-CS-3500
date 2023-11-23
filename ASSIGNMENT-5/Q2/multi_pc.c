#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

#define IDLE 0
#define BUSY 1

int P,C,PC,CC;
int stack[1000];
int top=-1;
int state[2][1000];
int count[2][1000]={0};
int pc[2][1000];

sem_t mutex;
sem_t S[2][1000];

void test(int index , int pc)
{
    int flag=1;
    int i,j,k;

    for(i=0 ; i<PC ; i++)
    {
        if(state[pc][i]==BUSY)
        {
            flag=0;
            break;
        }
    }
    for(i=0 ; i<CC ; i++)
    {
        if(state[pc][i]==BUSY)
        {
            flag=0;
            break;
        }
    }
    
	if(pc==0 && state[pc][index]==IDLE && flag==1)
    {
        //For Q2.2 the below sleep is done.
        //if(count[pc][index]==0) sleep(5);
		state[pc][index]=BUSY;
        count[pc][index]++;
        
        struct timeval start;
        gettimeofday(&start, NULL);

        srand((unsigned) start.tv_usec);

        int num=rand()%1000;
        stack[++top]=num;
		printf("Producer %d produced %d\n",index+1,num);

        state[0][index]=IDLE;

		sem_post(&S[pc][index]);
	}
    else if(pc==1 && state[pc][index]==IDLE && flag==1 && top>=0)
    {
        state[pc][index]=BUSY;
        count[pc][index]++;

        int num=stack[top--];
        printf("Consumer %d consumed %d\n",index+1,num);

        state[1][index]=IDLE;

        sem_post(&S[pc][index]);
    }
}

void produce(int index)
{
	sem_wait(&mutex);

	test(index,0);

	sem_post(&mutex);

	sem_wait(&S[0][index]);
}

void consume(int index)
{
	sem_wait(&mutex);

	test(index,1);

	sem_post(&mutex);

	sem_wait(&S[1][index]);
}

void* producer(void* num)
{
    int* i=num;

	while(count[0][*i]<PC)
    {
		produce(*i);
	}
}

void* consumer(void* num)
{
    int* i=num;

	while(count[1][*i]<CC)
    {
		consume(*i);
	}
}

int main(int argc, char *argv[])
{
    int n=sizeof(argv);
    printf("");

    for(int i=0 ; i<n ; i++)
    {
        if(strcmp(argv[i],"-p")==0) P=atoi(argv[i+1]);
        else if(strcmp(argv[i],"-pc")==0) PC=atoi(argv[i+1]);
        else if(strcmp(argv[i],"-c")==0) C=atoi(argv[i+1]);
        else if(strcmp(argv[i],"-cc")==0) CC=atoi(argv[i+1]);
    }
        
    for(int i=0 ; i<2 ; i++)
    {
        for(int j=0 ; j<1000 ; j++)
        {
            pc[i][j]=j;
        }
    }

	int i;
	pthread_t pthread_id[P];
    pthread_t cthread_id[C];

	sem_init(&mutex,0,1);

	for (i=0 ; i<P ; i++)
    {
        sem_init(&S[0][i],0,0);
    }
    for (i=0 ; i<C ; i++)
    {
        sem_init(&S[1][i],0,0);
    }

	for (i=0 ; i<P ; i++)
    {
		pthread_create(&pthread_id[i],NULL,producer,&pc[0][i]);
	}
    for (i=0 ; i<C ; i++)
    {
		pthread_create(&cthread_id[i],NULL,consumer,&pc[1][i]);
	}

	for (i=0 ; i<P ; i++)
    {
        pthread_join(pthread_id[i],NULL);
    }
    for (i=0 ; i<C ; i++)
    {
        pthread_join(cthread_id[i],NULL);
    }

    return 0;
}