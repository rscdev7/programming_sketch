#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>

int counter=1;

struct msg {
	long id;
	char txt[3000];
};

void num_files (char* str,int id_coda) {	
	struct stat buffer; 
	stat(str, &buffer);
	int c=0;
	if (S_ISDIR(buffer.st_mode)) {
		DIR* a=opendir(str);
		if (a!= NULL) {
			struct dirent* k=readdir(a);
			while (k!=NULL) {	
				c++;
				k=readdir(a);		
			}
			struct msg w;
			w.id=70;
			sprintf (w.txt,"%d",c);
			msgsnd(id_coda, &w, strlen(w.txt)+1, 0);
			closedir(a);
		}else{
			perror("Errore apertura ");
		}
	}
}

void total_size (char* str,int id_coda) {
	struct stat buffer;
	struct stat y; 
	stat(str, &buffer);
	int dim=0;
	if (S_ISDIR(buffer.st_mode)) {
		DIR* a=opendir(str);
		if (chdir (str)==-1) {
			printf ("Errore cambio path \n");
			exit(1);
		}
		if (a!= NULL) {
			struct dirent* k=readdir(a);
			while (k!=NULL) {
				stat(k->d_name,&y);
				if (strcmp (k->d_name,".")!=0 && strcmp (k->d_name,"..")!=0 && !S_ISDIR(y.st_mode)) { 	
					dim=dim+y.st_size;
				}
				k=readdir(a);		
			}
			struct msg w;
			w.id=70;
			sprintf (w.txt,"%d",dim);
			msgsnd(id_coda, &w, strlen(w.txt)+1, 0);
			closedir(a);
		}else{
			perror("Errore apertura ");
		}
	}
}

void search_char (char* str,int id_coda,char* gen) {
	strtok(gen," ");
	strtok(NULL," ");
	char* file=strtok (NULL," ");	
	char* ch=strtok (NULL," ");
	if (chdir (str)==-1) {
			printf ("Errore cambio path \n");
			exit(1);
	}
	int fd=open (file,O_RDONLY | 0666);
	if (fd==-1) {
		perror ("Errore aper \n");
		exit(1);
	}
	struct stat fl;
	stat(file,&fl);
	char* m=(char *)mmap(NULL, fl.st_size, PROT_READ, MAP_PRIVATE,
fd, 0);
	if (m== MAP_FAILED) {
		perror ("Errore map \n");
		exit (1);
	}

	int occ=0;
	int k=0;
	char j=' ';
	for (k=0;k<fl.st_size;k++) {
		j=ch[0];
		if (m[k]==j) occ++;
	}
	struct msg a;
	a.id=70;
	char bf[300];
	sprintf (bf,"%d",occ);
	strcpy(a.txt,bf);
	msgsnd(id_coda, &a, strlen(a.txt)+1, 0);
}

void son (char* str,int id_coda,int index) {
	if (id_coda==-1) {
		perror ("Errore apertura coda \n");
		exit (2);
	}
	while (1) {
		struct msg w;
		int uy=msgrcv(id_coda, &w, sizeof(w)-sizeof(long), index,
0);
		if (uy!=-1) {
			if (strcmp(w.txt,"exit")==0) break;
			if (strstr (w.txt,"num-files")!=NULL) num_files (str,id_coda);
			if (strstr (w.txt,"total-size")!=NULL) total_size (str,id_coda);
			if (strstr (w.txt,"search-char")!=NULL) search_char (str,id_coda,w.txt);
		}else{
			perror ("err ");
			break;		
		}
	}
	exit(2);
}

void gen_son (int argc,char** argv,int id_coda) {
	int pid=-5;
	int val=counter;
	if ((pid=fork())!=0) {
		counter++;
		if (counter<argc) gen_son(argc,argv,id_coda);
	}else{
		son (argv[val],id_coda,val);
	}
}

void terminale (int id_coda,int argc,char** argv) {
	char str[3000];
	strcpy (str,"");
	int i=1;
	while (strcmp (str,"exit")!=0) {
		printf ("-> ");
		strcpy(str,"");
		fgets (str,3000,stdin);
		
		str[strlen(str)-1]='\0';
		if (strcmp (str,"exit")!=0) {
			if (strstr (str,"num-files")!=NULL || strstr (str,"total-size")!=NULL || strstr (str,"search-char")!=NULL) {
				for (i=1;i<argc && i!=99;i++) {
					char cmp[300];
					sprintf (cmp,"%d",i);
					if (strstr(str,cmp)!=NULL) {
						struct msg a;
						a.id=i;
						strcpy(a.txt,str);
						msgsnd(id_coda, &a, strlen(a.txt)+1, 0);	
						i=99;
					}
				}
				if (i==100) {
					struct msg w;
					msgrcv(id_coda, &w, sizeof(w)-sizeof(long), 70,
0);
					printf ("%s \n",w.txt);

				}
			}
		}else{
			for (i=1;i<argc;i++) {
				struct msg a;
				a.id=i;
				strcpy(a.txt,"exit");
				msgsnd(id_coda, &a, strlen(a.txt)+1, 0);
			}
		}
	} 		
}


int main (int argc,char** argv) {
	if (argc<2) {
		printf ("Pochi argomenti \n");
		exit (1);
	}

	key_t chiave=800;
	int id_coda=msgget(chiave, IPC_CREAT | 0666);
	gen_son (argc,argv,id_coda);
	terminale (id_coda,argc,argv);
	msgctl(id_coda, IPC_RMID, NULL);
}
