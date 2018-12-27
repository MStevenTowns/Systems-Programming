#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>



pthread_t philosopher[50];
pthread_mutex_t chopstick[50];
int p=5;
int meal=5;

void *func(int n)
{
	pthread_mutex_lock(&chopstick[n]);
	pthread_mutex_lock(&chopstick[(n+1)%p]);
	printf ("Philosopher %d is eating\n\n",n);
	usleep(500000);
	pthread_mutex_unlock(&chopstick[n]);
	pthread_mutex_unlock(&chopstick[(n+1)%p]);
	
	printf ("Philosopher %d finished eating\n",n);
	printf ("Philosopher %d is thinking\n",n);
	return(NULL);
}

int main(int argc, char *argv[] )
{
	
	if(argc==1)
	{
		p=5;
		meal=5;
	}
	if(argc==2)
	{
		p=atoi(argv[1]);
		meal=5;
	}
	if(argc==3)
	{
		p=atoi(argv[1]);
		meal=atoi(argv[2]);
	}
	printf ("All %d philosophers are thinking\n",p);
	for(int j=0;j<meal;j++)
	{
		for(int i=0;i<p;i++)
			pthread_mutex_init(&chopstick[i],NULL);

		for(int i=0;i<p;i++)
			pthread_create(&philosopher[i],NULL,(void *)func,(void *)i);

		for(int i=0;i<p;i++)
			pthread_join(philosopher[i],NULL);

		for(int i=0;i<p;i++)
			pthread_mutex_destroy(&chopstick[i]);
	}
	return 0;
}
