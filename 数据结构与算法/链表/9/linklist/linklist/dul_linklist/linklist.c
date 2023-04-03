#include "linklist.h"
#include <stdlib.h>

struct node *head = NULL;
struct node *tail = NULL;

void create_list(unsigned int elem)
{
	struct node *p = (struct node *)malloc(sizeof(struct node));
	p->elem = elem;
	p->pre = NULL;   // 形成结构体成员
	p->next = NULL;

	//见图1:
	if(head == NULL)  //第一次新加入
		head = p;
	else
	{
		tail->next = p;
		p->pre = tail;   // 前驱点指向tail. 连起来
	}
	tail = p;
}

void insert_node(int pos, unsigned int elem)
{
	struct node *pre;
	pre = head;
	int i = 0;
	struct node *p = (struct node *)malloc(sizeof(struct node));
	// 见图2:
	if(pos == 0)   //头部插入
	{
		p->elem = elem;
		p->next = head;
		head->pre = p;
		p->pre = NULL;
		head = p;
	}
	else  
	{// 见图3:
		while(i < pos - 1)
		{
			pre = pre->next;
			i++;
		}

		p->elem = elem;
		p->pre = pre;
		p->next = pre->next;
		//重要:(新增)
		if(p->next != NULL)  //当前加入的p不是在尾节点后插入,因为是的话就不需要再连接这根线了
			pre->next->pre = p; 
		pre->next = p;  // 更新位置

		if(p->next == NULL)
			tail = p;
	}
}

void delete_node(int pos)
{
	struct node *pre, *p;
	pre = head;
	int i = 0;
	
	//见图4:
	if(pos == 0)
	{
		head = head->next;
		head->pre = NULL;  // 当前的前驱点的头变成NULL
		free(pre);    //删除原来的头
	}
	else
	{//见图5:
		while(i < pos - 1)
		{
			pre = pre->next;
			i++;
		}
	
		p = pre->next;
		pre->next = p->next;
		//重要:(新增)
		if(p->next != NULL)
			p->next->pre = pre;
		else//if(p->next == NULL)
			tail = pre;
		free(p);
	}
}

//下面都没做改动:
void print_linklist(void)
{
	struct node *p;
	
	for(p = head; p; p = p->next)
		printf("%5d", p->elem);

	printf("\n");
}

int search(unsigned int elem)
{
	struct node *p;

	for(p = head; p; p = p->next)
		if(p->elem == elem)
			return 1;
	return 0;
}

void reverse_print_linklist(void)
{
	struct node *p;

	for(p = tail; p; p = p->pre)
		printf("%5d", p->elem);
	printf("\n");
}
