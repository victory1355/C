#include "auto.h"


int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Usage: xxx.elf  path\n");
		return -1;
	}
	//创建表头
	head_photo = create_file_head();
	head_music = create_file_head();
	
	//提取MP3和JPG图片,并建立两条链表
	tree_find_file(argv[1] ,head_photo, head_music);
	
	//遍历链表,使用回调函数，多次使用
	travel_list(head_photo);
	
	//进入自动模式
	auto_model(head_music, head_photo);
	
	
	return 0;
}