#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>


typedef void* variant;

typedef struct SeqList
{
	int capacity;   //
	int size;
	variant* data;
}SeqList;

#define SeqList_Init(plist)\
(plist)->size = 0;\
(plist)->capacity = 8; \
(plist)->data = calloc((plist)->capacity,sizeof(variant));\
if(!(plist)->data)\
printf("内存申请失败\n");


#define SeqList_PushBack(plist,val)\
if((plist)->size == (plist)->capacity)\
	printf("seqlist is full,can't insert\n");\
(plist)->data[(plist)->size++] = (val);


#define SeqList_Destory(plist)\
free((plist)->data);


#define SeqList_Clear(plist)\
(plist)->size = 0;


#define foreach(variable,plist)\
for (int _i = 0,_cnt = 0; _i < (plist)->size; _i++,_cnt = 0)\
	for (variable = (plist)->data[_i]; _cnt < 1; _cnt++)


#define Break _i=999999;break;


#define Continue break;

typedef struct LinkMan
{
	char name[20];
	unsigned long long tel;
}LinkMan;

//创建联系人
LinkMan* createLinkMan(const char* name, unsigned long long tel)
{
	LinkMan* man = calloc(1, sizeof(LinkMan));
	if (!man)
	{
		return NULL;
	}
	strcpy(man->name, name);
	man->tel = tel;
	return man;
}

//输出联系人
void linkMan_print(LinkMan* man)
{
	printf("%-20s %llu\n", man->name, man->tel);
}

int main()
{
	SeqList list;
	SeqList_Init(&list);

	SeqList_PushBack(&list, createLinkMan("祈盼", 123456789));
	SeqList_PushBack(&list, createLinkMan("顽石", 17363691462));
	SeqList_PushBack(&list, createLinkMan("mercedes", 4654564));
	SeqList_PushBack(&list, createLinkMan("pertrichor", 3423546));
	SeqList_PushBack(&list, createLinkMan("皮皮", 7878788787));

	//把皮皮的电话修改为5280620
	foreach(LinkMan * man, &list)
	{
		if (strcmp(man->name, "顽石") == 0)
		{
			man->tel = 5280620;
			Break;
		}
		printf("for\n");
	}

	//遍历打印
	foreach(LinkMan * man, &list)
	{
		linkMan_print(man);
	}

	//释放内存
	foreach(LinkMan * man, &list)
	{
		free(man);
	}
	return 0;
}


