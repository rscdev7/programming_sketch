#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#define LEN 4000
#define SEM_ST 0
#define SEM_SC 1
#define SEM_SCAN 2
#define SEM_ST2 3
#define MAX_PATH_LEN 100

int WAIT(int sem_des, int num_semaforo){
	struct sembuf operazioni[1] = {{num_semaforo,-1,0}};
	return semop(sem_des, operazioni, 1);
}
int SIGNAL(int sem_des, int num_semaforo){
	struct sembuf operazioni[1] = {{num_semaforo,+1,0}};
	return semop(sem_des, operazioni, 1);
}

void stater (char* ptr,int id_sem,int max) {
	int cont_e=0;
	while (1) {
		WAIT (id_sem,SEM_SC);
		char* path=strtok (ptr,"$");
		char* file=strtok (NULL,"$");
		//printf ("Stater-Ricevo: Path %s e File %s \n",path,file);

		if (strcmp (ptr,"exit")!=0) {
			struct stat buf;
			char y[4000];
			strcpy(y,path);
			strcat(y,file);
			int fd=open (y, O_RDONLY |0666);
			if (fd==-1) {
				perror ("Errore apertura file \n");
				exit(6);
			}
			fstat (fd,&buf);
			int dim=buf.st_blocks;
			char bt[400];
			sprintf(bt, "%d", dim);
			strcpy (ptr,path);
			strcat (ptr,"$");
			strcat (ptr,bt);
			//printf ("Stater-Invio: %s \n",ptr);
			SIGNAL (id_sem,SEM_ST);
			WAIT(id_sem,SEM_ST2);
			SIGNAL (id_sem,SEM_SC);
		}else{
			cont_e++;
			if (cont_e==max) {
				SIGNAL (id_sem,SEM_ST);
				WAIT(id_sem,SEM_ST2);
				SIGNAL (id_sem,SEM_SC);	
				exit(5);
			}else{
				SIGNAL (id_sem,SEM_SC);	
			}
		}
	}
}

void scanner (char* path,char* ptr,int id_sem,char** argv,int i) {
	struct stat buffer;
	stat(path, &buffer);

	if (S_ISDIR(buffer.st_mode)) {
		DIR* rif=opendir (path);

		if (rif!=NULL) {
			chdir(path);
			struct dirent* a;

			a=readdir(rif);
			while (a!=NULL) {
				stat(a->d_name, &buffer);
				if (strcmp(a->d_name,".")!=0 && strcmp(a->d_name,"..")!=0 && !S_ISDIR(buffer.st_mode)) {
					WAIT (id_sem,SEM_SCAN);
					strcpy (ptr,path);
					strcat (ptr,"$"); 
					strcat (ptr,a->d_name);
					//printf ("Scanner-Invio: %s \n",ptr);
					SIGNAL (id_sem,SEM_SC);
					WAIT(id_sem,SEM_SC);
					SIGNAL (id_sem,SEM_SCAN);
					
				}

				if (S_ISDIR(buffer.st_mode) && strcmp(a->d_name,".")!=0 && strcmp(a->d_name,"..")!=0) {
					char tr[3000];
					strcpy(tr,"");
					strcat (tr,path);
					strcat(tr,a->d_name);
					strcat (tr,"/");
					scanner (tr,ptr,id_sem,NULL,i);
				}

				a=readdir(rif);
			}
		}	
	}
	if (argv!=NULL) {
		WAIT (id_sem,SEM_SCAN);
		strcpy (ptr,"exit");			
		SIGNAL (id_sem,SEM_SC);
		WAIT(id_sem,SEM_SC);
		SIGNAL (id_sem,SEM_SCAN);
	}
}

void padre (int argc,char* ptr,int id_sem,char** argv) {
	int tot=argc-1;
	int somme[tot];
	int i=0;
	for (i=0;i<tot;i++) {
		somme[i]=0;
	}

	while (1) {
		WAIT (id_sem,SEM_ST);
		if (strcmp(ptr,"exit")==0) break;
		char* path=strtok(ptr,"$");
		char* dim=strtok (NULL,"$");
		//printf ("Padre - Path %s Dim %s \n",path,dim);
		int i=1;
		int al=atoi(dim);
		for (i=1;i<argc;i++) {
			if (strstr (path,argv[i])!=NULL) {
				somme[i-1]=somme[i-1]+al;
			}
		}
		SIGNAL (id_sem,SEM_ST2);  
	}

	for (i=0;i<tot;i++) {
		printf ("Path %s Dimensione %d \n",argv[i+1],somme[i]);
	}	
}

void gen_son (int argc,char** argv,char* ptr,int id_sem){
	int n_son=argc-1;
	int pid=-5;
	pid=fork();
	if (pid!=0) {
		int i=0;
		for (i=1;i<argc;i++) {
			pid=fork();
			if (pid==0) {
				//SCANNER
				scanner(argv[i],ptr,id_sem,argv,i);
				exit(1);
			}
		}
		padre (argc,ptr,id_sem,argv); 
	}else{
		//STATER
		stater (ptr,id_sem,argc-1);
		exit(9);
	}
}

int main (int argc,char** argv) {
	if (argc<2) {
		printf ("Passati pochi argomenti \n");
		exit(1);
	}

	int i=0;
	for (i=1;i<argc;i++) {
		if (strlen(argv[i])>MAX_PATH_LEN) {
			printf ("Errore inserito un path troppo lungo \n");
			exit(1);
		}
	}

	key_t chiave=IPC_PRIVATE;
	int id_mem=shmget(chiave, LEN, IPC_CREAT | 0666);
	char* ptr=(char*)shmat(id_mem, NULL, 0);

	int id_sem=semget(chiave, 3, IPC_CREAT | 0666);
	semctl(id_sem, SEM_ST, SETVAL, 0);
	semctl(id_sem, SEM_SC, SETVAL, 0);
	semctl(id_sem, SEM_SCAN, SETVAL, 1);
	semctl(id_sem, SEM_ST2, SETVAL, 0);

	gen_son (argc,argv,ptr,id_sem);

	shmctl(id_mem,IPC_RMID,NULL);
	semctl(id_sem, 0, IPC_RMID, 0);
}
