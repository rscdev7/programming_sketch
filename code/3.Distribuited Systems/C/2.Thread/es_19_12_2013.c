#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

int m;
pthread_mutex_t mutex;
pthread_cond_t var;

void* p1 (void* ptr) {
	while (1) {
		pthread_mutex_lock (&mutex);
			if (m>=1 && m<=5) {
				pthread_cond_signal (&var);
				m=(int)((rand()%10)+1);
				printf ("Numero TH1-M: %d \n",m);
			}else if (m>=6 && m<=10){
				pthread_cond_wait (&var,&mutex);	
			}
		pthread_mutex_unlock (&mutex);
	}
	pthread_exit(NULL);
}

void* p2 (void* ptr) {
	while (1) {
		pthread_mutex_lock (&mutex);
			if (m>=6 && m<=10) {
				pthread_cond_signal (&var);
				m=(int)((rand()%10)+1);
				printf ("\t\t\t\tNumero TH2-M: %d \n",m);
			}else if (m>=1 && m<=5){
				pthread_cond_wait (&var,&mutex);	
			}
		pthread_mutex_unlock (&mutex);
	}
	pthread_exit(NULL);
}

int main () {
	m=(int)((rand()%10)+1);
	
	pthread_t th1,th2;
	
	pthread_mutex_init (&mutex,NULL);
	pthread_cond_init (&var,NULL);
	int ris=pthread_create (&th1,NULL,(void*) &p1,NULL);
	if (ris!=0) {
		perror ("Errore creazione thread \n");
	}

	ris=pthread_create (&th2,NULL,(void*) &p2,NULL);
	if (ris!=0) {
		perror ("Errore creazione thread \n");
	}

	pthread_join (th1,NULL);
	pthread_join (th2,NULL);
}
