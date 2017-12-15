#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include "head4sock.h"

#define BUFFER_SIZE 1024

int main(int argc,char **argv)
{
	if(argc != 2)
	{
		fprintf(stderr,"Usage:%s <path>\n",argv[0]);
		exit(1);
	}

	int fd;
	fd = Socket(AF_LOCAL,SOCK_STREAM,0);

	struct sockaddr_un remote_address;
	bzero(&remote_address, sizeof remote_address);
	remote_address.sun_family = AF_LOCAL;
	memcpy(remote_address.sun_path,argv[1],strlen(argv[1]));
	
	Connect(fd,(struct sockaddr *)&remote_address,sizeof(remote_address));

	char buffer[BUFFER_SIZE];
	bzero(buffer, BUFFER_SIZE);
	ssize_t n;

	while((n=read(fd,buffer,BUFFER_SIZE)) == -1 && errno == EINTR);
	if(n == -1)
	{
		perror("read() failed");
		close(fd);
		exit(0);
	}
	else if(n == 0)
		fprintf(stdout,"Connection closed by peer.\n");
	else
	{
		fprintf(stdout,"read %d bytes from peer:%s\n", n, buffer);
	}

	close(fd);
	exit(0);
}
