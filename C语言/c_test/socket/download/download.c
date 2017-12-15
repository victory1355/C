#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

#include <sys/socket.h>
#include <arpa/inet.h>

#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <unistd.h>

void progress(long long nread, long long filesize);

void usage(int argc)
{
	if(argc != 2)
	{
		printf("Usage: ./main www.boa.org/boa-0.94.14rc21.tar.gz\n");
		exit(1);
	}
}

void right_addr(char *domain, const char *argv)
{
	assert(argv);
	assert(domain);
	
	char *p;
	if(p = strstr(argv, "http://"))
	{
		printf("[%d]\n", __LINE__);
		 if(strcasecmp(argv, "http://www.com") ==0 )
		 {
			 printf("bad address format\n");
		     exit(1);
		 }else
		 {
			p = strchr(argv+strlen("http://"), '/');
			//printf("p = %s\n", p);
			//printf("%s\n", argv+strlen("http://"));
			strncpy(domain, argv+strlen("http://"), p-(argv+7));
			//printf("domain:%s\n", domain);
		 }
		 
	}
	else if(strstr(argv, "https://"))
	{
		printf("[%d]\n", __LINE__);
		if(strcasecmp(argv, "https://www.com") ==0 )
		 {
			 printf("bad address format\n");
			 exit(1);
		 }else
		 {
			p = strchr(argv+strlen("https://"), '/');
			//printf("p = %s\n", p);
			strncpy(domain, argv+strlen("https://"), p-(argv+strlen("https://")));
			//printf("domain:%s\n", domain);
		 }
	}
	else
	{
		printf("[%d]\n", __LINE__);
		p = strchr(argv, '/');
		if(p == NULL)
		{
			printf("ilegal address\n");
			exit(1);
		}
		//printf("p = %s\n", p);
		strncpy(domain, argv, p-argv);
		//printf("domain:%s\n", domain);
	}
	
}
int main(int argc, char **argv)
{
	usage(argc);
	char *domain = calloc(1, 100);
	bzero(domain, 100);
	
	right_addr(domain, argv[1]);
#ifdef DEBUG
	printf("domain name = %s\n", domain);
#endif
	struct hostent *p = gethostbyname(domain);
	if(p == NULL)
	{
		//perror("gethostbyname");
		printf("%s\n", strerror(h_errno));
		return -1;
	}
	int fd;
	if( (fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket");
		return -1;
	}
	struct sockaddr_in ser_addr;
	bzero(&ser_addr, sizeof ser_addr);
	
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(80);
	ser_addr.sin_addr = *((struct in_addr *)(p->h_addr_list[0]));
	
#ifdef DEBUG
	printf("IP:%s\n", inet_ntoa(ser_addr.sin_addr));
#endif
	
	
	
	
	if( connect(fd, (struct sockaddr *)&ser_addr, sizeof ser_addr) == -1)
	{
		perror("connect");
		return -1;
	}

	char *p1 = NULL;
	p1 = strrchr(argv[1], '/');
	
	char file_buf[1000];
	bzero(file_buf, sizeof file_buf);
	struct stat file_stat;                     //定义变量不可以放在判断语句里面,不然出现未申明错误
	bzero(&file_stat, sizeof file_stat);
	
	if(p1 != NULL)
	{
		snprintf(file_buf, sizeof file_buf, "/home%s", p1);
	}
	else{
		perror("strstr");
		return -1;
	}
#ifdef DEBUG	
	printf("download file = %s\n", file_buf);
	//while(1);
#endif

	FILE *fp = NULL;
	int total_read_len;
	
	if(access(file_buf, F_OK))
	{
		fp = fopen(file_buf, "w");
	}
	else
	{
		if(stat(file_buf, &file_stat) == -1)
		{
			perror("stat ");
			return -1;
		}
		else
		{
			total_read_len = file_stat.st_size;
		}
		
		fp = fopen(file_buf, "a");
		if(fp == NULL)
		{
			perror("fopen");
			return -1;
		}
		
	}
	
	char buf[1000], host_buf[1000];
	bzero(buf, sizeof buf);
	bzero(host_buf, sizeof host_buf);
	
	if(strstr(argv[1], "http"))
	{
		//strncpy(host_buf, argv[1]+7, ((p1+3) - (argv[1]+7)+1));
		//printf("%s\n", strchr(strchr(argv[1], '.')+1, '/'));
		
	//	while(1);
		snprintf(buf, sizeof(buf),"GET %s HTTP/1.1\r\n"
								  "Host: %s\r\n"
								  "Range: bytes=%d-\r\n\r\n",
								  strchr(strchr(argv[1], '.')+1, '/'), domain, (int)file_stat.st_size);
#ifdef DEBUG
		printf("==============request============= \n");
		printf("\n================================\n");
		printf("%s\n", buf);
		printf("================================\n");
#endif
	}
	else{
	
		//strncpy(host_buf, argv[1], ( (p1+3) - argv[1])+1);
		snprintf(buf, sizeof(buf),"GET %s HTTP/1.1\r\n"
								  "Host: %s\r\n"
								  "Range: bytes=%d-\r\n\r\n",
								  strchr(strchr(argv[1], '.')+1, '/'), domain, (int)file_stat.st_size);
#ifdef DEBUG
		printf("\n================================\n");
		printf("request = %s\n", buf);
		printf("================================\n");
#endif
	}
	
	if( write(fd, buf, strlen(buf)) ==-1)           //调用该函数出错会直接退出程序
	{
		perror("write");
		return -1;
	}
	char read_head[500];
	char read_content[100];
	char *p_content_length = NULL;
	bzero(read_head, sizeof read_head);
	int readn;
	
	//获取报头信息,只读一次
	int count = 0;
	while(1)
	{
		while( (readn = read(fd, read_head+count
					, sizeof (char))) ==-1  && errno == EINTR);
		if(readn == -1)
		{
			perror("read");
			return -1;
		}
		count++;
		if(strstr(read_head, "\r\n\r\n"))
		{	
			break;	
		}
		
	}
	
	//打印响应报头
#ifdef DEBUG
	printf("===========http respose=============\n");
	printf("==================================\n");
	printf("%s\n", read_head);
	printf("==================================\n");
#endif
	
	int content_length;
	//int content_range;
	p_content_length = strstr(read_head, "Content-Length");	
	char *p_content_range = strchr(strstr(read_head, "Content-Range"), '/');	
	
	if(p_content_length != NULL)
	{
		//p_content_length = p_content_length+strlen("Content-Length")+2;
		content_length = atoi(p_content_range+1);
#ifdef DEBUG
		//printf("%s\n", p_content_range);
		printf("content_length = %d\n", content_length);
		printf("file size = %lu\n", file_stat.st_size);
#endif
		if(file_stat.st_size == content_length)
		{
			printf("the file has existed, exit\n");
			close(fd);
			fclose(fp);
			return 0;
		}
		printf("content_length = %d\n", content_length);	
		//while(1);
	}
	else
	{
		printf("not found\n");
	}
	
	//获取实体内容     
	int fd1 = fileno(fp);
	if(fd1 < 0)
	{
		perror("fileno");
		return -1;
	}
	//printf("[%d]\n", __LINE__);
	while(1)
	{

		//bzero(read_content, sizeof read_content);
		while( (readn = read(fd, read_content, sizeof (read_content))) ==-1  && errno == EINTR);
		if(readn == -1)
		{
			perror("read");
			return -1;
		}
		write(fd1, read_content, readn);
	
		total_read_len += readn;
		progress(total_read_len, content_length);
	
		if(total_read_len == content_length)
		{
#ifdef DEBUG
			stat(file_buf, &file_stat);
	        printf("file_size = %lu\n", file_stat.st_size);
			printf("\nclose file\n");
#endif 
			close(fd1);
			close(fd);
			fclose(fp);
			break;
		}
		
	}

	return 0;
}



void progress(long long nread, long long filesize)
{
	struct winsize ws;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);

	int bar_len = ws.ws_col-32;
	bar_len = bar_len > 60 ? 60 : bar_len;

	int rate = filesize/bar_len;
	int cur  = nread/rate;

	char *total = calloc(1, 16);
	if(filesize < 1024)
		snprintf(total, 16, "%llu", filesize);
	else if(filesize >= 1024 && filesize < 1024*1024)
		snprintf(total, 16, "%.1fKB", (float)filesize/1024);
	else if(filesize >= 1024*1024 && filesize < 1024*1024*1024)
		snprintf(total, 16, "%.1fMB", (float)filesize/(1024*1024));


	char *bar = calloc(1, 128);
	if(nread < 1024)
		snprintf(bar, 128, "\r[%llu/%s] [", nread, total);
	else if(nread < 1024*1024)
		snprintf(bar, 128, "\r[%.1fKB/%s] [", (float)nread/1024, total);
	else if(nread < 1024*1024*1024)
		snprintf(bar, 128, "\r[%.1fMB/%s] [", (float)nread/(1024*1024), total);
	free(total);

	int i;
	for(i=0; i<cur; i++)
		snprintf(bar+strlen(bar), 128-strlen(bar)-i, "%s", "#");

	for(i=0; i<bar_len-cur-1; i++)
		snprintf(bar+strlen(bar), 128-strlen(bar)-i, "%s", "-");

	snprintf(bar+strlen(bar), 128-strlen(bar),
			"] [%.1f%%]%c", (float)nread/filesize*100,
			nread==filesize?'\n':' ');
	fprintf(stderr, "%s", bar);
	free(bar);
}























