#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <math.h>

int posizione=0;
int vittorie_tp0=0;
int vittorie_tp1=0;
pthread_mutex_t mutex;
pthread_cond_t wake;

void* tp0 (void* ptr) {
	int who_are_you=*((int*)ptr);
	while (1) {
		int recupero=(int)(rand()%3);	
		int forza=(int)(rand()%5);
		sleep(recupero);
		
		if (who_are_you==0) {

			pthread_mutex_lock (&mutex);
			if (vittorie_tp0>=2 || vittorie_tp1 >=2) {
				pthread_mutex_unlock (&mutex);
				pthread_exit (NULL);
			}

			printf ("Recupero: %d - Forza %d Vittorie: %d Posizione: %d \n",recupero,forza,vittorie_tp0,posizione);

			if (posizione>=10) {
				vittorie_tp1++;
				posizione=0;
				pthread_cond_signal (&wake);
			}else{
				posizione-=forza;
				if (posizione<=-10) {
					pthread_cond_wait (&wake,&mutex);
				}
			}
			pthread_mutex_unlock (&mutex);

		}else{
			pthread_mutex_lock (&mutex);
			if (vittorie_tp0>=2 || vittorie_tp1 >=2) {
				pthread_mutex_unlock (&mutex);
				pthread_exit (NULL);
			}

			printf ("\t\t\t\t\tRecupero: %d - Forza %d Vittorie: %d Posizione: %d \n",recupero,forza,vittorie_tp1,posizione);

			if (posizione<=-10) {
				vittorie_tp0++;
				posizione=0;
				pthread_cond_signal (&wake);
			}else{
				posizione+=forza;
				if (posizione>=10) {
					pthread_cond_wait (&wake,&mutex);
				}
			}

			pthread_mutex_unlock (&mutex);
		}
		
	}
	pthread_exit(NULL);
}


int main () {
	pthread_t th0,th1;
	srand (time(NULL));
	int ris=0;
	int n1=0;
	int n2=1;

	pthread_mutex_init (&mutex,NULL);
	pthread_cond_init (&wake,NULL);

	ris=pthread_create (&th0,NULL,(void*) &tp0,(void*)&n1);
	if (ris!=0) {
		perror ("Errore creazione thread \n");
		exit (-5);	
	}

	ris=pthread_create (&th1,NULL,(void*) &tp0,(void*)&n2);
	if (ris!=0) {
		perror ("Errore creazione thread \n");
		exit (-5);	
	}

	pthread_join (th0,NULL);
	pthread_join (th1,NULL);
	
	if (vittorie_tp0>vittorie_tp1) {
		ris=0;
	}else{
		ris=1;
	}
	printf ("Il vincitore e' tp%d \n",ris);

}
