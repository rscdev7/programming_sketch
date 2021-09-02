#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

struct msg {
	long id;
	char mes [500000];
};

void padre (int* pipefd) {
	char buffer[4000];
	while (1) {
		strcpy (buffer,"");
		int ris=read(pipefd[0],buffer,4000);
		if (ris==-1) {
			printf ("Errore lettura pipe padre \n");
			exit(6);
		}
		if (strcmp(buffer,"exit")==0) break;
		printf ("%s",buffer);		
	}
}

void reader (int id_coda,char* file,int num,int argc) {
	int fd=open (file, O_RDONLY | 0666);
	if (fd==-1) {
		perror ("Errore apertura file \n");
		exit (6);
	}			

	struct stat buf;
	stat (file,&buf);
	struct msg a;
	
	a.id=6;

	int ris=read (fd,a.mes,buf.st_size);
	if (ris==-1) {
		perror ("Errore lettura file \n");
		exit (6);
	}
	msgsnd(id_coda,&a,strlen(a.mes)+1,0);

	strcpy (a.mes,file);
	msgsnd(id_coda,&a,strlen(a.mes)+1,0);

	if (num==argc-1) {
		strcpy (a.mes,"exit");
		msgsnd(id_coda, &a, strlen(a.mes)+1, 0);	
	}
}

void filter (int* pipefd,int id_coda,char** argv,int argc) {
	while (1) {
		struct msg a;
		struct msg b;
		msgrcv(id_coda, &a, sizeof(a)-sizeof(long), 0,
0);
		if (strcmp (a.mes,"exit")==0) {
			char bt[3000];
			strcpy (bt,"exit");
			int ris=write (pipefd[1],bt,strlen(bt)+1);
			if (ris==-1) {
				perror ("Errore scrittura pipe  \n");
				exit (6);
			}
			break;
		}

		
		msgrcv(id_coda, &b, sizeof(b)-sizeof(long), 0,
0);
		char buff [50000];
		int ok=0;
		char* ptr=strtok (a.mes,"\n");
		strcpy (buff,"");
		while (ok==0) {
			strcat(buff,b.mes);
			strcat (buff," -> ");
			strcat (buff,ptr);
			strcat (buff,"\n");
			ptr=strtok (NULL,"\n");
			if (ptr==NULL) ok=1;
		}

		int i=1;
		while (i<argc) {
			if (strcmp(argv[i],"-v")!=0 && 	strcmp(argv[i],"-i")!=0	&& strstr(argv[i],".txt")!=NULL) break;	
			i++;
		}
		char word[4000];
		i--;
		strcpy (word,argv[i]);
		int v=0;
		int li=0;
		while (i>=2) {
			if (strcmp(argv[i],"-v")==0) v=1;
			if (strcmp(argv[i],"-i")==0) li=1;
			i--;
		}
		
		char send[100000];
		strcpy (send,"Risultato: \n");
		strcpy (send,"\n");
		//printf ("i %d v %d \n",li,v);
		//printf ("Word %s \n",word);
		if	(v==1 && li==1) {
			ptr=strtok (buff,"\n");
			ok=0;
			while (ok==0) {
								
				if (strcasestr (ptr,word)==NULL) {
					strcat (send,ptr);
					strcat (send,"\n");
				}
				ptr=strtok (NULL,"\n");
				if (ptr==NULL) ok=1;	
			}
		}else{

			if (v==1){
				ptr=strtok (buff,"\n");
				ok=0;
				while (ok==0) {
					//printf ("Ptr %s \n",ptr);
					
					if (strstr (ptr,word)==NULL) {
						strcat (send,ptr);
						strcat (send,"\n");
					}
					ptr=strtok (NULL,"\n");
					if (ptr==NULL) ok=1;	
				}
			}

			if (li==1) {
				ptr=strtok (buff,"\n");
				ok=0;
				while (ok==0) {
								
					if (strcasestr (ptr,word)!=NULL) {
						strcat (send,ptr);
						strcat (send,"\n");
					}
					ptr=strtok (NULL,"\n");
					if (ptr==NULL) ok=1;	
				}		
			}
			if (li==0 && v==0) {
				ptr=strtok (buff,"\n");
				ok=0;
				while (ok==0) {
								
					if (strstr (ptr,word)!=NULL) {
						strcat (send,ptr);
						strcat (send,"\n");
					}
					ptr=strtok (NULL,"\n");
					if (ptr==NULL) ok=1;	
				}	
			}
		}

		int ris=write (pipefd[1],send,strlen(send)+1);
		if (ris==-1) {
			perror ("Errore scrittura pipe \n");
			exit (6);
		}
	}	
}

void gen_son (int argc,char** argv) {
	int pipefd[2];
	if (pipe(pipefd)==-1)  {
		perror ("Errore apertura pipe \n");
		exit (6);
	}	

	key_t chiave=IPC_PRIVATE;
	int id_coda=msgget(chiave, IPC_PRIVATE | 0666);
	int pid=-6;

	pid=fork();
	if (pid!=0) {
		int i=1;

		while (i<argc) {
			if (strcmp(argv[i],"-v")!=0 && 	strcmp(argv[i],"-i")!=0	&& strstr(argv[i],".txt")!=NULL) break;	
			i++;
		}

		while (i<argc) {
			pid=fork();
			if (pid!=0) {
				//PADRE
				padre(pipefd);
			}else{
				//READER
				reader (id_coda,argv[i],i,argc);
				exit(7);
			}
			i++;
		}
	}else{
		//FILETER
		close (pipefd[0]);
		filter (pipefd,id_coda,argv,argc);
		exit(5);
	}
	close (pipefd[0]);	
	close (pipefd[1]);
	msgctl (id_coda,IPC_RMID,NULL);
}

int main (int argc,char** argv) {
	if (argc<3) {
		printf ("Passati pochi argomenti \n");
		exit(6);
	}
	gen_son (argc,argv);
}
