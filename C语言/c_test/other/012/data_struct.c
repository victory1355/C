#include "data_struct.h"

//具体实现的函数


//创建一个学生表
Sqlist *create_sqlist(void)
{
	Sqlist *list = malloc(sizeof(Sqlist));
	if(list == NULL)
	{
		perror("create_sqlist failed\n");
		return NULL;
	}
	list->lenght = -1;
	
	return list;
}


//尾插法插入数据
bool insert_sqlist(Sqlist *list, int data)
{
		if(list == NULL)
				return false;
		if(list->lenght == SIZE-1)
				return false;
		
		list->lenght++;
		list->data[list->lenght] = data;
		
		return true;
}



//删除数据
bool delete_sqlist(Sqlist *list, int data)
{
	if(list == NULL)
		return false;
	int i;
	for(i=0; i<=list->lenght; i++)
	{
		if(list->data[i] == data)
			break;
	}
	if(i > list->lenght)
			return false;
	for(;i<list->lenght; i++)
		list->data[i] = list->data[i+1];
	//长度-1
	list->lenght--;
		
	return true;
}

//显示数据
void show_sqlist(Sqlist *list)
{
	if(list == NULL || list->lenght == -1)
		return ;
	int  i;
	printf("-----------student information table-----------\n");
	for(i=0; i<=list->lenght; i++)
	{
		printf("%-2d  ",list->data[i]);
		if(i%9 == 0)
			printf("\n");
	}
	
	printf("\n----------------------end---------------------\n");
		
	
	printf("\n");
}

//查找数据
int search_sqlist(Sqlist *list, int data)
{
	if(list == NULL)
		return -1;
	int i;
	//查找数据
	for(i=0; i<=list->lenght; i++)
		if(list->data[i] == data)
			return i;
		
	if(i > list->lenght)
			return ;
	
}


//任意位置插入数据
bool insert_pos_sqlist(Sqlist *list, int data, int pos)
{
	if(list == NULL || list->lenght == SIZE-1)
			return false;
	
	if(pos > SIZE-1)
	{
		printf("position not exist\n");
		return false;
	}
	int  i;
	for(i=list->lenght; i>pos; i--)
		list->data[i] = list->data[i-1];
	
	list->lenght++;
	
	return true;
	
}










































