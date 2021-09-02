/*
    Homework n.5

    Estendere l'esempio 'nanoshell.c' ad una shell piu' realistica in cui
    si possono:
    - passare argomenti al comando invocato (per semplicita', assumiamo
    che questi non contengano spazi);
    - usare la redirezione dei canali di input/output/error;
    - mandare un comando in esecuzione in background (con la '&' finale).

    Esempi di invocazione che la shell dovrebbe supportare sono:
    $ cal 3 2015
    $ cp /etc/passwd /etc/hosts /tmp
    $ cat </dev/passwd >/tmp/passwd
    $ cat filechenonesiste 2>/dev/null
    $ ls -R /etc/ &
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>


struct ext{
	int ini;
	int end;
};

#define LEN_BUFFER 1024
#define DIM_V 1024

char* sub (char* stringa,int inizio,int fine) {	
	char* goal=malloc (1024);
	int i=0;
	int c=0;

	while (i<=fine) {
		if (i>=inizio) {
			goal[c]=stringa[i];	
			c++;
		}
		i++;
	}
	c++;
	goal[c]='\0';
	return goal;	
}

char* rig (char* ptr) {
	char* str=malloc (3000);
	int index=0;
	int ct=0;
	while (ptr[index]!='<') {
		index++;
	}
	index++;
	int len=strlen(ptr);
	while (index<len) {
		str[ct]=ptr[index];
		index++;		
		ct++;
	}
	strcat (str,".txt");
	return str;
}

int lef (char* ptr) {
	int std=10;
	int index=0;
	if (ptr[index]== '<') {
		return 1;
	}
	std=ptr[index]-'0';
	return std;
}

int rig_2 (char* ptr) {
	int std=-5;
	int index=0;
	while (ptr[index] != '>') {
		index++;
	}
	index++;
	if (ptr[index]== ' ') return 1;
	std=ptr[index]-'0';
	return std;
}

char* lef_2 (char* ptr) {
	char* str=malloc (3000);
	int index=0;
	int ct=0;
	while (ptr[index]!='>') {
		str[ct]=ptr[index];
		index++;		
		ct++;
	}
	strcat (str,".txt");
	return str;
}

int main(int argc, char *argv[]) {
    char comando[LEN_BUFFER];
    int pid, len;

    while (1) {
        printf("[pid= %i] Digitare un comando da eseguire ('quit' per uscire): ",getpid());
        fgets(comando, LEN_BUFFER, stdin);
        len = strlen(comando);
        if (comando[len - 1] == '\n')
            comando[len - 1] = '\0';

        if (strcmp(comando, "quit") == 0)
            break;

        pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(1);
        }
        if (pid == 0) {
			
			int i=0;
			int first=0;

			int bk=0;
			int contatore=0;
			int c2=0;

			char cmd[LEN_BUFFER];
			char* vector [DIM_V];

			int j=0;
			for (j=0;j<DIM_V;j++) {
				vector[j]=NULL;
			}

			while (i<len && first==0) {
				if (comando[i]==' ') {
					first=1;
				}else{
					cmd[i]=comando[i];
					i++;
				}
			}

			vector[0]=cmd;
			bk=i;
			
			while (bk<len) {
				if (comando[bk]==' ') {
					bk++;
				}else{
					if (comando[bk]!=' ' && comando[bk-1]==' ') {
						contatore++;
					}
					bk++; 		
				}
			}

			bk=i;
			struct ext interval[contatore];

			while (bk<len && c2<contatore) {
				if (comando[bk]==' ') {
					bk++;
				}else{
					if (comando[bk]!=' ' && comando[bk-1]==' ') {
						interval[c2].ini=bk;			
					}

					if (comando[bk]!=' ' && comando[bk+1] == ' ' || comando[bk+1] == '\0') {
						interval[c2].end=bk;
						c2++;	
					}
					bk++; 		
				}
			}

			if (contatore==1) {	

      			vector[1]=sub(comando,interval[0].ini,interval[0].end);
				vector[2]=NULL;

			}else{
			
				c2=1;
				int calc=0;
				for (calc=0;calc<contatore;calc++) {
					vector[c2]=sub(comando,interval[calc].ini,interval[calc].end);
					c2++;
				}
				vector[c2]=NULL;
			}

			int cmp=c2-1;
			if (strstr("&",vector[cmp])) {
				int pid=fork();
				if (pid==0) {
					vector[cmp]=NULL;
					contatore--;

					int rj=0;
					int stop=0;
					char* ptr=NULL;

					for (rj=0;rj<contatore+1;rj++) {
						ptr=strstr(vector[rj],"<");
						if (ptr!=NULL) {
							stop++;
						}

						ptr=strstr(vector[rj],">");
						if (ptr!=NULL) {
							stop++;
						}
					}

					if (stop>0) {
						int redc [stop];
						int r=0;

						for (rj=0;rj<contatore+1;rj++) {
							ptr=strstr(vector[rj],"<");
							if (ptr!=NULL) {
								redc[r]=rj;		
								r++;
							}
						
							ptr=strstr(vector[rj],">");
							if (ptr!=NULL) {
								redc[r]=rj;		
								r++;
							}
						}

						char* q[DIM_V];	
						int y=0;
						for (y=0;y<DIM_V;y++) q[y]=NULL;
						int base=0;

						for (rj=0;rj<contatore+1;rj++) {
							if (strstr(vector[rj],"<")==NULL &&
								strstr (vector[rj],">")==NULL) {
								q[base]=vector[rj];
								base++;
							}
						}
						q[base]=NULL;

						for (rj=0;rj<stop;rj++) {
							if (strstr (vector[redc[rj]],"<")!=NULL) {
							
								int std=lef (vector[redc[rj]]);
								char* file=rig (vector[redc[rj]]);
								int fd;
								if ((fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0660)) == -1) {
        						perror(argv[2]);
        						exit(1);
    							}	

								close (std);
								dup(fd);
							}else{
								int std=rig_2 (vector[redc[rj]]);
								char* file=lef_2(vector[redc[rj]]);

								int fd;
								if ((fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0660)) == -1) {
        							perror(argv[2]);
        							exit(1);
    							}	

								close (std);
								dup(fd);
							}
						}
					
					execvp (cmd,q);

            		fprintf(stderr, "Errore nell'esecuzione di '%s'\n", comando);
            		exit(2);
				}
				execvp (cmd,vector);
            	fprintf(stderr, "Errore nell'esecuzione di '%s'\n", comando);
           		exit(2);
				}else{
					exit(1);
				}
			}else{

				if (contatore==1 && strcmp(vector[1],"&")==0) {
					contatore--;
					vector[1]=NULL;
					vector[2]=NULL;
				}
				
				int rj=0;
				int stop=0;
				char* ptr=NULL;

				for (rj=0;rj<contatore+1;rj++) {

					ptr=strstr(vector[rj],"<");
					if (ptr!=NULL) {
						stop++;
					}

					ptr=strstr(vector[rj],">");
					if (ptr!=NULL) {
						stop++;
					}
				}
				if (stop>0) {
					int redc [stop];
					int r=0;

					for (rj=0;rj<contatore+1;rj++) {
						ptr=strstr(vector[rj],"<");
						if (ptr!=NULL) {
							redc[r]=rj;		
							r++;
						}
						
						ptr=strstr(vector[rj],">");
						if (ptr!=NULL) {
							redc[r]=rj;		
							r++;
						}
					}

					char* q[DIM_V];	
					int y=0;
					for (y=0;y<DIM_V;y++) q[y]=NULL;
					int base=0;

					for (rj=0;rj<contatore+1;rj++) {
						if (strstr(vector[rj],"<")==NULL &&
							strstr (vector[rj],">")==NULL) {
							q[base]=vector[rj];
							base++;
						}
					}
					q[base]=NULL;

					for (rj=0;rj<stop;rj++) {
						if (strstr (vector[redc[rj]],"<")!=NULL) {
							
							int std=lef (vector[redc[rj]]);
							char* file=rig (vector[redc[rj]]);
							int fd;
							if ((fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0660)) == -1) {
        					perror(argv[2]);
        					exit(1);
    						}	

							close (std);
							dup(fd);
						}else{
							int std=rig_2 (vector[redc[rj]]);
							char* file=lef_2(vector[redc[rj]]);

							int fd;
							if ((fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0660)) == -1) {
        						perror(argv[2]);
        						exit(1);
    						}	

							close (std);
							dup(fd);
						}
					}
					execvp (cmd,q);
					exit(2);
				}
            	execvp (cmd,vector);
            	fprintf(stderr, "Errore nell'esecuzione di '%s'\n", comando);
            	exit(2);
			}
        } else {
            wait(NULL);
        }
    }
    exit(0);
}
