
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

//ȥ��data���ݺ����ں�����
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
	//��ʼ������
	s1->data = 88;
	s1->list.prev = &(s1->list);
	s1->list.next = &(s1->list);
	
	
	SNode *s2 = (SNode *)malloc(sizeof(SNode));
	//��ʼ������
	s2->data = 100;
	s2->list.prev = &(s2->list);
	s2->list.next = &(s2->list);
	
	struct demo_list *head = &s1->list;
	struct demo_list *node = &s2->list;
	
	//��node�ڵ����head�ڵ��
	node->next = head->next;
	node->prev = head;
	head->next->prev = node;
	head->next = node;
	
	//���濪ʼ���ԣ�ͨ��s1�ҵ���������
	struct demo_list *lptr = &s1->list;
	lptr = lptr->next;		//����ͷ�ڵ�
	
	printf("%p   %p     offset = %d\n", &(s1->list), s1);
	
	unsigned int offset =  (s1->list)- s1;
	
	printf("%p   %p     offset = %d\n", &(s1->list), s1, offset);
	
	SNode *s = (SNode *)((char *)lptr - offset);     //��ȡ�ڶ����ṹ��ĵ�ַ
	
	//��ӡ��ṹ�������
	printf("second data: %d \n", s->data);

	return 0;
}
















