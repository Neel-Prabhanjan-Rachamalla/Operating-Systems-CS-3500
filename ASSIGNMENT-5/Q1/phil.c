#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <semaphore.h>

#define THINKING 0
#define HUNGRY 1
#define EATING 2

int N;
int tim=0;
int state[1000];
int count[1000]={0};
int p[1000];
int flag=0;

sem_t mutex;
sem_t S[1000];

void test(int index)
{
	if (state[index]==HUNGRY && state[(index+N-1)%N]!=EATING && state[(index+1)%N]!=EATING)
    {
		state[index]=EATING;
        count[index]++;

        if(flag==0 && count[index]==1)
        {
            sleep(0.01);
            flag=1;
        }

		printf("<%d> Philosopher %d in EATING state - %d\n",tim,index,count[index]);

        tim+=100;

        sleep(0.1);

		sem_post(&S[index]);
	}
}

void putdownfork(int index)
{
    struct timeval start;
    gettimeofday(&start, NULL);

    srand((unsigned) start.tv_usec);

	sem_wait(&mutex);

	state[index]=THINKING;

	printf("<%d> Philosopher %d in THINKING state\n",tim,index);

    double t=rand()%50+50;
    tim+=(int)t;

    printf("");
    sleep(t*0.001);

	test((index+N-1)%N);
	test((index+1)%N);

	sem_post(&mutex);
}

void pickupfork(int index)
{
	sem_wait(&mutex);

	state[index]=HUNGRY;

	test(index);

	sem_post(&mutex);

	sem_wait(&S[index]);
}

void* philosopher(void* num)
{
    int* i=num;

	while(count[*i]<5)
    {
		pickupfork(*i);

		putdownfork(*i);
	}
}

int main(int argc, char *argv[])
{
    char* b=argv[1];
    N=atoi(b);

    for(int i=0 ; i<1000 ; i++)
    {
        p[i]=i;
    }

    time_t a;
    srand((unsigned) time(&a));

	int i;
	pthread_t thread_id[N];

	sem_init(&mutex, 0, 1);

	for (i=0 ; i<N ; i++)
    {
        sem_init(&S[i], 0, 0);
    }

	for (i=0 ; i<N ; i++)
    {
		pthread_create(&thread_id[i],NULL,philosopher,&p[i]);

		printf("<%d> Philosopher %d in THINKING state\n",tim,i);

        if(i==N-1)
        {
            int t=rand()%50+50;
            tim+=t;
        }
	}

	for (i=0 ; i<N ; i++)
    {
        pthread_join(thread_id[i],NULL);
    }

    return 0;
}
