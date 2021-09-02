#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

int x=0;
pthread_mutex_t mutex;
void* a (void* ptr) {
	int cnt=0;
	while (1) {
		pthread_mutex_lock (&mutex);
		if (x>300) {
			pthread_mutex_unlock (&mutex);
			printf ("Val cnt A: %d \n",cnt);
			pthread_exit (NULL);
		}
		x++;
		cnt++;
		pthread_mutex_unlock (&mutex);
		int val=(int)(rand()%100)+1;
		usleep (val*1000);	
	}
}

void* b (void* ptr) {

	int cnt=0;
	while (1) {
		pthread_mutex_lock (&mutex);
		if (x>300) {
			pthread_mutex_unlock (&mutex);
			printf ("Val cnt B: %d \n",cnt);
			pthread_exit (NULL);
		}
		x++;
		cnt++;
		pthread_mutex_unlock (&mutex);
		int val=(int)(rand()%100)+1;
		usleep (val*1000);	
	}

}

int main () {
	pthread_t th1,th2;
	pthread_mutex_init (&mutex,NULL);
	int ris=pthread_create (&th1,NULL,(void*) &a,NULL);
	if (ris!=0) {
		perror ("Errore creazione thread \n");
		exit (-5);
	}

	ris=pthread_create (&th2,NULL,(void*) &b,NULL);
	if (ris!=0) {
		perror ("Errore creazione thread \n");
		exit (-5);
	}

	pthread_join (th1,NULL);
	pthread_join (th2,NULL);

}
