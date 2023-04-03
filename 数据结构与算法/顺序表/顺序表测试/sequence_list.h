#include <stdbool.h>
#ifndef SEQUENCE_LIST_H_
#define SEQUENCE_LIST_H_

/*
顺序表 :
*1, 用什么来存储数据 : 数组
*   1.1 静态数组：int arr[];
*   1.2 动态数组: int* parr = calloc(size, sizeof(type));
*2, 需要知道顺序表的容量:capacity
*3, 需要知道有效元素个数 : size
*/
#define SEQLIST_INIT_SIZE 8	//顺序表的初始大小

typedef void* Data;

typedef struct
{
	int capacity;
	int size;
	Data* data;

	bool isHeap;		//顺序表是否申请再堆区(这里使用seqList_create()就是堆区创建)
}Seqlist;

//初始化顺序表
void seqlist_init(Seqlist* list);

//创建一个顺序表
Seqlist* seqList_create();

//释放顺序表
void seqList_destory(Seqlist* list);


//尾插
void seqList_pushback(Seqlist* list, Data val);

// 头插
void seqList_pushfront(Seqlist* list, Data val);

//指定位置
void seqList_insert(Seqlist* list, int pos, Data val);

// 尾删
void seqList_popback(Seqlist* list);

//头删
void seqList_popfront(Seqlist* list);

//删除指定的元素
void seqList_removeOne(Seqlist* list, Data val);

//指定位置删除
void seqList_removePos(Seqlist* list, int pos);

//输出所有元素
void seqlist_print(Seqlist* list);

//判断顺序表是否为null
bool seqlist_empty(Seqlist* list);
bool seqlist_full(Seqlist* list);
int seqlist_size(Seqlist* list);


//扩容
bool is_inc(Seqlist* list);

#endif // !SEQUENCE_LIST_H_
