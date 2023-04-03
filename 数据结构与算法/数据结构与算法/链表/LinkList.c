#include "LinkList.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>

linkNode* createList()
{
	linkNode* head = malloc(sizeof(linkNode));
	if (!head)
	{
		printf("head malloc failed");
		return NULL;
	}
	memset(head, 0, sizeof(linkNode));
	return head;
}

linkNode* createNode(Data val)
{
	linkNode* newNode = malloc(sizeof(linkNode));
	if (!newNode)
	{
		printf("newNode malloc falied"); return NULL;
	}
	newNode->data = val;
	newNode->next = NULL;
	return newNode;
}

void pushfront(linkNode* list, Data val)
{
	linkNode* newNode = createNode(val);
	newNode->next = list->next;
	list->next = newNode;
}

void push_back(linkNode* list, Data val)
{
	linkNode* newNode = createNode(val);
	linkNode* cur = list;
	while (cur->next)
	{
		cur = cur->next;
	}
	cur->next = newNode;
}

void insert_pos(linkNode* list, int pos, Data val)
{
	linkNode* cur = list;
	linkNode* newNode = createNode(val);

	while (pos-- && cur->next)
	{
		cur = cur->next;
	}

	newNode->next = cur->next;
	cur->next = newNode;
}

void insert_item(linkNode* list, linkNode* item, Data val)
{
	linkNode* newNode = createNode(val);
	newNode->next = item->next;
	item->next = newNode;
}

linkNode* find(linkNode* list, Data val)
{
	linkNode* curNode = list->next; while (curNode)
	{

		if (curNode->data == val)
		{
			return curNode;
		}
		curNode = curNode->next;
	}
	return NULL;

}

void pop_front(linkNode* list)
{
	linkNode* temp = list->next;
	list->next = list->next->next;
	free(temp);
}

void pop_back(linkNode* list)
{
	linkNode* cur = list;
	linkNode* temp = NULL;
	while (cur->next && cur->next->next)
	{

		cur = cur->next;
	}
	free(cur->next);
	cur->next = NULL;
}

void removeOne(linkNode* list, Data val)
{
	if (isempty(list))
		return;
	linkNode* cur = list;
	while (cur->next)
	{
		if (cur->next->data == val)
		{
			break;
		}
		cur = cur->next;
	}
	//É¾³ý
	if (cur->next)
	{
		linkNode* temp = cur->next;
		cur->next = cur->next->next;
		free(temp);
	}
}

void removeA1l(linkNode* list, Data val)
{
	if (isempty(list))
		return;
	linkNode* cur = list;
	linkNode* temp = NULL;
	while (cur->next)
	{
		if (cur->next->data == val)
		{
			temp = cur->next;
			cur->next = temp->next;
			free(temp);
			temp = NULL;
		}
		else
		{
			cur = cur->next;
		}

	}
}

bool isempty(linkNode* list)
{
	return list->next == NULL;
}

void show_list(linkNode* list)
{
	linkNode* cur = list->next;
	while (cur)
	{
		printf("%d ", cur->data);
		cur = cur->next;
	}
	printf("\n");
}

