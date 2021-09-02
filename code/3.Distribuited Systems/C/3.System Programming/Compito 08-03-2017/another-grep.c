#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

struct msg{
	long id;
	char mes[4000];
};

void reader (char* file,int* pipefd) {
	int fd=open (file, O_RDONLY | 0666);
	if (fd==-1) {
		perror ("Errore apertura file \n");
		exit (6);
	}	

	struct stat b;
	stat (file,&b);

	char buffer[b.st_size+5];

	int ris=read(fd,buffer,b.st_size+1);
	if (ris==-1) {
		perror ("Errore lettura file \n");
		exit (6);
	}

	buffer[b.st_size-1]='\0';

	ris=write (pipefd[1],buffer,b.st_size);
	if (ris==-1) {
		perror ("Errore scrittura file file \n");
		exit (6);
	}
}

void writer (int id_coda) {
	while (1) {
		struct msg a;
		strcpy (a.mes,"");
		int ris=msgrcv(id_coda, &a, sizeof (a)-sizeof(long),0,0);
		if (ris==-1) {
			perror ("Errore lettura coda \n");
			exit (3);
		}
		if (strcmp (a.mes,"exit")==0) break;
		printf ("Messaggio %s \n",a.mes);
	}
	msgctl(id_coda, IPC_RMID, NULL);	
}

void padre (int id_coda,int*pipefd,char* word,char* file) {
	struct stat b;
	stat (file,&b);

	char buffer[4000];

	int ris=read(pipefd[0],buffer,4000);
	if (ris==-1) {
		perror ("Errore lettura pipe \n");
		exit (6);
	}

	buffer[b.st_size-1]='\0';
	
	char* ptr=strtok (buffer,"\n");
	int ok=0;
	while (ok==0) {
		struct msg a;
		strcpy (a.mes,"");
		a.id=5;
		strcpy (a.mes,ptr);
		if (strstr (ptr,word)!= NULL) {
			msgsnd(id_coda, &a, strlen (a.mes)+1, 0);
		}
		ptr=strtok (NULL,"\n");
		if (ptr==NULL) {
			strcpy (a.mes,"");
			a.id=5;
			strcpy (a.mes,"exit");
			msgsnd(id_coda, &a, strlen (a.mes)+1, 0);
			ok=1;
		}
	}
	
}

void gen_son (char** argv,int id_coda) {
	int pid=fork();
	if (pid!=0) {

		int pipefd[2];
		if (pipe(pipefd)==-1) {
			perror ("Errore apertura pipe \n");
			exit (4);
		}

		pid=fork();
		if (pid!=0) {	
			//PADRE
			close (pipefd[1]);
			padre(id_coda,pipefd,argv[1],argv[2]);
			close (pipefd[0]);
		}else{
			//R
			close (pipefd[0]);
			reader(argv[2],pipefd);
			close (pipefd[1]);
			exit(2);
		}
	}else{
		//W
		writer (id_coda);
		exit(2);	
	}	
}

int main (int argc,char** argv) {
	if (argc<3) {
		printf ("Passati pochi argomenti \n");
		exit(2);
	}

	key_t chiave=IPC_PRIVATE;
	int id_coda=msgget(chiave, IPC_CREAT | 0666);

	gen_son(argv,id_coda);
}
