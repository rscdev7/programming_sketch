/* Sample UDP server */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#define LEN 10

struct sockaddr_in vec[LEN];
int size=0;
int head=0;
int tail=0;

int enqueue (struct sockaddr_in a) {
	if (size!=LEN) {
		vec[tail]=a;
		tail++;
		size++;
		if (tail==LEN) {
			tail=0;		
		}
		return 1;	
	}
	return 0;
}
struct sockaddr_in* dequeue () {
	struct sockaddr_in* c=malloc(sizeof(struct sockaddr_in));
	if (size>0) {
		c=&vec[head];
		head++;
		size--;
		if (head==LEN) head=0;
	}
	return c;
}

int main(int argc, char**argv) {
	int sockfd, n;
  	extern int errno;
  	struct sockaddr_in local_addr, remote_addr;
  	struct sockaddr_in backup;
  	socklen_t len = sizeof(remote_addr);
  	char mesg[1000];

  	if (argc < 2) { 
		printf("Use: server listening_PORT");
		return 0;
  	}	 

	if ((sockfd=socket(AF_INET,SOCK_DGRAM,0)) <0) { 
		printf("\nErrore nell'apertura del socket");
    	return -1;
  	}

  	memset(&local_addr,0,sizeof(local_addr));
  	local_addr.sin_family = AF_INET;
  	local_addr.sin_addr.s_addr=htonl(INADDR_ANY);
  	local_addr.sin_port=htons(atoi(argv[1]));

  	if (bind(sockfd, (struct sockaddr *) &local_addr, sizeof(local_addr))<0){ 
		printf("\nErrore nel binding. Errore %d \n",errno);
	    return -1;
  	}

  int a=0;
  int verify=0;

	for (;;) {
		a=0;

		if (size==0) {
			n = recvfrom(sockfd,mesg,1000,0,(struct sockaddr *)&remote_addr,&len);
			enqueue(remote_addr);	
		}

		backup=*dequeue();
		sendto(sockfd,mesg,n,0,(struct sockaddr *)&backup,len);

		while (a==0) {
			n = recvfrom(sockfd,mesg,1000,0,(struct sockaddr *)&remote_addr,&len);

			if (remote_addr.sin_port==backup.sin_port &&
	   	    	remote_addr.sin_addr.s_addr==backup.sin_addr.s_addr) {
				a=1;
			}else{
				enqueue(remote_addr);
			}
		}
	}
}
