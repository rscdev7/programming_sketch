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
#include <dirent.h>

#define BUF_S 1024



void copy_file (char* file_path, char* dest_path) {
	int sd,dd;
	char buf[BUF_S];
	struct stat info_file;
	struct stat info_path;	
	lstat(file_path,&info_file);
	stat(dest_path,&info_path);
	
	//	ESTRAZIONE NOME FILE
			char str[3000];
			if (strstr (file_path,"/")!=NULL) {
					int i=strlen(file_path);
					i--;

					while (file_path[i]!='/'){
						i--; 			
					}

					i++;
					int index=i;
					int c=0;
					char q[3000];

					while (index<strlen(file_path)) {
						q[c]=file_path[index];	
						c++;
						index++;
					}

					strcpy(str,dest_path);
					strcat(str,q);
					int val=strlen(dest_path)+strlen(q);
					str[val]='\0';
				}else{
					strcat(str,dest_path);
					strcat(str,file_path);
				}
				//FINE ESTRAZIONE NOME FILE

	if (!S_ISLNK(info_file.st_mode)) {
		
		if (info_file.st_dev!=info_path.st_dev) {
		
			sd=open (file_path,O_RDONLY);	
			if (sd==-1) {
				printf ("Errore sd argv \n");
				perror(file_path);			
				exit(1);
			}
			
			//CREAZIONE FILE DESTINAZIONE
			dd=open (str,O_WRONLY | O_CREAT | O_TRUNC,0666);	
			if (dd==-1) {
				printf ("Errore dd argv \n");			
				exit(1);	
			}

			int size=0;
			int dest=0;

			//INIZIO COPIA 
			do{

				size=read(sd,buf,BUF_S);
				if (size==-1) {
					printf ("Errore lettura sd argv \n");
					exit(1);
				}

				dest=write (dd,buf,size);
				if (dest==-1) {
					printf ("Errore scrittura dd argv \n");				
					exit(1);
				}
			
			}while (size==BUF_S);
		}else{
			link(file_path,str);				
		}

	}else{
		char app[3000];	
		readlink(file_path,app,sizeof(buf));
		symlink(app,str);
	}
}
void recursive_dir (char* dir_path, char* dest_path) {

	DIR* folder;
	struct dirent* current;
	struct stat info;

	folder=opendir (dir_path);
	if (folder==NULL) {
		printf ("Errore apertura cartella \n");
		exit(1);
	}
	if (chdir (dir_path)==-1) {
		printf ("Errore cambio path \n");
		exit(1);
	}

	while ((current=readdir(folder))!=NULL) {
		lstat(current->d_name,&info);
		printf ("now %s \n",current->d_name);		
		if (S_ISDIR(info.st_mode)) {
			
			if (strcmp(current->d_name,".")!=0 && strcmp(current->d_name,"..")!=0) {
				char next[3000];
				strcpy(next,"");
				strcat(next,dir_path);
				strcat (next,current->d_name);
				strcat (next,"/");	
				recursive_dir(next,dest_path);	

				if (chdir (dir_path)==-1) {
					printf ("Errore cambio path \n");
						exit(1);
				}		
			}
		}else{
			char fl [3000];
			char cart[3000];
			strcpy(fl,"");
			strcpy(cart,"");
			getcwd(cart,3000);
			strcat (cart,"/");
			strcat (fl,cart);
			strcat(fl,current->d_name);
			copy_file (fl,dest_path);
		}
		
	}
	closedir (folder);	
}


int main (int argc,char** argv) {
	struct stat a;
	int count=1;

	if (argc <3) {
		printf ("Errore \n");
		exit(1);
	}

	do{
		lstat(argv[count],&a);
		if (!S_ISDIR(a.st_mode)) {
			copy_file (argv[count],argv[argc-1]);
		}else{
			recursive_dir (argv[count],argv[argc-1]);
		}
		count++;
	}while (count<argc-1);
}








