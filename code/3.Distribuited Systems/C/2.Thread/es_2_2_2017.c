#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <errno.h>
int n=0;
pthread_mutex_t mutex;

void * to (void* ptr) {
	//int* a=malloc (sizeof(int));
	//*a=5;
	//pthread_exit(a);
	int c=0;
	while (c<=100) {
		usleep (200000);
		int val=0;
		do{
			val=(int)(rand()%100);
		}while(val%2==0);

		pthread_mutex_lock (&mutex);
		n+=val;
		printf ("Val %d TO n: %d \n",val,n);
		pthread_mutex_unlock (&mutex);

		if (n%2!=0 && c>=10) {
			printf ("Fine TO \n");
			pthread_exit(NULL);
		}
		
		c++;
	}
	pthread_exit(NULL);
}

void* te (void* ptr) {
	int c=0;
	while (c<=100) {
		usleep (200000);
		int val=0;
		do{
			val=(int)(rand()%100);
		}while(val%2!=0);

		pthread_mutex_lock (&mutex);
		n+=val;
		printf ("\t\t\tVal %d TE n: %d \n",val,n);
		pthread_mutex_unlock (&mutex);

		if (n%2==0 && c>=10) {
			printf ("Fine TE \n");
			pthread_exit(NULL);
		}
		c++;
	}
	pthread_exit(NULL);

}

int main () {
	pthread_t th1,th2;
	pthread_mutex_init (&mutex,NULL);
	
	srand (time(NULL));
	int ris=pthread_create (&th1,NULL,(void *) &to,NULL);
	if (ris!=0) {
		perror ("Errore creazione thread \n");
		exit (-5);
	}

	ris=pthread_create (&th2,NULL,(void*) &te,NULL);
	if (ris!=0) {
		perror ("Errore creazione thread \n");
		exit (-5);
	}
	//void* b;
	//pthread_join (th1,&b);
	pthread_join (th1,NULL);
	//int* c=b;
	//printf ("Restituito %d \n",*c);
	pthread_join (th2,NULL);


}
