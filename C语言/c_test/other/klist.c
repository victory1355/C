#include <stdio.h>
#include <stdlib.h>

#include "list.h"


typedef struct snode
{
	struct list_head list;
	int data;
	

}SNode;


int main()
{
	SNode *s1 = (SNode *)malloc(sizeof(SNode));
	SNode *s2 = (SNode *)malloc(sizeof(SNode));
	
	
/*#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
struct list_head name = LIST_HEAD_INIT(name)

static inline void INIT_LIST_HEAD(struct list_head *list)
{
	list->next = list;
	list->prev = list;
}*/

	//初始化内容
	s1->data = 88;
	INIT_LIST_HEAD(&s1->list);
	
	s2->data = 100;
	INIT_LIST_HEAD(&s2->list);
	
	
	
/*static inline void __list_add(struct list_head *new, // 要插入的节点
				struct list_head *prev,// 前节点 before
				struct list_head *next) // 后节点 after
{
	next->prev = new; // 后节点的上家为new
	new->next = next;
	new->prev = prev;
	prev->next = new;
}
static inline void list_add(struct list_head *new, struct list_head *head)
{
	__list_add(new, head, head->next);
}*/

	//添加新节点
	list_add(&s2->list, &s1->list);
	
	struct list_head *l = &s1->list;
	l = l->next;		//跳过头节点
	
	
/*	#define container_of(ptr, type, member) ({			\
       const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
      (type *)( (char *)__mptr - offsetof(type,member) );})
*/
  
	SNode *s = container_of(l, SNode, list);
	printf("second data: %d \n", s->data);

	return 0;
}

