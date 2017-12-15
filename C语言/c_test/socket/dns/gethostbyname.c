#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <netinet/in.h>
#include <strings.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <pthread.h>

#include "cJSON.h"

void reciver_data(int fd);
int send_query(int fd);
void *routine(void *);


int main(void)
{
	struct hostent * p = gethostbyname("jisutianqi.market.alicloudapi.com");
	if(p == NULL)
	{
		perror("gethostbyname");
		return -1;
	}
	
	/*printf("[%d]\n", __LINE__);
	printf("官方名称：%s\n", p->h_name);
	
	printf("别名：\n");
	printf("--------\n");
	int i;
	for(i=0; p->h_aliases[i]!=NULL; i++)
	{
		printf("%s\n", p->h_aliases[i]);
	}

	printf("\n地址类型：");
	switch(p->h_addrtype)
	{
	case AF_INET:
		printf("IPv4\n");
		break;
	case AF_INET6:
		printf("IPv6\n");
	}

	printf("地址长度：%d\n", p->h_length);

	printf("\nIP地址列表：\n");
	printf("--------\n");
	struct in_addr **list = (struct in_addr **)p->h_addr_list;

	printf("%d\n", sizeof( *(p->h_addr_list[0] )));
	printf("%d\n", sizeof( *(    list      [0] )));
	
	for(i=0; p->h_addr_list[i]!=NULL; i++)
	{
		printf("%s\n", inet_ntoa( *list[i]) );
	}*/
	
	//while(1);
	//==================================================
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if( fd == -1)
	{
		perror("socket");
		return -1;
	}

	struct sockaddr_in srvaddr;
	bzero(&srvaddr, sizeof(srvaddr));

	srvaddr.sin_family = AF_INET;
	srvaddr.sin_port = htons(80);
	struct in_addr **list = (struct in_addr **)p->h_addr_list;
	//printf("%s\n", inet_ntoa( *list[0]) );
	srvaddr.sin_addr = *list[0];
	
	//负责获取城市信息
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	
	
	pthread_t tid;
	pthread_create(&tid, &attr, routine, NULL);
	
	while(1);
	
	if( connect(fd, (struct sockaddr *)&srvaddr, sizeof(srvaddr)) == -1)
	{
		perror("connect");
		return -1;
	}
	while(1)
	{
		//发送请求
		if( send_query(fd) == 0)
		{
			//接受数据
			reciver_data(fd);
		}
		else
		{
			break;
		}
		//sleep();
	}
		
	
	return 0;
}

void *routine(void *arg)
{
	struct hostent * p = gethostbyname("jisutianqi.market.alicloudapi.com");
	if(p == NULL)
	{
		perror("gethostbyname");
		return (void *)-1;
	}
	
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if( fd == -1)
	{
		perror("socket");
		return (void *)-1;
	}

	struct sockaddr_in srvaddr;
	bzero(&srvaddr, sizeof(srvaddr));
	struct in_addr **list = (struct in_addr **)p->h_addr_list;
	
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_port = htons(80);
	printf("%s\n", inet_ntoa( *list[0]) );
	srvaddr.sin_addr = *list[0];
	
	if( connect(fd, (struct sockaddr *)&srvaddr, sizeof(srvaddr)) == -1)
	{
		perror("connect");
		return (void *)-1;
	}
	//char buf[10000000];
	char *buf = malloc(sizeof(char)*1000);
	bzero(buf, sizeof buf);
	
	sprintf(buf,"GET /weather/city? HTTP/1.1\r\n"
	"Host:jisutianqi.market.alicloudapi.com\r\n"
	"Authorization:APPCODE 43a3a5e33894497bb332921e8b97a672\r\n\r\n");
	
//	printf("%s\n", buf);
	if( write(fd, buf, strlen(buf)) != -1)
	{
		printf("%s\n", buf);
	}
	//================================================================================
	int readn;
	//char buf[10000];
	bzero(buf, sizeof buf);
	char buf1[800];
	int count = 0;
	
	while(1)
	{
		
		while((readn = read(fd, buf1, sizeof buf1)) == -1 && errno ==EINTR);
		if(readn == 0)
		{
			//printf("[%d]\n", __LINE__);
			break;
		}
		else if(readn == -1)
		{
			perror("read");
			return (void *)0;
		}
		else
			printf("%s", buf1);
		count++;
		if(count == 1000000);
		 break;
		bzero(buf1, sizeof buf1);
	}
	printf("\n");
	printf("[%d]\n", __LINE__);
	//printf("%s\n", buf1);
	
	//去掉HTTP头
	/*char *p1= strstr(buf, "\r\n\r\n");
	p1 = p1+4;
	printf("p1 = %s\n", p1);*/
	
}


int send_query(int fd)
{
	char buf[300];
	bzero(buf, sizeof(buf));
	char city_name[50];
	bzero(city_name, sizeof city_name);
	
	snprintf(buf, sizeof(buf), "GET /weather/query?"
							   "city=%s "
							   "HTTP/1.1\r\n"
							   "Host:jisutianqi.market.alicloudapi.com\r\n"
							   "Authorization:APPCODE 43a3a5e33894497bb332921e8b97a672\r\n\r\n", city_name);
	
	
	if( write(fd, buf, strlen(buf)) != -1)
	{
		printf("%s\n", buf);
	}
	
	return 0;
	
}


void reciver_data(int fd)
{
	//char ch;
	int readn;
	char buf[10000];
	bzero(buf, sizeof buf);
	
	while(1)
	{
		while((readn = read(fd, buf, sizeof buf)) == -1 && errno ==EINTR);
		if(readn == 0)
		{
			printf("[%d]\n", __LINE__);
			break;
		}
		else if(readn == -1)
		{
			perror("read");
			return ;
		}
	}
	//printf("%s\n", buf);
	
	//去掉HTTP头
	char *p = strstr(buf, "\r\n\r\n");
	p = p+4;
	//printf("p = %s\n", p);
	//cJSON *root = cJSON_Parse(p);
	//cJSON *status = cJSON_GetObjectItem(root, "status");
	//printf("status:%s\n", status->valuestring);
	/*cJSON *root = cJSON_Parse(p);
	cJSON *result = cJSON_GetObjectItem(root, "result");
	//printf("[%d]\n", __LINE__);
	
	cJSON *city   = cJSON_GetObjectItem(result, "city");
	cJSON *weather= cJSON_GetObjectItem(result, "weather");
	cJSON *week= cJSON_GetObjectItem(result, "week");
	cJSON *date= cJSON_GetObjectItem(result, "date");
	cJSON *temp= cJSON_GetObjectItem(result, "temp");

	//printf("[%d]\n", __LINE__);
	printf("%s %s %s %s %s\n", 	 city->valuestring
								,weather->valuestring
								,week->valuestring
								,date->valuestring
								,temp->valuestring);
	//printf("[%d]\n", __LINE__);
	
	//对csjon数组的操作
	cJSON *index = cJSON_GetObjectItem(result, "index");

	int array_size = cJSON_GetArraySize(index);
	int i;
	for(i=0; i<array_size; i++)
	{
		cJSON *item = cJSON_GetArrayItem(index, i);

		cJSON *iname = cJSON_GetObjectItem(item, "iname");
		printf("%s\n", iname->valuestring);
		//cJSON *ivalue= cJSON_GetObjectItem(item, "ivalue");
		//printf("%s\n", ivalue->valuestring);
		//cJSON *detail= cJSON_GetObjectItem(item, "detail");
		//printf("%s\n", detail->valuestring);
	}
	
	
	cJSON *aqi = cJSON_GetObjectItem(result, "aqi");
	cJSON *primarypollutant = cJSON_GetObjectItem(aqi, "primarypollutant");
	printf("%s", primarypollutant->valuestring);
	
	index = cJSON_GetObjectItem(result, "daily");
	array_size = cJSON_GetArraySize(index);
	
	for(i=0; i<array_size; i++)
	{
		cJSON *item1 = cJSON_GetArrayItem(index, i);
		cJSON *week_daily = cJSON_GetObjectItem(item1, "week");
		printf("daily-->time:%s\n", week_daily->valuestring);
	}
	
	index = cJSON_GetObjectItem(result, "hourly");
	array_size = cJSON_GetArraySize(index);
	
	for(i=0; i<array_size; i++)
	{
		cJSON *item2 = cJSON_GetArrayItem(index, i);
		cJSON *time = cJSON_GetObjectItem(item2, "time");
		printf("hourly-->time:%s\n", time->valuestring);
	}
	*/
	//sleep(10);
	
	printf("\n");
}




























