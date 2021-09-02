/*
    Homework n.1

    Scrivere un programma in linguaggio C che permetta di copiare un numero
    arbitrario di file regolari su una directory di destinazione preesistente.

    Il programma dovra' accettare una sintassi del tipo:
     $ homework-1 file1.txt path/file2.txt "nome con spazi.pdf" directory-destinazione
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#define BUF_S 1024

int main (int argc,char** argv) {

	char buf[BUF_S];
	int sd,dd;
	int num=argc;
	int count=1;

	if (argc <3) {
		printf ("Errore \n");
		exit(1);
	}
	int s=0;
	do{

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

		char str[3000];
		char wk[3000];

		if (s==2) {
			strcpy(wk,t);
		}else{
			strcpy(wk,argv[count]);
		}		

		sd=open (wk,O_RDONLY);	
		if (sd==-1) {
			printf ("Errore sd argv: %d \n",count);			
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

		count++;
	}while (count<argc-1);
}
