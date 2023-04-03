#include"SeqList.h"
#include<malloc.h>
#include<assert.h>
#include<stdio.h>

//扩容, 每次增加原来的两倍
bool inc(SeqList* list)
{
	//realloc 再原始的基础上增加
	SeqList* newList = realloc(list->data, (list->capacity + list->capacity * 2) * sizeof(Data));
	if (!newList)
	{
		return false;
	}
	list->data = newList;
	list->capacity += list->capacity * 2;
	return true;
}

// 普通
void seqList_init(SeqList* list)
{
	list->isHeap = false;
	list->size = 0;
	list->capacity = SEQLIST_INIT_SIZE;
	list->data = calloc(list->capacity, sizeof(Data));
	if (!list->data)
	{
		assert(list->data);	//断言list->data为真，如果不为真，则会中断程序
	}
}

// 动态
SeqList* seqList_create()
{
	SeqList* list = calloc(1, sizeof(SeqList));
	if (!list)
	{
		assert(list);
	}
	seqList_init(list);
	list->isHeap = true;
	return list;
}

void seqList_destory(SeqList* list)
{
	//先释放数组
	free(list->data);
	//再释放顺序表
	if (list->isHeap)
		free(list);
}

void seqList_pushback(SeqList* list, Data val)
{
	//list->size == list->capacity 并且扩容失败才是真正的满了
	if (seqList_full(list) && !inc(list))
	{
		printf("seqlist is full,can't insert!\n");
		return;
	}
	list->data[list->size++] = val;
}

void seqList_pushfront(SeqList* list, Data val)
{
	if (seqList_full(list))
	{
		printf("seqlist is full,can't insert!\n");
		return;
	}
	//先移动后面的元素，为新插入的元素腾出空间
	for (int i = list->size; i > 0; i--)
	{
		list->data[i] = list->data[i - 1];
	}
	//插入新数据
	list->data[0] = val;
	list->size++;
}

void seqList_insert(SeqList* list, int pos, Data val)
{
	if (seqList_full(list))
	{
		printf("seqlist is full,can't insert!\n");
		return;
	}
	//判断pos是否合法
	if (pos < 0 || pos > list->size)
	{
		pos = list->size;
	}
	//移动
	for (int i = list->size; i > pos; i--)   // 整体h
	{
		list->data[i] = list->data[i - 1];   // 数组的本质就是覆盖
	}
	list->data[pos] = val;
	list->size++;
}

void seqList_popback(SeqList* list)
{
	if (seqList_empty(list))
	{
		return;
	}
	list->size--;
}

void seqList_popfront(SeqList* list)
{
	if (seqList_empty(list))
	{
		return;
	}
	for (int i = 0; i < list->size - 1; i++)
	{
		list->data[i] = list->data[i + 1];
	}
	list->size--;
}

void seqList_removeOne(SeqList* list, Data val)
{
	if (seqList_empty(list))
	{
		return;
	}

	//删除
	seqList_removePos(list, seqList_find(list, val));
}

void seqList_removePos(SeqList* list, int pos)
{
	if (seqList_empty(list))
	{
		return;
	}
	assert(pos > 0 && pos <= list->size);

	for (int k = pos; k < list->size - 1; k++)
	{
		list->data[k] = list->data[k + 1];
	}
	list->size--;
}

void seqList_print(SeqList* list)
{
	if (seqList_empty(list))
	{
		printf("seqList is empty!\n");
		return;
	}
	for (int i = 0; i < list->size; i++)
	{
		printf("%d ", list->data[i]);
	}
	printf("\n");
}

bool seqList_empty(SeqList* list)
{
	return list->size == 0;
}

bool seqList_full(SeqList* list)
{
	return list->size == list->capacity;
}

int seqList_size(SeqList* list)
{
	return list->size;
}

int seqList_find(SeqList* list, Data val)
{
	for (int i = 0; i < list->size; i++)
	{
		if (list->data[i] == val)
		{
			return i;
		}
	}
	return -1;
}