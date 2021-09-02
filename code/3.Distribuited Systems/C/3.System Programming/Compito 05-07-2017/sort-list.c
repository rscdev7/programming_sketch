#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <unistd.h>
#define MAX_WORD_LEN 4000
#define SEM_DAD 0
#define SEM_CMP 1
#define SEM_OK 2
#define SEM_K 3

int WAIT(int sem_des, int num_semaforo){
	struct sembuf operazioni[1] = {{num_semaforo,-1,0}};
	return semop(sem_des, operazioni, 1);
}
int SIGNAL(int sem_des, int num_semaforo){
	struct sembuf operazioni[1] = {{num_semaforo,+1,0}};
	return semop(sem_des, operazioni, 1);
}

int find_max(char* fl,int dim) {
	int len=dim-1;
	while (fl[len]!='\n') {
		len--;
	}
	len=len+1;
	return len;
}

void padre (char* ptr,int id_sem) {
	while (1) {
		WAIT (id_sem,SEM_DAD);
		if (strcmp(ptr,"exit")==0) break;
		printf ("%s \n",ptr);
		SIGNAL (id_sem,SEM_OK);
	}

}

void comparer (char* ptr,int id_sem) {
	while (1) {
		WAIT (id_sem,SEM_CMP);
		if (strcmp(ptr,"exit")==0) break;
		char* str1=strtok (ptr,"$");
		char* str2=strtok (NULL,"$");
		if (strcasecmp(str1,str2)>=0) {
			strcpy (ptr,"1");
		}else{
			strcpy (ptr,"2");	
		}
		SIGNAL (id_sem,SEM_K);
	}
}



void sorter (char* file,char* ptr,int id_sem) {
	FILE* fp=fopen (file,"r");
	if (fp==NULL) {
		perror ("Errore apertura file \n");
		exit (2);
	}

	int dim=0;
	char buff[4000];
	while(fgets (buff,4000,fp)!=NULL) {
		dim++;	
	}
	fclose(fp);	
	
	char v[dim][2000];

	
	int fd=open(file,O_RDONLY | 0666);
	if (fd==-1) {
		perror ("Errore apertura file \n");
		exit (2);
	}

	struct stat b;
	stat (file,&b);

	char* memory=(char*)mmap(NULL, b.st_size, PROT_READ, MAP_PRIVATE,
fd, 0);

	if (memory==MAP_FAILED) {
		perror ("Errore mappatura memoria \n");
		exit(56);
	}

	int max=find_max(memory,b.st_size);
	int i=0;
	int c=0;
	int w=0;
	while (i<max) {
		c=0;
		while (memory[c]!='\n') {
			c++;
			i++;
		}
		strncpy(v[w],memory,c);
		w++;
		memory=memory+c+1;
		i++;
	}
	int n1=0;  
    char temp[4000];
	int n2=0;
    for(n1=0; n1<dim-1; n1++){
		for(n2=0; n2<dim-n1-1; n2++){
			strcpy(ptr,"");
			strcpy(ptr,v[n2]);
			strcat (ptr,"$");	
			strcat(ptr,v[n2+1]);


			SIGNAL (id_sem,SEM_CMP);
			WAIT(id_sem,SEM_K);

            if(strcmp(ptr,"1")==0){  
                strcpy(temp,v[n2]);
                strcpy(v[n2],v[n2+1]);
                strcpy(v[n2+1],temp);
			}
			
		}
	}

	strcpy (ptr,"exit");
	SIGNAL (id_sem,SEM_CMP);

	i=0;
	while (i<dim) {
		strcpy (ptr,v[i]);
		SIGNAL (id_sem,SEM_DAD);
		WAIT (id_sem,SEM_OK);
		i++;
	}
	strcpy (ptr,"exit");
	SIGNAL (id_sem,SEM_DAD);
}

void gen_son (int argc,char**argv,char* ptr,int id_sem) {
	int pid=.6;
	pid=fork();
	if (pid!=0) {
		pid=fork();
		if (pid!=0) {
			//PADRE
			padre(ptr,id_sem);
		}else{
			//SORTER
			sorter (argv[1],ptr,id_sem);
			exit(5);
		}
	}else{
		//COMPARER
		comparer (ptr,id_sem);
		exit(6);
	}
}

int main (int argc,char** argv) {
	if (argc!=2) {
		printf ("Numero argomenti errato \n");
		exit(5);
	}

	key_t chiave=IPC_PRIVATE;
	int id_mem=shmget(chiave, 108, IPC_CREAT | 0666);

	char* ptr=(char*)shmat(id_mem, NULL, 0);
	int id_sem=semget(chiave, 4, IPC_CREAT | 0666);

	semctl(id_sem, SEM_DAD, SETVAL, 0);
	semctl(id_sem, SEM_CMP, SETVAL, 0);
	semctl(id_sem, SEM_OK, SETVAL, 0);
	semctl(id_sem, SEM_K, SETVAL, 0);

	gen_son (argc,argv,ptr,id_sem);

	shmctl(id_mem, IPC_RMID, NULL);
	semctl(id_sem,0, IPC_RMID, 0);
}
