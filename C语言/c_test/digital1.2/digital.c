#include "digital.h"

int main(int argc, char *argv[])
{
	//测试代码
	//创建头节点
	head_photo = create_file_head();
	if(head_photo == NULL)
	{
		//perror("create fail");
		return -1;
	}
	head_music = create_file_head();
	if(head_music == NULL)
	{
		//perror("create fail");
		return -1;
	}
	flag_usb = 10;
	//初始化终端
	init_term();
	
	int ret;
	
	//控制线程
	ret = pthread_cond_init(&cond, NULL);
	if(ret != 0)
	{
		//perror("cond init fail\n");
		return -1;
	}
	ret = pthread_mutex_init(&mutex, NULL);
	if(ret != 0)
	{
		//perror("cond init fail\n");
		return -1;
	}
	
	pthread_t usb_thread;
	pthread_t user_thread;
	pthread_t print_thread;
	
	//负责不断检测U盘和挂载U盘
	ret = pthread_create(&usb_thread, NULL, found_usb_thread, NULL);
	if(ret != 0)
	{
		//perror("create fail\n");
		return -1;
	}
	//负责用户交互
	ret = pthread_create(&user_thread, NULL, user_control_thread, NULL);
	if(ret != 0)
	{
		//perror("create fail\n");
		return -1;
	}
	//负责数据的打印和刷新
	ret = pthread_create(&print_thread, NULL, print_list_thread, NULL);
	if(ret != 0)
	{
		//perror("create fail\n");
		return -1;
	}
	
	//主线程负责回收
	pthread_join(usb_thread, NULL);
	pthread_join(user_thread, NULL);
	pthread_join(print_thread, NULL);
	
	//主线程退出
	//printf("exit....\n");
	pthread_exit(NULL);
	
}






















