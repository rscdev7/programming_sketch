#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

int swap (char* pt1,char* pt2,int dim) {
	int contatore=0;
	do{
		if (*(pt1+contatore)>*(pt2+contatore)) {
			return 1;		
		}
		if (*(pt1+contatore)<*(pt2+contatore)) {
			return 0;		
		} 
		contatore++;
	}while (contatore<dim);
}


int main(int argc, char *argv[]) {

	int fd;
	char* sr;
	struct stat sb;

	if (argc<3) {
		printf ("Errore, passati pochi arg \n");
		exit(1);
	}

	if ((fd=open(argv[2],O_RDONLY))==-1) {
		printf ("Error apertura \n");
		exit(1);
	}

	int val=atoi(argv[1]);
	fstat (fd,&sb);
	sr=(char *)mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);

	int count=0;
	char* v[sb.st_size/val];
	int index=0;

	while (count<sb.st_size) {
		v[index]=&sr[count];		
		index++;
		count+=val;
	}
	int w=sb.st_size/val;
	
	int n1=0;  
    int n2=0;  
    char* temp=NULL;  

	for(n1=0; n1<w; n1++){
        for(n2=0; n2<w-n1-1; n2++){
				if(swap(v[n2],v[n2+1],w)==1){  //Scambio valori
                	temp=v[n2];
                	v[n2]=v[n2+1];
                	v[n2+1]=temp;
				}
		}
	}	
	
	/*for (n1=0;n1<w;n1++) {
		int p=0;
		while (p<val) {
			printf (" %c",*(v[n1]+p));
			p++;
		}
		printf ("\n");
	}*/

	int dd;
	if ((dd=open("ord.txt",O_WRONLY | O_CREAT | O_TRUNC,0666))==-1) {
		printf ("Error apertura \n");
		exit(1);
	}

	int result;
	int i=0;
	for (i=0;i<w;i++) {
		if ((result = write(dd, v[i], val)) == -1) {
            perror(argv[2]);
            exit(1);
        }
	}
	close (fd);
	close (dd);
	munmap(sr,sb.st_size);
}
