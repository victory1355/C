#include "data_struct.h"

int main()
{
	//srand(time(0));
	int number, i, delete_num, locate_num;
	
	printf("a test of datastructure.\n");
	Sqlist *list;
	//创建列表
    list = create_sqlist();
	
	for(i=0; i<50; i++)
	{
		number = rand()%100;
		//插入模块测试
		insert_sqlist(list, number);
	}
	//显示模块测试
	show_sqlist(list);
	printf("please input delete num\n");
	scanf("%d", &delete_num);
	
	
	//删除数据模块测试
	delete_sqlist(list, delete_num);
	show_sqlist(list);
	
	
	//查找数据模块测试
	printf("please input search_num\n");
	scanf("%d", &locate_num);
	int j = search_sqlist(list, locate_num);
	printf("the %d location is %d\n", locate_num, j);

	return 0;
}
