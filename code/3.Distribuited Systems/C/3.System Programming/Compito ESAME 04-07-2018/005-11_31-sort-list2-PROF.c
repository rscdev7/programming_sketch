/*
	Nominativo: Rosario Scalia
	Matricola: X81000374

*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#define MAX_WORD_LEN 100
struct msg{
	long id;
	char mes[4000];
};

void comparer (int id_coda) {
	struct msg a;
	struct msg b;
	while (1) {

		int r=msgrcv(id_coda, &a, sizeof (a)-sizeof (long), 10,0);
		if (r==-1) {
			perror ("Errore lettura messaggio \n");
			exit(11);
		}

		if (strcmp (a.mes,"exit")==0) {
			break;
		}

		int y=msgrcv(id_coda, &b, sizeof (b)-sizeof (long), 10,0);
		if (y==-1) {
			perror ("Errore lettura messaggio \n");
			exit(12);
		}

		if (strcmp (b.mes,"exit")==0) {
			break;
		}

		if (strcasecmp(a.mes, b.mes)>0) {
			a.id=5;
			strcpy (a.mes,"1");
			msgsnd(id_coda, &a, strlen (a.mes)+1, 0);
		}else{
			a.id=5;
			strcpy (a.mes,"0");
			msgsnd(id_coda, &a, strlen (a.mes)+1, 0);
		}
	}
	msgctl(id_coda, IPC_RMID, NULL);
}

void padre (int* pipefd) {
	char buffer[100000];
	strcpy (buffer,"");
	int ris=read(pipefd[0],buffer,4000); //PROF: con file grossi non funziona
	if (ris==-1) {
		perror ("Errore lettura da pipe \n");
		exit (6);
	}
	printf ("%s",buffer);
}

int find_max (char* mem,int limit) {
	int dim=limit-1;
	while (dim>=0) {
		if (mem[dim]!='\n') break;
		dim--;
	}
	dim=dim+1;
	return dim;
}

void sorter (int id_coda,int*pipefd,char* file) {
	FILE* fp=fopen (file,"r");
	char str[4000]; //PROF: dissemire il codice con numeri ricorrenti è una pessima abitudine: usare #define per definire costanti tramite il precompilatore
	int c=0; //CONTERRA' IL NUMERO DI RIGHE DEL FILE
	struct stat d;
	stat (file,&d);

	while (fgets (str,4000,fp)!= NULL) {
		c++;
	}

	fclose (fp);

	char v[c][MAX_WORD_LEN]; //PROF: così alloca la memoria nello stack; con grossi file grossi può dare problemi

	int fd=open (file, O_RDONLY | 0666);
	if (fd==-1) {
		perror ("Errore apertura file \n");
		exit (5);
	}

	char* memory=(char*)mmap(NULL, d.st_size, PROT_READ, MAP_PRIVATE,
fd, 0); //PROF: perché usare mappatura di memoria? non era richiesto

	if (memory==MAP_FAILED)  {
		perror ("Errore mappatura memoria \n");
		exit (9);
	}

	int max=find_max(memory,d.st_size);
	int w=0;
	int i=0;
	int k=0;

	while (i<max) {
		k=0;
		while (memory[k]!='\n') {
			k++,
			i++;
		}
		strncpy (v[w],memory,k);
		v[w][k]='\0';
		w++;
		memory=memory+k+1;
		i++;
	}

	int n1=0;
	int n2=0;
	struct msg a;
	struct msg b;
	struct msg risp;
	a.id=10;
	b.id=10;

	for (n1=0;n1<c;n1++) {
		for (n2=0;n2<c-n1-1;n2++) {
			strcpy (a.mes,v[n2]);
			strcpy (b.mes,v[n2+1]);

			msgsnd(id_coda, &a, strlen (a.mes)+1, 0);
			msgsnd(id_coda, &b, strlen (b.mes)+1, 0); //PROF: si doveva usare un unico messaggio

			msgrcv(id_coda, &risp, sizeof (risp)-sizeof (long), 5,0);
			if (strcmp (risp.mes,"1")==0) {
				char temp[4000];
				strcpy (temp,v[n2]);
				strcpy (v[n2],v[n2+1]);
				strcpy (v[n2+1],temp); //PROF: usando memoria allocata e un vettore di puntatori si poteva evitare di fare copie delle stringhe: bastava scambiare i puntatori
			}
		}
	}

	int ris=0;
	char concat[10000]; //PROF: e se il file è più grosso....?!
	strcpy (concat,"");

	for (i=0;i<c;i++) {
		strcat (concat,v[i]);
		strcat (concat,"\n");
	}
    //PROF: bastava scrivere parola per parola dentro la pipe

	ris=write (pipefd[1],concat,strlen(concat)+1);
	if (ris==-1) {
		perror ("Errore scrittura file \n");
		exit (10);
	}

	//CHIUSURA RISORSE ALLOCATE
	munmap(memory, d.st_size); //PROF: ha cambiato nel frattempo il puntatore 'memory', l'unmap non può funzionare

	strcpy (a.mes,"exit");
	msgsnd(id_coda, &a, strlen (a.mes)+1, 0);
    //PROF: i valori di ritorno vanno controllati!
}

void gen_son (char* file) {
	key_t chiave=IPC_PRIVATE;
	int id_coda=msgget(chiave, IPC_CREAT | 0666);

	int pid=-5;
	pid=fork();

	if (pid!=0) {
		int pipefd[2];
		if (pipe(pipefd)==-1) {
			perror ("Errore creazione pipe \n");
			exit(2);
		}

		pid=fork();

		if (pid!=0) {
			//PADRE
			close (pipefd[1]);
			padre (pipefd);
			close (pipefd[0]);
		}else{
			//SORTER
			close (pipefd[0]);
			sorter (id_coda,pipefd,file);
			close (pipefd[1]);
			exit (5);
		}
	}else{
		//COMPARER
		comparer (id_coda);
		exit(2); //PROF: un exit status !=0 significa che il processo è andato in errore
	}

}

int main (int argc,char** argv) {
	if (argc<3) {
		printf ("Errore passati pochi argometi \n");
		exit (1);
	}
	gen_son (argv[2]);
}
