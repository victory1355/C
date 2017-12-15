#include "head4sock.h"

#define MAXSIZE 80 

void usage(const char *info)
{
	printf("Usage: %s <PORT>\n", info);	
	exit(0);
}


int main(int argc, char *argv[]) // ./udpsrv 50001
{
	if(argc != 2)
		usage(argv[0]);

	int fd;

	// 1
	fd = Socket(AF_INET, SOCK_DGRAM, 0);

	// 2 bind
	struct sockaddr_in srvaddr;
	bzero(&srvaddr, sizeof(srvaddr));

	srvaddr.sin_family = AF_INET;
	srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	srvaddr.sin_port = htons(atoi(argv[1]));

	Bind(fd, (struct sockaddr *)&srvaddr, sizeof(srvaddr));

	char *buf = calloc(1, MAXSIZE);
	struct sockaddr_in cliaddr;
	socklen_t len = sizeof(cliaddr);
	while(1)
	{
		bzero(buf, MAXSIZE);
		bzero(&cliaddr, len);

		recvfrom(fd, buf, MAXSIZE, 0,
			(struct sockaddr *)&cliaddr, &len);

		printf("from %s:%hu: %s",
				inet_ntoa(cliaddr.sin_addr),
				ntohs(cliaddr.sin_port),
				buf);
	}

	close(fd);

	return 0;
}
