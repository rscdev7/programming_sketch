#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>


int main (int argc,char** argv) {

	char buffer[4096];
	strcpy (buffer,"");

	int sock=socket (AF_INET,SOCK_STREAM,0);
	if (sock==-1) {
		perror ("Errore creazione socket \n");
		exit (-5);
	}

	struct sockaddr_in rem_addr;
	socklen_t len=sizeof (rem_addr);
	rem_addr.sin_family=AF_INET;
	rem_addr.sin_port=3333;
	inet_aton ("127.0.0.1",&rem_addr.sin_addr);

	int ris=connect (sock,(struct sockaddr * ) &rem_addr,len);
	if (ris==-1) {
		perror ("Errore connect socket \n");
		exit (-5);	
	}

	printf ("Inserisci il titolo del libro \n");
	scanf ("%s",buffer);
	
	ris=write (sock,buffer,strlen (buffer)+1);
	if (ris==-1) {
		perror ("Errore scrittura socket \n");
		exit (-5);	
	}	

	ris=read (sock,buffer,4096);
	if (ris==-1) {
		perror ("Errore lettura socket \n");
		exit (-5);	
	}

	if (ris>0) {
		buffer[ris-1]='\0';
		printf ("Messaggio ricevuto dal Server: %s \n",buffer);
	}
	close(sock);
}
