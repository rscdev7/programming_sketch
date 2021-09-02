#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <math.h>
#define T1 1
#define T2 2
#define T3 3

int sample=50;
pthread_mutex_t mutex;

void* t (void* ptr) {
	int who_are_you=* ( (int *) ptr);
	while (1) {
		switch (who_are_you) {
			case (1): pthread_mutex_lock (&mutex);
				  int old_sam=sample;
				  sample=(int)(rand ()%81)+10;
				  printf ("Sono il Thread 1, Old_Sample= %d - New Sample= %d \n",old_sam,sample);
				  if (sample==old_sam) {
				  	pthread_mutex_unlock (&mutex);
				        printf ("Fine Th-1 \n");
				        pthread_exit(NULL);
				  } 
				  pthread_mutex_unlock (&mutex);
				  break;
			case (2): 
				  pthread_mutex_lock (&mutex);
				  old_sam=sample;
				  sample=(int)(rand ()%81)+10;
				  printf ("\t\tSono il Thread 2, Old_Sample= %d - New Sample= %d \n",old_sam,sample);
				  if (sample==old_sam) {
				  	pthread_mutex_unlock (&mutex);
				        printf ("\t\tFine Th-2 \n");
				        pthread_exit(NULL);
				  } 
				  pthread_mutex_unlock (&mutex);
				  break;
			case (3): pthread_mutex_lock (&mutex);
				  old_sam=sample;
				  sample=(int)(rand ()%81)+10;
				  printf ("\t\t\tSono il Thread 3, Old_Sample= %d - New Sample= %d \n",old_sam,sample);
				  if (sample==old_sam) {
				  	pthread_mutex_unlock (&mutex);
				        printf ("\t\t\tFine Th-3 \n");
				        pthread_exit(NULL);
				  } 
				  pthread_mutex_unlock (&mutex);
				  break;
		}
	}
	
	pthread_exit (NULL);
}

int main () {
	pthread_t th1,th2,th3;	
	pthread_mutex_init (&mutex,NULL);

	int n1=1;
	int n2=2;	
	int n3=3;
	
	int ris=pthread_create (&th1,NULL,(void*) &t,(void*) &n1);
	if (ris!=0) {
		perror ("Errore creazione thread \n");
		exit (-5);
	}

	

	ris=pthread_create (&th2,NULL,(void*) &t,(void*) &n2);
	if (ris!=0) {
		perror ("Errore creazione thread \n");
		exit (-5);
	}

	ris=pthread_create (&th3,NULL,(void*) &t,(void*) &n3);
	if (ris!=0) {
		perror ("Errore creazione thread \n");
		exit (-5);
	}

	pthread_join (th1,NULL);
	pthread_join (th2,NULL);
	pthread_join (th3,NULL);

	printf ("Valore finale Sample: %d \n",sample);
}
