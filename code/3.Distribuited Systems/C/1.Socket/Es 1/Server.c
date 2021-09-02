#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

int sock;
void get () {
	close(sock);
	exit(1);
}

int cubo (int n) {
	return n*n*n;
}
int main (int argc,char** argv) {
	char buffer[4096];
	strcpy (buffer,"");	
	
	sock=socket (AF_INET,SOCK_STREAM,0);
	if (sock==-1) {
		perror ("Errore creazione socket \n");
		exit (0);
	}
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int)) < 0){
    		perror("setsockopt(SO_REUSEADDR) failed");
	}

	signal(SIGINT,get);
	
	struct sockaddr_in addr;
	struct sockaddr_in rem_addr;
	socklen_t len=sizeof (addr);
	socklen_t rem_len=sizeof(rem_addr);
	addr.sin_family=AF_INET;
	addr.sin_port=3333;
	inet_aton("127.0.0.1",&addr.sin_addr);
	
	int ris=bind (sock,(struct sockaddr *) &addr,len);
	if (ris==-1) {
		perror ("Errore binding socket \n");
		exit (-5);
	}

	ris=listen (sock,5);
	if (ris==-1) {
		perror ("Errore listen socket \n");
		exit (-5);
	}
		
	while (1) {

		printf ("In attesa di Connessioni \n");

		strcpy (buffer,"");

		int o_sock=accept (sock,(struct sockaddr *) &rem_addr,&rem_len);
		if (o_sock==-1) {
			perror ("Errore accept socket \n");
			exit (-5);
		}

		printf ("Nuovo client connesso \n");

		ssize_t n_byte=read (o_sock,&buffer,4096);
		if (n_byte==-1) {
			perror ("Errore lettura dati dal buffer \n");
			exit (-5);
		}

		if (n_byte>0) {
			buffer[n_byte-1]='\0';
			printf ("Ricevuto dal Client: %s \n",buffer);

			int val=atoi(buffer);
			strcpy (buffer,"");
			val=cubo(val);
			sprintf(buffer,"%d",val);

			n_byte=write (o_sock,&buffer,4096);
			if (n_byte==-1) {
				perror ("Errore scrittura file \n");
				exit (-5);
			}
			
		}else{
			strcpy (buffer,"NOTHING REC");

			n_byte=write (o_sock,&buffer,4096);
			if (n_byte==-1) {
				perror ("Errore scrittura file \n");
				exit (-5);
			}	
		}

		close (o_sock);		
	}

	close (sock);

}
