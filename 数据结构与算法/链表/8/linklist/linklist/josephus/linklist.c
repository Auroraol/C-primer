#include "linklist.h"
#include <stdlib.h>

struct node *head = NULL;
struct node *tail = NULL;

void create_list(unsigned int elem)
{
	struct node *p = (struct node *)malloc(sizeof(struct node));
	p->elem = elem;
	p->next = NULL;

	if(head == NULL)
		head = p;
	else
		tail->next = p;

	tail = p;
	tail->next = head;
}

void insert_node(int pos, unsigned int elem)
{
	struct node *pre;
	pre = head;
	int i = 0;
	struct node *p = (struct node *)malloc(sizeof(struct node));

	if(pos == 0)
	{
		p->elem = elem;
		p->next = head;
		head = p;
		tail->next = head;
	}
	else
	{
		while(i < pos - 1)
		{
			pre = pre->next;
			i++;
		}

		p->elem = elem;
		p->next = pre->next;
		pre->next = p;

		if(p->next == head)
			tail = p;
	}
}

void delete_node(int pos)
{
	struct node *pre, *p;
	pre = head;
	int i = 0;

	if(pos == 0)
	{
		head = head->next;
		free(pre);
		tail->next = head;
	}
	else
	{
		while(i < pos - 1)
		{
			pre = pre->next;
			i++;
		}
	
		p = pre->next;
		pre->next = p->next;
		if(p->next == head)
			tail = pre;
		free(p);
	}
}

void print_linklist(void)
{
	struct node *p;
	p = head;
	
//	for(p = head; p != head; p = p->next)
//		printf("%d", p->elem);

	do{
		printf("%5d", p->elem);
		p = p->next;
	}while(p != head);

	printf("\n");
}

int search(unsigned int elem)
{
	struct node *p;
	p = head;

//	for(p = head; p; p = p->next)
//		if(p->elem == elem)
//			return 1;
	do{
		if(p->elem == elem)
			return 1;
		p = p->next;
	}while(p != head);

	return 0;
}
