//防止头文件重复包含
#ifndef _SEQLIST_H	//①
#define _SEQLIST_H	//②
#include<stdbool.h>

#define SEQLIST_INIT_SIZE 8	// 顺序表的初始大小

//ADT抽象数据类型
typedef int Data;

//定义顺序表结构体  --> 本质就是数组,核心是移动覆盖
typedef struct SeqList
{
	int capacity;		// 容量
	int size;			// 有效元素的个数
	Data* data;			// 定义数组指针	//因为要使用数组
	bool isHeap;		// 顺序表是否申请再堆区
}SeqList;

//初始化顺序表
void seqList_init(SeqList* list);
//创建一个顺序表
SeqList* seqList_create();
//释放顺序表
void seqList_destory(SeqList* list);
//尾插
void seqList_pushback(SeqList* list, Data val);
//头插
void seqList_pushfront(SeqList* list, Data val);
//指定姿势
void seqList_insert(SeqList* list, int pos, Data val);


// 删除的本质就是覆盖
//尾删
void seqList_popback(SeqList* list);
//头删
void seqList_popfront(SeqList* list);
//删除指定的元素
void seqList_removeOne(SeqList* list, Data val);
//指定位置删除
void seqList_removePos(SeqList* list, int pos);


//输出所有元素
void seqList_print(SeqList* list);


//定义几个万金油函数
//判断顺序表是否为null
bool seqList_empty(SeqList* list);
bool seqList_full(SeqList* list);
int seqList_size(SeqList* list);
int seqList_find(SeqList* list, Data val);


#endif // !_SEQLIST_H	③