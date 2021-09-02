/* Sample UDP client */

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <math.h>
#include <time.h>
#include <netinet/in.h>
#include <arpa/inet.h>

FILE* fp;

int main(int argc, char**argv) {

	int sockfd, n;
	struct sockaddr_in remote_addr;
	char sendline[1000];
	char recvline[1000];
	sendline[0]='r';
	socklen_t len = sizeof(remote_addr);

	if (argc != 3){ 
		printf("usage:  UDPclient <remote_IP remote_port>\n");
    		return 1;
	}

	if((sockfd=socket(AF_INET,SOCK_DGRAM,0)) <0){ 
		printf("\nErrore nell'apertura del socket");
		return -1;
	}

	memset(&remote_addr,0,sizeof(remote_addr));
	remote_addr.sin_family = AF_INET;
	remote_addr.sin_addr.s_addr=inet_addr(argv[1]);
	remote_addr.sin_port=htons(atoi(argv[2]));	
   	int a=0;

	sendto(sockfd,sendline,strlen(sendline),0,
          (struct sockaddr *)&remote_addr, sizeof(remote_addr));

	printf ("\n");
	printf ("Risorsa Richiesta \n");

	n=recvfrom(sockfd,recvline,1000,0, &remote_addr, &len);
	recvline[n]=0;
	printf ("Risorsa Acquisita \n");

	fp=fopen ("res.txt","a");

	if (fp!=NULL) {
		while (a==0) {
			printf ("Inserisci una Stringa \n");
			scanf ("%s",&sendline);
			printf ("\n");
			if (strlen(sendline)>1 || strlen(sendline)==1 && sendline[0]!='x' && sendline[0]!='X') {
				fprintf (fp,"%s \n",sendline);
				printf ("Scrittura Effettuata \n");
			}else{
				a=1;
			}
		}
	}
	
	fclose (fp);
 	
	sendto(sockfd,sendline,strlen(sendline),0,
          (struct sockaddr *)&remote_addr, sizeof(remote_addr));

	printf ("Risorsa Rilasciata \n");
	printf ("\n");
}


