#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

int x=0;
pthread_mutex_t mutex;
void* tA (void* ptr) {
	int hit=0;
	while (1) {
		int val=(int)(rand()%200)+1;
		usleep (val*100);
		pthread_mutex_lock (&mutex);
		if (x>500) {
			pthread_mutex_unlock (&mutex);
			printf ("A - Val hit: %d \n",hit);
			pthread_exit (NULL);
		}else{
			x++;
			hit++;
		}
		pthread_mutex_unlock(&mutex);
		
	}
}

void* tB (void* ptr) {
	int hit=0;
	while (1) {
		int val=(int)(rand()%200)+1;
		usleep (val*100);
		pthread_mutex_lock (&mutex);
		if (x>500) {
			pthread_mutex_unlock (&mutex);
			printf ("\t\t\tB - Val hit: %d \n",hit);
			pthread_exit (NULL);
		}else{
			x++;
			hit++;
		}
		pthread_mutex_unlock(&mutex);
		
	}
}

int main () {
	pthread_t th1,th2;
	pthread_mutex_init (&mutex,NULL);
	srand(time(NULL));
	int ris=pthread_create (&th1,NULL,(void*) &tA,NULL);
	if (ris!=0) {
		perror ("Errore creazione thread \n");
		exit (-5);
	}

	ris=pthread_create (&th2,NULL,(void*) &tB,NULL);
	if (ris!=0) {
		perror ("Errore creazione thread \n");
		exit (-5);
	}

	pthread_join (th1,NULL);
	pthread_join (th2,NULL);

}
