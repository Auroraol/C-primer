#pragma once
#include <stdbool.h>

typedef int Data;

// 定义节点结构
typedef struct linkNode
{
	Data data;
	struct linkNode* next;

}linkNode;

// 创建链表
linkNode* createList();

// 创建节点
linkNode* createNode(Data val);

// 插入
//头插入
void pushfront(linkNode* list, Data val);
//尾插入
void push_back(linkNode* list, Data val);
//指定位置插入(下标)
void insert_pos(linkNode* list, int pos, Data val);
//指定位置插入(在指定元素之后)
void insert_item(linkNode* list, linkNode* item, Data val);
// 查找元素
linkNode* find(linkNode* list, Data data);


// 删除
//头删
void pop_front(linkNode* list);
//尾删
void pop_back(linkNode* list);
//指定元素删除
void removeOne(linkNode* list, Data val);
void removeA1l(linkNode* list, Data val);  // 删除所有val
bool isempty(linkNode* list);

// 遍历
void show_list(linkNode* list);