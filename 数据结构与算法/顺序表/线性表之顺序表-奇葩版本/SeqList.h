//防止头文件重复包含
#ifndef _SEQLIST_H	//①
#define _SEQLIST_H	//②
#include<stdbool.h>
#define SEQLIST_INIT_SIZE 8	//顺序表的初始大小

typedef struct Student
{
	int number;
	char name[20];
}Student;
//typedef Student Data;

typedef struct Girl
{
	int age;
	char name[20];
	int height;
}Girl;
typedef Girl Data;


//ADT抽象数据类型
//typedef int Data;

typedef bool (*SEQLIST_FIND_CALLBACK)(void*, void*);

//定义顺序表结构体
typedef struct SeqList
{
	int capacity;		//容量
	int size;			//有效元素的个数
	Data* data;			 //定义数组指针	

	bool isHeap;		//顺序表是否申请再堆区
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
void seqList_insert(SeqList* list, int pos,Data val);

//尾删
void seqList_popback(SeqList* list);
//头删
void seqList_popfront(SeqList* list);
//删除指定的元素
void seqList_removeOne(SeqList* list,Data val, SEQLIST_FIND_CALLBACK cmp);
//指定位置删除
void seqList_removePos(SeqList* list, int pos);


//输出所有元素
void transform(SeqList* list, void (*fun)(void*));


//定义几个万金油函数
//判断顺序表是否为null
bool seqList_empty(SeqList* list);
bool seqList_full(SeqList* list);
bool seqList_size(SeqList* list);


int seqList_find(SeqList* list, Data val, SEQLIST_FIND_CALLBACK cmp);


#endif // !_SEQLIST_H	③

