#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>

int main (int argc,char** argv) {
	
	char buffer[4096];
	strcpy(buffer,"");

	int sock=socket (AF_INET,SOCK_STREAM,0);
	if (sock==-1) {
		perror ("Errore apertura socket \n");
		exit (-5);
	}
	
	struct sockaddr_in addr;
	socklen_t len=sizeof (addr);
	addr.sin_family=AF_INET;
	addr.sin_port=3333;
	inet_aton ("127.0.0.1",&addr.sin_addr);

	int ris=connect	(sock,(struct sockaddr *) &addr,len);
	if (ris==-1) {
		perror ("Errore connect sulla socket \n");
		exit (-5);
	}
	
	printf ("Inserisci il tuo messaggio \n");
	scanf ("%s",buffer);

	ris=write (sock,buffer,sizeof(buffer));
	if (ris==-1) {
		perror ("Errore lettura \n");
		exit (-5);
	}

	strcpy(buffer,"");
	ris=read (sock,buffer,4096);
	if (ris==-1) {
		perror ("Errore scrittura \n");
		exit (-5);
	}
	
	printf ("Messaggio Server: %s \n",buffer);

	close (sock);
	
}
