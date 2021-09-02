#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

int find_max (char* ptr,int limit) {
	int index=limit-1;
	while (index>=0) {
		if (ptr[index]!='\n') break;
		index--;	
	}
	index=index+1;
	return index;
}

void reader (char* file,int* pipefd) {
	int fd=open (file,O_RDONLY | 0666);
	if (fd==-1) {
		perror ("Errore apertura del file \n");
		exit (4);
	}

	struct stat buf;
	stat (file,&buf);

	char* ptr=(char*)mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE,
fd, 0);
	if (ptr==MAP_FAILED) {
		perror ("Errore mappatura memoria \n");
		exit (5);
	}

	int max=find_max(ptr,buf.st_size);
	int i=0;
	int c=0;
	char buffer[3000];
	int ris=0;

	while (i<max) {
		c=0;
		while (ptr[c]!='\n') {
			c++;
			i++;
		}	

		strcpy(buffer,"");
		strncpy(buffer, ptr, c);
		buffer[c]='\0';
		int dim=strlen(buffer);
		sleep(1);
		ris=write (pipefd[1],buffer,dim+1);
		if (ris==-1) {
			perror ("Errore scrittura su pipe \n");
			exit (6);
		} 

		ptr=ptr+c+1;
		i++;
	}
	
	sleep (1);
	strcpy (buffer,"exit");
	ris=write (pipefd[1],buffer,strlen(buffer)+1);
	if (ris==-1) {
		perror ("Errore scrittura su pipe \n");
		exit (6);
	}
	close (pipefd[0]);
	close (pipefd[1]);
}

void padre (int argc,char** argv,int* pipefd) {
	int sott=0;
	int i=0;
	int ris=0;
	while (i<argc) {
		if (strcmp (argv[i],"yet-another-fgrep")!=0 && strcmp (argv[i],"-v")!=0
			&& strcmp (argv[i],"-i")!=0 && strstr(argv[i],".txt")!=NULL) {
			break;
		}
		i++;		
	}
	sott=i;
	char word[4000];
	strcpy (word,argv[sott-1]);
	int pid=-5;
	char buffer[3000];
	char send[7000];
	while (sott<argc) {
		int pipe_w[2];
		ris=pipe(pipe_w);
		if (ris==-1) {
			perror ("Errore creazione Pipe P-O \n");
			exit(1);
		}
		strcpy (buffer,"");
		pid=fork();
		if (pid!=0) {
			while (strcmp (buffer,"exit")!=0) {
				strcpy (buffer,"");
				sleep(1);
				ris=read (pipe_w[0],buffer,3000);
				if (ris==-1) {
					perror ("Errore lettura pipe \n");
					exit (8);
				}
				if (strcmp (buffer,"exit")!=0) {
					if (strcmp(argv[2],"-v")==0) {
						if (strcmp(argv[3],"-i")==0) {
							if (strcasestr(buffer,word)==NULL) {
								strcpy(send,"");
								strcat (send,argv[sott]);
								strcat (send," - ");
								strcat (send,buffer);
					
								ris=write (pipefd[1],send,strlen(send)+1);
								if (ris==-1) {
									perror ("Errore scrittura pipe \n");
									exit (8);
								}
							}	
						}else{
							if (strstr(buffer,word)==NULL) {
								strcpy(send,"");
								strcat (send,argv[sott]);
								strcat (send," - ");
								strcat (send,buffer);
					
								ris=write (pipefd[1],send,strlen(send)+1);
								if (ris==-1) {
									perror ("Errore scrittura pipe \n");
									exit (8);
								}
							}			
						}	
					}else{
						if (strcmp(argv[2],"-i")==0) {
							if (strcmp(argv[3],"-v")==0) {
								if (strcasestr(buffer,word)==NULL) {
									strcpy(send,"");
									strcat (send,argv[sott]);
									strcat (send," - ");
									strcat (send,buffer);
					
									ris=write (pipefd[1],send,strlen(send)+1);
									if (ris==-1) {
										perror ("Errore scrittura pipe \n");
										exit (8);
									}
								}	
							}else{
								if (strcasestr(buffer,word)!=NULL) {
									strcpy(send,"");
									strcat (send,argv[sott]);
									strcat (send," - ");
									strcat (send,buffer);
					
									ris=write (pipefd[1],send,strlen(send)+1);
									if (ris==-1) {
										perror ("Errore scrittura pipe \n");
										exit (8);
									}
								}			
							}
						}else{
							if (strstr(buffer,word)!=NULL) {
								strcpy(send,"");
								strcat (send,argv[sott]);
								strcat (send," - ");
								strcat (send,buffer);
					
								ris=write (pipefd[1],send,strlen(send)+1);
								if (ris==-1) {
									perror ("Errore scrittura pipe \n");
									exit (8);
								}
							}		
						}		
					}
				}
			}
		}else{
			reader(argv[sott],pipe_w);
			exit(3);
		}
		sott++;
		close (pipe_w[0]);
		close (pipe_w[1]);
	}

	close (pipefd[0]);
	close (pipefd[1]);	
}

void outputer (int* pipefd) {
	char buffer[3000];
	while (1) {
		sleep(1);
		strcpy (buffer,"");
		int ris=read(pipefd[0],buffer,3000);
		if (ris==-1) {
			perror ("Errore apertura pipe outputer \n");
			exit(2);
		}
		if (strcmp (buffer,"exit")==0) {
			break;
		}
		printf ("%s \n",buffer);
	}
	close (pipefd[0]);
	close (pipefd[1]);
}

int main (int argc,char** argv) {
	if (argc<3) {
		printf ("Passati pochi argomenti \n");
		exit(1);
	}

	int pipefd[2];
	int d=pipe(pipefd);
	if (d==-1) {
		perror ("Errore creazione Pipe P-O \n");
		exit(1);
	}

	int pid=-5;
	pid=fork();
	if (pid!=0) {
		padre (argc,argv,pipefd);
		exit(7);
	}else{
		outputer (pipefd);
		exit(3);
	}
}
