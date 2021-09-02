/* 
 Nominativo: Rosario Scalia
  Matricola: X81000374
*/	  
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#define MAX_WD 150
#define SEM_RP 0
#define SEM_WP 1

int WAIT(int sem_des, int num_semaforo){
	struct sembuf operazioni[1] = {{num_semaforo,-1,0}};
	return semop(sem_des, operazioni, 1);
}

int SIGNAL(int sem_des, int num_semaforo){
	struct sembuf operazioni[1] = {{num_semaforo,+1,0}};
	return semop(sem_des, operazioni, 1);
}

int check_pal (char* str) {
	int dim=strlen(str);
	int fin=dim-1;
	int i=0;
	for (i=0;i<dim;i++) {
		if (str[i]!=str[fin-i]) return 0;
	}
	return 1;
}

void elabora (int sem,char* memr){ 
	while (strcmp(memr,"fn")!=0) {
		WAIT (sem,SEM_RP);
		if (check_pal(memr)==1) {
			SIGNAL (sem,SEM_WP);
			WAIT (sem,SEM_WP);
		}
		SIGNAL (sem,SEM_RP);
	}
	strcpy (memr,"fn");
	SIGNAL (sem,SEM_WP);
}
void stampa (char* file,int sem,char* memr) { 
	while (strcmp(memr,"fn")!=0) {
		WAIT (sem,SEM_WP);
		if (strcmp(file,"nf")==0) {
			if (strcmp (memr,"fn")!=0) {
				printf ("%s \n",memr);
			}
		}else{
			if (strcmp (memr,"fn")!=0) {
				int fd=open(file,O_CREAT | O_RDWR ,0666);
				if (fd!=-1) {
					close(1);
					dup (fd);
					printf ("%s \n",memr);
				}
			}
		}
		SIGNAL (sem,SEM_WP);
	}
}

void invia (char** argv,int sem,char* memr) { 
	int fd=open(argv[1], O_RDONLY, 0666);
	if (fd==-1) {
		perror ("Errore apertura file: \n");
	}
	struct stat buffer;
	stat(argv[1],&buffer);
	char* fl=(char *) mmap(NULL, buffer.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	int counter=0;
	int index=0;
	while (counter<buffer.st_size-1) {
		strcpy (memr,"");
		index=0;
		while (fl[counter]!='\n') {
			memr[index]=fl[counter];
			counter++;
			index++;
		}
		memr[index]='\0';
		SIGNAL(sem,SEM_RP);
		counter++;
		WAIT (sem,SEM_RP);
	}
	strcpy (memr,"fn");
	SIGNAL(sem,SEM_RP);
}


int main (int argc,char** argv) {

	if (argc<2) {
		printf ("Passati pochi argomenti \n");
	}
	key_t chiave=IPC_PRIVATE;
	int idr=shmget (chiave,MAX_WD,IPC_CREAT | IPC_EXCL | 0666); 
	char* memr=(char*)shmat(idr, NULL, 0);
	int idw=shmget (chiave,MAX_WD,IPC_CREAT | IPC_EXCL | 0666); 
	char* memw=(char*)shmat(idw, NULL, 0);
	int id_sem=semget(chiave, 2, IPC_CREAT | IPC_EXCL | 0666);
	semctl(id_sem, SEM_RP, SETVAL, 0);
	semctl(id_sem, SEM_WP, SETVAL, 0);
	int num=argc;
	int pid=-1;
	pid=fork();
	if (pid!=0) {
		pid=fork();
		if (pid!=0) {
			//PADRE
			elabora (id_sem,memr);
			shmctl(idr, IPC_RMID, NULL);
			shmctl(idw, IPC_RMID, NULL);
			semctl(id_sem, 0, IPC_RMID, 0);
			exit(1);
		}else{
			//W
			if (num==3) {
				stampa (argv[2],id_sem,memr);
			}else{
				char str[200];
				strcpy (str,"nf");
				stampa (str,id_sem,memr);
			}
			exit(3);
		}
	}else{
		//R	
		invia(argv,id_sem,memr);
		exit(2);
	}
}
