
/*
    Homework n.6

    Scrivere un programma che crei un processo figlio con cui scambiera' dati
    tramite una coda di messaggi. Tale coda sara' creata dal padre e distrutta,
    a fine lavori, dal figlio.

    Il processo padre dovra' accettare comandi inseriti da tastiera (per semplicita'
    senza parametri) e questi dovranno essere inviati al figlio che li eseguira'
    di volta in volta creando dei processi nipoti: uno per ogni comando.

    Il tutto si dovra' arrestare correttamente all'inserimento del comando
    'exit' sul padre.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <math.h>
struct M{
	long id;
	char mesg[1024];
};

void invia (int des) {
	struct M messaggio;
	do{
		printf ("Inserisci un messaggio \n");
		fgets (messaggio.mesg,1024,stdin);
		messaggio.id=1;
		if(msgsnd(des,&messaggio,strlen(messaggio.mesg)+1,0)==-1){
			perror ("Errore Invio: ");
			msgctl(des, IPC_RMID, NULL);
			exit (2);
		}
	}while(strcmp(messaggio.mesg,"exit\n")!=0);
}

void ricevi (int des) {
	struct M w;
	int rec=-1;
	do{
		strcpy (w.mesg,"");
		rec=msgrcv (des,&w,sizeof(w)-sizeof(long),0,0);
		if (rec==-1) {
			perror ("Errore ricezione ");
			msgctl(des, IPC_RMID, NULL);
			exit (3);
		}else{
			if (strlen(w.mesg)>0) printf ("Messaggio Ricevuto: %s \n",w.mesg);
			int pid=fork();
			if (pid==0) {
				char v[1024];
				strcpy(v,"");
				strncat (v,w.mesg,strlen(w.mesg)-1);
				execlp(v,v,NULL);
			}
		}	
	}while(strcmp(w.mesg,"exit\n")!=0);
	msgctl(des, IPC_RMID, NULL);
}
int main () {
	key_t chiave=9000;	
	int des=msgget (chiave, IPC_CREAT | 0660);
	if (des ==-1) {
		perror ("Errore \n");
		exit(1);
	}
	printf ("ID %i \n",des);
	int pid=fork();

	if (pid==0) {
		ricevi(des);
		exit(1);
	}else{
		invia (des);	
		exit(2);
	}
}
