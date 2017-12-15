#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "kernel_list.h"

pthread_mutex_t m;

typedef struct 
{
	unsigned short ID;
	int connfd;

	struct list_head list;
}clinode, *clilist;

clilist head = NULL;

void usage(int argc, char **argv)
{
	if(argc != 2)
	{
		fprintf(stderr, "Usage: %s <PORT>\n", argv[0]);
		exit(0);
	}
}

clilist newclient(int connfd, unsigned short ID)
{
	clilist new = calloc(1, sizeof(clinode));
	if(new != NULL)
	{
		new->ID	= ID;
		new->connfd = connfd;

		INIT_LIST_HEAD(&new->list);
	}

	return new;
}

void show_client(clilist head)
{
	struct list_head *pos;
	clilist p;

	//pthread_mutex_lock(&m);
	list_for_each(pos, &head->list)
	{
		p = list_entry(pos, clinode, list);	
		printf("ID: %hu\n", p->ID);
	}
	//pthread_mutex_unlock(&m);
}

void private_talk(unsigned short receiver_ID, char *msg)
{
	struct list_head *pos;
	clilist p;

	bool flag = false;
	
	printf("[%d]\n", __LINE__);
//	pthread_mutex_lock(&m);
	list_for_each(pos, &head->list)
	{
		p = list_entry(pos, clinode, list);	

		if(p->ID == receiver_ID)
		{
			write(p->connfd, msg, strlen(msg));
			flag = true;
			break;
		}
	}
	//pthread_mutex_unlock(&m);

	if(!flag)
	{
		printf("没有这个人！\n");
	}
}

void broadcast(clilist sender, char *msg)
{
	struct list_head *pos;
	clilist p;

	printf("[%d]\n", __LINE__);
	//pthread_mutex_lock(&m);
	list_for_each(pos, &head->list)
	{
		p = list_entry(pos, clinode, list);	

		if(p->ID == sender->ID)
		{
			continue;
		}
		//printf()
		printf("[%d]\n", __LINE__);
		write(p->connfd, msg, strlen(msg));
	}
	//pthread_mutex_unlock(&m);
}

void process_msg(clilist sender)
{
	char *msg = calloc(1, 1024);
	int nread;

	while((nread=recv(sender->connfd, msg, 1024, 0)) == -1 && errno == EINTR);

	// hits a real error
	if(nread == -1)
	{
		fprintf(stderr, "recv() failed: %s\n", strerror(errno));
		return;
	}
	// peer closed
	else if(nread == 0)
	{
		list_del(&sender->list);
		free(sender);
		return;
	}
	// received some data
	else
	{
		// 私聊
		char *tmp;
		if((tmp=strstr(msg, ":")) != NULL)
		{
			printf("[%d]\n", __LINE__);
			private_talk(atoi(msg), tmp+1);
		}
		// 群发
		else
		{
			broadcast(sender, msg);
		}
	}

	free(msg);
}

clilist init_list(void)
{
	head = calloc(1, sizeof(clinode));
	if(head != NULL)
	{
		INIT_LIST_HEAD(&head->list);
	}

	return head;
}

int main(int argc, char **argv) // ./Server 50001
{
	usage(argc, argv);

	// 1, 创建了一个TCP套接字
	int fd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in srvaddr;
	socklen_t len = sizeof(srvaddr);
	bzero(&srvaddr, len);

	srvaddr.sin_family = AF_INET;
	srvaddr.sin_port = htons(atoi(argv[1]));
	srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	// 2, 绑定地址（IP + PORT）
	if(bind(fd, (struct sockaddr *)&srvaddr, len) == -1)
	{
		fprintf(stderr, "bind() failed: %s\n", strerror(errno));
		exit(0);
	}

	// 3, 设置监听状态
	listen(fd, 3);

	struct sockaddr_in cliaddr;
	len = sizeof(cliaddr);
	bzero(&cliaddr, len);

	// 4, 创建一个空的用户链表
	head = init_list();
	if(head == NULL)
	{
		fprintf(stderr, "init_list() failed: %s\n",
				strerror(errno));	
		exit(0);
	}
	//地址复用
	const int on = 1;
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof on);
	//pthread_mutex_init(&m, NULL);


	fd_set rset; // 将所有需要处理的fd统统加进入
	int maxfd;

	struct list_head *pos;
	struct list_head *n, *posn;
	clilist p;
	
	printf("welcome to cheap QQ server\n");
	
	while(1)
	{
		FD_ZERO(&rset);

		// 1,将监听套接子搞进去
		FD_SET(fd, &rset);
		maxfd = fd;

		// 2,遍历用户链表，将所有的已连接套接子搞进去，顺便取得最大的maxfd
		//struct list_head *
		list_for_each_safe(pos, posn, &head->list)
		{
			p = list_entry(pos, clinode, list);
			FD_SET(p->connfd, &rset);

			maxfd = maxfd > p->connfd ? maxfd : p->connfd;
		}

		// 无限等待rset中的任意一个或多个fd读就绪... ...
		select(maxfd+1, &rset, NULL, NULL, NULL);

		// 等了很久之后，select返回了....

		// 1, 有新的连接请求！
		if(FD_ISSET(fd, &rset))
		{

			int connfd = accept(fd, (struct sockaddr *)&cliaddr, &len);
	
			printf("Welcome: %s:%hu\n", inet_ntoa(cliaddr.sin_addr),
						    ntohs(cliaddr.sin_port));

			// 更新当前用户列表
			clilist new = newclient(connfd, ntohs(cliaddr.sin_port));

			list_add(&new->list, &head->list);
		}

		// 2, 遍历所有的用户节点，一个个判断是否有人发来数据
		list_for_each_safe(pos, n, &head->list)
		{
			p = list_entry(pos, clinode, list);

			// 果然有客户端发来数据！
			if(FD_ISSET(p->connfd, &rset))
			{
				process_msg(p);
			}
		}
	}

	return 0;
}
