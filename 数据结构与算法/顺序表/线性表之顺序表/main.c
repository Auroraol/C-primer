#include<stdio.h>
#include"SeqList.h"
/*
* 数据结构:存储数据的结构 线性表 树 图
* 线性表:一个节点只有一个前驱和一个后继
*	1,顺序表:内存是连续的		数组
*	2,链表:内存是不连续的		结构体 + 指针
*	3,访问受限的线性表: 栈 队列
*
* 顺序表:
*	1,用什么来存储数据:数组
*		1.1 静态数组：int arr[];
*		1.2 动态数组: int *parr = calloc(size,sizeof(type));
*	2,需要知道顺序表的容量:capacity
*	3,需要知道有效元素个数:size
*/

int main()
{
	SeqList list = {0};
	seqList_init(&list);

	//seqList_destory(&list);	//释放栈区的内存，是不合法的
	//SeqList* plist = seqList_create();
	//seqList_destory(plist);	//只能释放堆区的内存

	for (int i = 0; i < 100; i++)
	{
		seqList_pushback(&list, i + 1);
	}

	//for (int i = 0; i < 10; i++)
	//{
	//	seqList_pushfront(&list, 8 +i);
	//}

	seqList_insert(&list, 2, 666);

	seqList_print(&list);

	printf("\n%d %d\n", seqList_size(&list), list.capacity);

	//seqList_popback(&list);
	//seqList_popfront(&list);
	//seqList_removeOne(&list, 666);
	//seqList_removePos(&list, 20);

	//seqList_print(&list);


	return 0;
}