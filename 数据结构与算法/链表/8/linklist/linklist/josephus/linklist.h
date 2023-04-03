#ifndef LINKLIST_H__
#define LINKLIST_H__

#include <stdio.h>

extern struct node *head;
extern struct node *tail;

struct node
{
	unsigned int elem;
	struct node *next;
};

void create_list(unsigned int elem);
void insert_node(int pos, unsigned int elem);
void delete_node(int pos);
void print_linklist(void);
int search(unsigned int elem);

#endif

