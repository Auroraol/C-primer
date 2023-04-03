#include<stdio.h>
#include"SeqList.h"
#include<string.h>
/*
* 数据结构:存储数据的结构 线性表 树 图
* 线性表:一个节点只有一个前驱和一个后继
*	1,顺序表:内存是连续的		数组
*	2,链表:内存是不连续的		结构体 + 指针
*	3,访问受限的线性表:栈 队列
* 
* 顺序表:
*	1,用什么来存储数据:数组
*		1.1 静态数组：int arr[];
*		1.2 动态数组: int *parr = calloc(size,sizeof(type));
*	2,需要知道顺序表的容量:capacity
*	3,需要知道有效元素个数:size
*/

void stu_print(Student* stu)
{
	printf("%d %s\n", stu->number, stu->name);
}

bool stu_cmp(Student* left, Student* right)
{
	if (left->number == right->number)
	{
		return true;
	}
	return false;
}

void girl_print(Girl* girl)
{
	printf("%d %s %d\n", girl->age, girl->name, girl->height);
}

bool girl_cmp(Girl* left, Girl* right)
{
	if (strcmp(left->name, right->name) == 0)
	{
		return true;
	}
	return false;
}




//int main1()
//{
//	SeqList list;
//	seqList_init(&list);
//
//	char name[20] = { 0 };
//	for (int i = 0; i < 3; i++)
//	{
//		sprintf(name, "maye_%d", i);
//		Student stu = { 100 + i};
//		strcpy(stu.name, name);
//		seqList_pushback(&list, stu);
//	}
//
//	transform(&list,stu_print);
//
//
//	//seqList_popback(&list);
//	Student stu = { .number = 100 };
//	seqList_removeOne(&list, stu,stu_cmp);
//
//	printf("\n");
//	transform(&list, stu_print);
//
//
//	seqList_destory(&list);
//	return 0;
//}

int main()
{
	SeqList list;
	seqList_init(&list);

	Girl girls[3] = { {18,"月月",170},{18,"盼盼",171},{20,"皮皮",168} };
	for (int i = 0; i < 3; i++)
	{
		seqList_pushback(&list,girls[i]);
	}

	transform(&list, girl_print);

	seqList_removeOne(&list, girls[0], girl_cmp);


	transform(&list, girl_print);


	seqList_destory(&list);
	return 0;
}