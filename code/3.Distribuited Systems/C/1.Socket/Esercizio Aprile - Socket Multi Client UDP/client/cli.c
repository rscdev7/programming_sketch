/* Sample UDP client */

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

struct Pack{
	int sockfd;
	char* recvline;
	struct sockaddr_in rem;
	socklen_t lung;
};

void* rec (void* e) {
	struct Pack* v=(struct Pack*)e;
	for (;;) {
		int n=recvfrom(v->sockfd,v->recvline,1000,0, &(v->rem), &(v->lung));
    v->recvline[n]=0;
	printf("From IP:%s Port:%d msg:%s \n", inet_ntoa(v->rem.sin_addr),  ntohs(v->rem.sin_port), v->recvline);
	}
}


void tr (int* args) {
	printf ("Ciao \n");
	
	}

int main(int argc, char**argv) {
  int sockfd, n;
  struct sockaddr_in remote_addr;
  char sendline[1000];
  char recvline[1000];
  socklen_t len = sizeof(remote_addr);
  
  if (argc != 3)
  { printf("usage:  UDPclient <remote_IP remote_port>\n");
    return 1;
  }

  if((sockfd=socket(AF_INET,SOCK_DGRAM,0)) <0)
  { printf("\nErrore nell'apertura del socket");
    return -1;
  }
  
  memset(&remote_addr,0,sizeof(remote_addr));
  remote_addr.sin_family = AF_INET;
  remote_addr.sin_addr.s_addr=inet_addr(argv[1]);
  remote_addr.sin_port=htons(atoi(argv[2]));

  pthread_t re;
	struct Pack f;
	f.sockfd=sockfd;
	f.recvline=recvline;
	f.rem=remote_addr;
	f.lung=len;
	pthread_create(&re, NULL, &rec, &f);
  while (fgets(sendline, 1000,stdin) != NULL)
  { sendto(sockfd,sendline,strlen(sendline),0,
          (struct sockaddr *)&remote_addr, sizeof(remote_addr));
  }
}
