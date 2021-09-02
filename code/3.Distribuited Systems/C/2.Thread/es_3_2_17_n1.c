#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <errno.h>

int n=100;
pthread_mutex_t mutex;

void* t1 () {
	int counter=0;
	while (counter<1000) {
		usleep (100000);
		srand (time(NULL));
		int val=(int)(rand()%10);

		pthread_mutex_lock(&mutex);
		n+=val;
		pthread_mutex_unlock(&mutex); 

		printf ("Val n: %d \n",n);
		if (n>150) {
			printf ("Fine Thread \n");
			pthread_exit(NULL);
		}
		counter++;
	}
	printf ("Fine Thread \n");
	pthread_exit(NULL);
}

void* td () {
	int counter=0;
	while (counter<1000) {
		usleep (300000);
		srand (time(NULL));
		int val=(int)(rand()%10);

		pthread_mutex_lock(&mutex);
		n-=val;
		pthread_mutex_unlock(&mutex); 

		printf ("\t\t\t Val n: %d \n",n);
		if (n<80) {
			printf ("\t\t\t Fine Thread \n");
			pthread_exit(NULL);
		}
		counter++;
	}
	printf ("\t\t\t Fine Thread \n");
	pthread_exit(NULL);
}

int main (int argc,char** argv) {
	pthread_t th1,th2; 
	pthread_mutex_init(&mutex, NULL);

	int ris=pthread_create(&th1, NULL,
	    (void *) &t1, NULL);
	if (ris!=0) {
		perror ("Errore creazione thread \n");
	}

	ris=pthread_create(&th2, NULL,
	    (void *) &td, NULL);
	if (ris!=0) {
		perror ("Errore creazione thread \n");
	}

	pthread_join (th1,NULL);
	pthread_join (th2,NULL);		
}
