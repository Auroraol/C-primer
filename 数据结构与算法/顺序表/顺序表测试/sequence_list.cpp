#include "sequence_list.h"
#include <malloc.h>
#include <assert.h>
#include <stdio.h>


void seqlist_init(Seqlist* list)
{
	list->capacity = SEQLIST_INIT_SIZE;
	list->size = 0;
	list->data = (Data*)calloc(list->capacity, sizeof(Data));
	if (!list->data)
	{
		assert(list->data);
	}
	list->isHeap = false;
}

Seqlist* seqList_create()
{
	Seqlist* list = (Seqlist*)calloc(1, sizeof(Seqlist));
	if (!list)
	{
		assert(list);
	}

	seqlist_init(list);
	list->isHeap = true;
	return list;
}

void seqList_destory(Seqlist* list)
{
	free(list->data);
	if (list->isHeap)
		free(list);
}

void seqList_pushback(Seqlist* list, Data val)
{
	if (seqlist_full(list) && !is_inc(list))
	{
		printf("seqlist is full,can't insert!\n");
		return;
	}

	list->data[list->size++] = val;
}

void seqList_pushfront(Seqlist* list, Data val)
{
	if (seqlist_full(list))
	{
		printf("seqlist is full,can't insert!\n");
		return;
	}

	for (int i = list->size; i > 0; i--)
	{
		list->data[i] = list->data[i - 1];
	}
	list->data[0] = val;
	list->size++;
}

void seqList_insert(Seqlist* list, int pos, Data val)
{
	if (seqlist_full(list))
	{
		printf("seqlist is full,can't insert!\n");
		return;
	}

	//判断pos是否合法
	if (pos < 0 || pos > list->size)
	{
		return;
	}

	for (int i = list->size; i > pos; i--)
	{
		list->data[i] = list->data[i - 1];
	}

	list->data[pos] = val;
	list->size++;
}

void seqList_popback(Seqlist* list)
{
	if (seqlist_empty(list))
		return;
	list->size--;
}

void seqList_popfront(Seqlist* list)
{
	if (seqlist_empty(list))
		return;
	int i = 1;
	for (int j = 0; j < list->size; j++)
	{
		list->data[j] = list->data[i++];
	}
	list->size--;
}

void seqList_removeOne(Seqlist* list, Data val)
{
	if (seqlist_empty(list))
		return;
	int i = 0;
	for (int j = 0; j < list->size; j++)
	{
		if (list->data[j] != val)
		{
			list->data[i++] = list->data[j];
		}
	}
	list->size--;
}

void seqList_removePos(Seqlist* list, int pos)
{
	if (seqlist_empty(list))
		return;
	for (int i = pos; i < list->size; i++)
	{
		list->data[i] = list->data[i + 1];
	}
	list->size--;
}

void seqlist_print(Seqlist* list)
{
	printf("容量:%d 大小:%d\n", list->capacity, list->size);
	if (seqlist_empty(list))
		return;
	for (int i = 0; i < list->size; i++)
	{
		printf("%d\n", list->data[i]);
	}
}

bool seqlist_empty(Seqlist* list)
{
	return list->size == 0;
}

bool seqlist_full(Seqlist* list)
{

	return list->size == list->capacity;
}

int seqlist_size(Seqlist* list)
{
	return list->size;
	return 0;
}

bool is_inc(Seqlist* list)
{
	if (seqlist_full(list))
	{

	}
	Data* newList = (Data*)realloc(list->data, (list->capacity + list->capacity * 2) * sizeof(Data));

	if (!newList)
	{
		return false;
	}

	list->data = newList;
	list->capacity += list->capacity * 2;
	return true;
}


