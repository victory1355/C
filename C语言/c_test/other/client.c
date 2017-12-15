#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

void usage(int argc, char **argv)
{
	if(argc != 3)
	{
		fprintf(stderr, "Usage: %s <IP> <PORT>\n", argv[0]);
		exit(0);
	}

}

void *routine(void *arg)
{
	int arg1 = (int)arg;
	char *msg = calloc(1,1024);
	while(1)
	{
		bzero(msg, sizeof(msg));
		if(read(arg1, msg, 1024) != -1)
		{
			
			printf("rec :%s\n",msg);
		}	
	}
	
	
}

int main(int argc, char **argv) // ./client 192.168.10.xxx 50001
{
	usage(argc, argv);	

	// 1, 创建了一个TCP套接字
	int fd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in srvaddr;
	socklen_t len = sizeof(srvaddr);
	bzero(&srvaddr, len);

	srvaddr.sin_family = AF_INET;
	srvaddr.sin_port = htons(atoi(argv[2]));
	srvaddr.sin_addr.s_addr = inet_addr(argv[1]);
	
	int rec;
	// 2, 连接对端（IP + PORT）
	rec = connect(fd, (struct sockaddr *)&srvaddr, len);
	if(rec == -1)
	{
		printf("connect error");
		return -1;
	}
	// 3, 创建一条线程专门用来接收服务端发来的消息
	pthread_t tid;
	pthread_create(&tid, NULL, routine, (void *)fd);

	// 4, 主线程专门负责监听标准输入，将数据及时发给服务端
	char *msg = calloc(1, 1024);
	while(1)
	{
		bzero(msg, 1024);
		if(fgets(msg, 1024, stdin) == NULL)
			break;
		
		write(fd, msg, strlen(msg));
	}

	close(fd);
	return 0;
}


