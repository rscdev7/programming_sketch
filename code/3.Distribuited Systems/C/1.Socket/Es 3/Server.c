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

struct Libro{
	char titolo[50];
	int n_copie;
};
struct Libro* v;
void init () {
	v=malloc(4*sizeof(struct Libro));

	strcpy (v[0].titolo,"Cormen");
	v[0].n_copie=5;

	strcpy (v[1].titolo,"V_per_vendetta");
	v[1].n_copie=5;

	strcpy (v[2].titolo,"Rck");
	v[2].n_copie=5;

	strcpy (v[3].titolo,"SSL");
	v[3].n_copie=5;
	
	/*for (int i=0;i<4;i++) {
		printf ("Libro: %s -- N_Copie= %d \n",v[i].titolo,v[i].n_copie);
	}*/
}

int main (int argc,char** argv) {
	
	init ();
	
	char buffer[4096];
	strcpy (buffer,"");

	int sock=socket (AF_INET,SOCK_STREAM,0);
	if (sock==-1) {
		perror ("Errore apertura socket \n");
		exit (-4);
	}

	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int)) < 0){
    		perror("setsockopt(SO_REUSEADDR) failed");
	}

	struct sockaddr_in addr;
	struct sockaddr_in rem_addr;
	socklen_t len=sizeof (addr);
	socklen_t rem_len=sizeof (rem_addr);
	addr.sin_family=AF_INET;
	addr.sin_port=3333;
	inet_aton ("127.0.0.1",&addr.sin_addr);

	int ris=bind (sock,(struct sockaddr*) &addr,len);
	if (ris==-1) {
		perror ("Errore bind socket \n");
		exit (-4);		
	}

	ris=listen (sock,5);
	if (ris==-1) {
		perror ("Errore listen socket \n");
		exit (-4);		
	}

	while (1) {
		
		printf ("In attesa di nuove connesioni....... \n");

		int os=accept (sock,(struct sockaddr *) &rem_addr,&rem_len);
		if (os==-1) {
			perror ("Errore accept socket \n");
			exit (-5);
		}		
		
		printf ("Nuova Connessione \n");

		int n_byte=read (os,buffer,4096);
		if (n_byte==-1) {
			perror ("Errore lettura socket \n");
			exit (-3);
		}

		char* titolo=NULL;
		char*copie=NULL;
		titolo=strtok (buffer,",");
		copie=strtok (NULL,",");
		int find=0;
		for (int i=0;copie!=NULL&&titolo!=NULL&&i<4;i++) {
			if (strcmp (titolo,v[i].titolo)==0) {
				int val=atoi(copie);
				if (val<=v[i].n_copie) {
					find=1;
					break;
				}
			}
		}

		if (find==1) strcpy (buffer,"true");
		if (find==0) strcpy (buffer,"false");

		n_byte=write (os,buffer,strlen(buffer)+1);
		if (n_byte==-1) {
			perror ("Errore scrittura socket \n");
			exit (-3);
		}

		close(os);
	}	
}



