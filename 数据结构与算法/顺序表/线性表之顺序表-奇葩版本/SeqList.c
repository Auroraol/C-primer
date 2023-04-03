#include"SeqList.h"
#include<malloc.h>
#include<assert.h>
#include<stdio.h>
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

SeqList* seqList_create()
{
	//SeqList list;			//局部变量，函数结束自动释放，不安全了
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
	if(list->isHeap)
		free(list);
}

void seqList_pushback(SeqList* list, Data val)
{
	if (seqList_full(list))
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
	for (int i = list->size; i > pos; i--)
	{
		list->data[i] = list->data[i - 1];
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

void seqList_removeOne(SeqList* list, Data val, SEQLIST_FIND_CALLBACK cmp)
{
	if (seqList_empty(list))
	{
		return;
	}

	//删除
	seqList_removePos(list, seqList_find(list, val, cmp));
}

void seqList_removePos(SeqList* list, int pos)
{
	if (seqList_empty(list))
	{
		return;
	}
	assert(pos >= 0 && pos <= list->size);
	for (int k = pos; k < list->size - 1; k++)
	{
		list->data[k] = list->data[k + 1];
	}
	list->size--;
}

void transform(SeqList* list, void (*fun)(void*))
{
	for (int i = 0; i < list->size; i++)
	{
		fun(list->data + i);
	}
}

bool seqList_empty(SeqList* list)
{
	return list->size == 0;
}

bool seqList_full(SeqList* list)
{
	return list->size == list->capacity;
}

bool seqList_size(SeqList* list)
{
	return list->size;
}


int seqList_find(SeqList* list, Data val, SEQLIST_FIND_CALLBACK cmp)
{
	for (int i = 0; i < list->size; i++)
	{
		if (cmp(list->data + i, &val))
		{
			return i;
		}
	}
	return -1;
}
