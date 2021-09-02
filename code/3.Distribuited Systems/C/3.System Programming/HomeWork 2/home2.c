/*
    Homework n.2

    Estendere l'esempio 'move.c' visto a lezione per supportare i 2 casi speciali:
    - spostamento cross-filesystem: individuato tale caso, il file deve essere
      spostato utilizzando la strategia "copia & cancella";
    - spostamento di un link simbolico: individuato tale caso, il link simbolico
      deve essere ricreato a destinazione con lo stesso contenuto (ovvero il percorso
      che denota l'oggetto referenziato); notate come tale spostamento potrebbe
      rendere il nuovo link simbolico non effettivamente valido.

    La sintassi da supportare e' la seguente:
     $ homework-2 <pathname sorgente> <pathname destinazione>
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <libgen.h>
#include <unistd.h>

#define BUF_S 1024

int main (int argc,char** argv) {

	char buf[BUF_S];
	int sd,dd;
	int num=argc;
	int count=1;
	struct stat f;
	struct stat g;
	if (argc <3) {
		printf ("Errore \n");
		exit(1);
	}
	int s=0;
	do{
		char str[3000];
		char wk[3000];

		if (strcmp(argv[count],"sim")!=0) {

		s=0;

		char t[3000];
		int value=strlen(argv[count]);
		strcpy(t,argv[count]);
		

		while (strstr(argv[count],"txt")==NULL) {
			count++;
			s=2;
			t[value]=' ';
			value++;
			strcat(t,argv[count]);
			value+=strlen(argv[count]);
		}

		
		
		if (s==2) {
			strcpy(wk,t);
		}else{
			strcpy(wk,argv[count]);
		}		

		}else{
			count++;
			strcat(wk,argv[count]);
			printf ("str %s \n",wk);
		}
		lstat(wk,&f);
		stat(argv[argc-1],&g);

		if (!S_ISLNK(f.st_mode)) {
			if (f.st_dev!=g.st_dev) {
				sd=open (wk,O_RDONLY);	
				if (sd==-1) {
					printf ("Errore sd argv: %d \n",count);
					perror(wk);			
					exit(1);
				}
				if (strstr (wk,"/")!=NULL) {
					int i=strlen(wk);
					i--;

					while (wk[i]!='/'){
						i--; 			
					}

					i++;
					int index=i;
					int c=0;
					char q[3000];

					while (index<strlen(wk)) {
						q[c]=wk[index];	
						c++;
						index++;
					}

					strcpy(str,argv[argc-1]);
					strcat(str,q);
					int val=strlen(argv[argc-1])+strlen(q);
					str[val]='\0';
				}else{
					strcat(str,argv[argc-1]);
					strcat(str,argv[count]);
				}

				dd=open (str,O_WRONLY | O_CREAT | O_TRUNC,0666);	
				if (dd==-1) {
					printf ("Errore dd argv: %d \n",count);			
					exit(1);	
				}

				int size=0;
				int dest=0;
	
				do{

					size=read(sd,buf,BUF_S);
					if (size==-1) {
						printf ("Errore lettura sd argv %d \n",count);
						exit(1);
					}

					dest=write (dd,buf,size);
					if (dest==-1) {
						printf ("Errore scrittura dd argv %d \n",count);				
						exit(1);
					}
			
				}while (size==BUF_S);
				unlink (wk);
				count++;
			}else{
				char z[3000];
				strcat(z,argv[argc-1]);

				int i=strlen(wk);
				i--;

				while (wk[i]!='/'){
					i--; 			
				}			

				i++;
				int index=i;
				int c=0;
				char q[3000];

				while (index<strlen(wk)) {
					q[c]=wk[index];	
					c++;
					index++;
				}
				strcat(z,q);
				link(wk,z);
				unlink(wk);
				count++;
			}
		}else{

			char z[3000];
			strcat(z,argv[argc-1]);

			int i=strlen(wk);
			i--;
			
			while (wk[i]!='/'){
				i--; 			
			}			

			i++;
			int index=i;
			int c=0;
			char q[3000];
			
			while (index<strlen(wk)) {
				q[c]=wk[index];	
				c++;
				index++;
			}
			char buf[3000];	
			readlink(wk,buf,sizeof(buf));
			strcat(z,q);
			symlink(buf,z);
			unlink(wk);
			count++;	
		}
	}while (count<argc-1);
}








