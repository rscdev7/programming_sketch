#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <ctype.h>

int somma_cifre (char* str) {
	int somma=0;
	int len=strlen (str);
	int i=0;
	for (i=0;i<len;i++) {
		if (isdigit(str[i])>0) {
			int num=str[i]-48;
			somma+=num;
		}	
	}
	return somma;
}

int main (int argc,char** argv) {
	
	char buffer[4096];
	strcpy (buffer,"");

	int sock=socket (AF_INET,SOCK_STREAM,0);
	if (sock==-1) {
		perror ("Errore apertura socket \n");
		exit(-5);
	}
	
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int)) < 0){
    		perror("setsockopt(SO_REUSEADDR) failed");
	}

	struct sockaddr_in addr;
	struct sockaddr_in rem_addr;
	socklen_t len=sizeof(addr);
	socklen_t rem_len=sizeof (rem_addr);
	addr.sin_family=AF_INET;
	addr.sin_port=3333;
	inet_aton ("127.0.0.1",&addr.sin_addr);
	
	int ris=bind (sock,(struct sockaddr*) &addr,len);
	if (ris==-1) {
		perror ("Errore bind socket \n");
		exit (-5);
	}

	ris=listen (sock,5);
	if (ris==-1) {
		perror ("Errore listening socket socket \n");
		exit (-5);
	}

	while (1) {
		printf ("Attendo nuove connesioni \n");

		int new=accept (sock,(struct sockaddr *) &rem_addr,&rem_len);
		if (new==-1) {
			perror ("Errore apertura socket \n");
			exit(-5);
		}

		printf ("Nuovo client connesso \n");
		int n=0;
		while (2) {
			n++;
			strcpy(buffer,"");
			printf ("In attesa di messaggi \n");
				

			int n_byte=read (new,&buffer,4096);
			if (n_byte==-1) {
				perror ("Errore lettura socket \n");
				exit(-5);
			}

			if (n_byte>0) {
				buffer[n_byte-1]='\0';
				if (strcmp (buffer,"exit")==0) break;

				printf ("Messaggio Ricevuto: %s \n",buffer);
				
				int val=somma_cifre (buffer);			
				printf ("Somma: %d,%d \n",somma_cifre(buffer),n);

				sprintf (buffer,"%d,%d",val,n);
				n_byte=write (new,&buffer,strlen(buffer)+1);
				if (n_byte==-1) {
					perror ("Errore scrittura socket \n");
					exit(-5);
				}
			}
		}
		close (new);
	}	
}
