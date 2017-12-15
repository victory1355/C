
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

//去除data内容后变成内核链表
struct demo_list 
{
	struct demo_list *prev;
	struct demo_list *next;
};

typedef struct snode
{
	struct demo_list list;
	int data;
}SNode;


int main()
{
	SNode *s1 = (SNode *)malloc(sizeof(SNode));
	//初始化内容
	s1->data = 88;
	s1->list.prev = &(s1->list);
	s1->list.next = &(s1->list);
	
	
	SNode *s2 = (SNode *)malloc(sizeof(SNode));
	//初始化内容
	s2->data = 100;
	s2->list.prev = &(s2->list);
	s2->list.next = &(s2->list);
	
	struct demo_list *head = &s1->list;
	struct demo_list *node = &s2->list;
	
	//将node节点插入head节点后
	node->next = head->next;
	node->prev = head;
	head->next->prev = node;
	head->next = node;
	
	//下面开始测试：通过s1找到所有内容
	struct demo_list *lptr = &s1->list;
	lptr = lptr->next;		//跳过头节点
	
	printf("%p   %p     offset = %d\n", &(s1->list), s1);
	
	unsigned int offset =  (s1->list)- s1;
	
	printf("%p   %p     offset = %d\n", &(s1->list), s1, offset);
	
	SNode *s = (SNode *)((char *)lptr - offset);     //获取第二个结构体的地址
	
	//打印大结构体的数据
	printf("second data: %d \n", s->data);

	return 0;
}
















