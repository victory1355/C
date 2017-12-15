#include <stdio.h>

int main(void)
{
	int fd = socket(...);

	// 使能广播功能
	int on = 1;
	setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));

	// 设置接收数据缓冲区大小
	int size = 4096;
	setsockopt(fd, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size));

	// 设置读就绪超时
	struct timeval tv = {10, 0};
	setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

}
