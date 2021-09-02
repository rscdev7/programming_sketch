/*
	Nominativo: Rosario Scalia
	Matricola: X81000374

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/sem.h>
#include <ctype.h>
#include <sys/mman.h>
char que[300];
int isPal (char* str) {
	int dim=strlen(str);
	int i=0;
	for (i=0;i<dim;i++) {
		if (str[i]==str[dim-1-i] || str[dim-1-i]==toupper(str[i]) || str[dim-1-i]==tolower(str[i])) {
			
		}else{
			return 0;
		}
	}
	return 1;		
}
void padre (char* coda_r,char* coda_w) {
	while (1) {
		char buffer[3000];
		int fd=open(coda_r, O_RDONLY, 0666);
		int n=read(fd,buffer,3000);
		if (n==-1) {
			perror ("Errore lettura file \n");
			int res=unlink (coda_r);
			if (res==-1) {
				perror ("Errore chiusura pipe \n");
				exit (3);
			}
			exit (7);
		}
		close (fd);
		if (strcmp(buffer,"exit")==0) {
			fd=open (coda_w,O_RDONLY | 0666);
			if (fd==-1) {
				perror ("Errore apertura file \n");
				int res=unlink (coda_w);
				if (res==-1) {
					perror ("Errore chiusura pipe \n");
					exit (3);
				}
				exit (7);
			}
			n=write (fd,buffer,strlen(buffer)+1);
			if (n==-1) {
				perror ("Errore scrittura file \n");
				int res=unlink (coda_w);
				if (res==-1) {
					perror ("Errore chiusura pipe \n");
					exit (3);
				}
				exit (7);
			}
			close (fd);	
			exit(5);
		}
		if (isPal (buffer)==1) {
			fd=open (coda_w,O_RDONLY | 0666);
			if (fd==-1) {
				perror ("Errore apertura file \n");
				int res=unlink (coda_w);
				if (res==-1) {
					perror ("Errore chiusura pipe \n");
					exit (3);
				}
				exit (7);
			}
			n=write (fd,buffer,strlen(buffer)+1);
			if (n==-1) {
				perror ("Errore scrittura file \n");
				int res=unlink (coda_w);
				if (res==-1) {
					perror ("Errore chiusura pipe \n");
					exit (3);
				}
				exit (7);
			}
			close (fd);
		}
	}
}

int find_end (char* st,int dim) {
	int c=1;
	while (st[dim-c]=='\n') {
		c++;
	}
	c=dim-c+1;
	return c;
}

void r (char* coda,int argc,char** argv) {
	if (argc==2) {
		int fd=open (argv[1],O_RDONLY | 0666);
		int fp=open (coda,O_RDONLY | 0666);
		if (fd==-1) {
			perror ("Errore apertura file \n");
			int res=unlink (coda);
			if (res==-1) {
				perror ("Errore chiusura pipe file \n");
				exit (3);
			}
			exit (7);
		}
		if (fp==-1) {
			perror ("Errore apertura coda \n");
			int res=unlink (coda);
			if (res==-1) {
				perror ("Errore chiusura pipe coda \n");
				exit (3);
			}
			exit (7);
		}
		struct stat b;
		stat (argv[1],&b);
		char* ptr=(char*)mmap(NULL, b.st_size, PROT_READ, MAP_PRIVATE,fd, 0);
		if (ptr!=MAP_FAILED) {
			int c=0;
			int max=find_end (ptr,b.st_size);
			char buffer [300];
			int val=0;
			while (val<max) {
				c=0;
				strcpy(buffer,"");
				while (ptr[c]!='\n') {
					c++;
					val++;
				}
				strncpy (buffer,ptr,c);
				buffer[c]='\0';
				val++;
				c++;
				ptr=ptr+c;
				sleep(1);
				int n=write (fp,buffer,strlen(buffer)+1);
				if (n==-1) {
					perror ("Errore scrittura file \n");
					int res=unlink (coda);
					if (res==-1) {
						perror ("Errore chiusura pipe \n");
						exit (3);
					}
					exit (7);
				}
			}
			sleep(1);
			strcpy(buffer,"exit");
			int n=write (fp,buffer,strlen(buffer)+1);
			if (n==-1) {
				perror ("Errore scrittura file \n");
				int res=unlink (coda);
				if (res==-1) {
					perror ("Errore chiusura pipe \n");
					exit (3);
				}
				exit (7);
			}
			close (fp);
			exit(4);
		}
	}else{
		char buffer[3000];
		while (1) {
			strcpy (buffer,"");
			printf ("Inserisci una parola \n");
			fgets (buffer,3000,stdin);
			buffer[strlen(buffer)-1]='\0';
			int fd=open (coda,O_RDONLY | 0666);
			if (fd==-1) {
				perror ("Errore apertura file \n");
				int res=unlink (coda);
				if (res==-1) {
					perror ("Errore chiusura pipe \n");
					exit (3);
				}
				exit (7);
			}
			int n=write (fd,buffer,strlen(buffer)+1);
			if (n==-1) {
				perror ("Errore scrittura file \n");
				int res=unlink (coda);
				if (res==-1) {
					perror ("Errore chiusura pipe \n");
					exit (3);
				}
				exit (7);
			}
			close (fd);
			if (strcmp(buffer,"exit")==0) return;
		}
	}
}
void reset (char* path_r,char* path_w) {
	int res=unlink (path_r);
	res=unlink (path_w);
}

void w (char* coda) {
	char buffer[3000];
	while (1) {
		strcpy (buffer,"");
		int fd=open(coda, O_RDONLY, 0666);
		int n=read(fd,buffer,3000);
		if (n==-1) {
			perror ("Errore lettura file \n");
			int res=unlink (coda);
			if (res==-1) {
				perror ("Errore chiusura pipe \n");
				exit (3);
			}
			exit (7);
		}	
		if (strcmp(buffer,"exit")==0) {
			reset (coda,que);
			exit(2);
		}
		if (n>1) printf ("Parola: %s \n",buffer);
		close (fd);
	}
}



int main (int argc,char** argv) {
	char path_r[3000];
	char path_w[3000];
	strcpy (path_r,"/home/rosario/coda_r");
	strcpy (path_w,"/home/rosario/coda_w");
	strcpy (que,"/home/rosario/coda_r");
	int res=mkfifo(path_r, 0666);
	if (res==-1) {
		perror ("Errore creazione pipe \n");
		exit (1);
	}

	res=mkfifo(path_w, 0666);
	if (res==-1) {
		perror ("Errore creazione pipe \n");
		exit (2);
	}

	int pid=-5;
	pid=fork();

	if (pid!=0) {
		pid=fork();
		if (pid!=0) {
			padre(path_r,path_w);	
		}else{
			//W
			w(path_w);
			exit(5);
		}
	}else{
		//R
		r(path_r,argc,argv);
		exit(6);
	}

	res=unlink (path_r);
	if (res==-1) {
		perror ("Errore chiusura pipe main \n");
		exit (3);
	}

	res=unlink (path_w);
	if (res==-1) {
		perror ("Errore chiusura pipe main \n");
		exit (4);
	}
}

