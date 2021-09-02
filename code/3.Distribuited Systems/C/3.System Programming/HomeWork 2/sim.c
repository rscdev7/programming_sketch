#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <libgen.h>
#include <unistd.h>

#define BUF_S 1024

int main (int argc,char** argv) {
	char y[4000];
	strcat(y,argv[argc-1]);
	symlink(argv[1],y);
}
