#include "linkedlist.h"
#include <stdlib.h> // c语言中 malloc的函数包含的头文件   //在c++中要使用 rand() 函数必须,在程序中包含 <cstdlib> 头文件
#include<stdio.h>

// struct node *head = NULL; //头指针  // 结点的插入方法一般有：头插法；尾插法(掌握)
// struct node *tail = NULL;

// void create_list(unsigned char elem)
// {
//     struct node *p = (struct node *)malloc(sizeof(struct node)); // 开辟内存空间 malloc返回void的类型 通过(struct node *)进行强制类型转换指针
//     p->elem = elem;                                              // 数据域
//     p->next = NULL;

//     // 链接节点
//     if (head == NULL) //第一次插入第一个节点时 //头节点必须指向第一个节点
//         head = p;
//     else // 再插入其他的新来节点   // 此时的尾节点的指针域应该切换到新来的
//         tail->next = p;
//     tail = p; // 更新
// }
struct node *head = NULL;
struct node *tail = NULL;

void create_list(unsigned char elem)
{
	struct node *p = (struct node *)malloc(sizeof(struct node));
	p->elem = elem;
	p->next = NULL;

	if(head == NULL)
		head = p;
	else
		tail->next = p;

	tail = p;
}



//插入:
void insert_node(int pos, char elem) // pos 表示位置 前驱点   elem表示要处理的数据
{
    struct node *pre; // 前驱点
    pre = head;       // 初始值(都要从头指针开始)

    int i;
    struct node *p = (struct node *)malloc(sizeof(struct node)); //  开辟内存空间

    if (pos == 0) // 没有前驱点的情况,在头节点时操作
    {
        p->elem = elem;
        p->next = head;
        head = p; // 更新头
    }
    else
    {
        //(1)有前驱点/不是头节点的情况:
        while (i < pos - 1) //不确定循环次数用while  // 循环次数比要找的节点位置少1(找到前驱点)
        {
            pre = pre->next;   //找前驱点的过程就是前驱点的移动移动//更新per的位置
            i++;
        }
        //新开辟的节点:
        p->elem = elem;
        p->next = pre->next; // 新的节点指针域 指向前驱点所在的指针域(原来位置节点的)
        pre->next = p;       // 重新更新前驱域的指针域.

        if (p->next == NULL) //在末尾插入,到达末尾了;没节点连接了
            tail = p;  //直接插入
    }
}

//删除:
void delete_node(int pos)
{
    struct node *pre, *p;  //*p 接受要删除节点
    pre = head; 
    int i;
 
    if (pos == 0)
    {
        head = head->next;
        free(pre);    //删除头节点(因为pre指向头节点
    }
    else
        {while (i < pos - 1)
        {
            pre = pre->next;
            i++;
        }

        p = pre->next;  //当前要删除的节点
        pre->next = p->next;   //   p->next表示删除节点的下一个节点, 让pre-next直接连接删除节点的下一个节点就能达到目的
        if (p->next == NULL)
            tail = pre;   // 删除尾节点,前驱点就成为末尾

        free(p);  //删除
    }
}

//输出链表
void print_linklist(void)
{
    struct node *p;  //定义一个结构体指针p
    
    for (p = head; p; p = p->next)   // p表示不为空就进行  // 注意更新条件
        printf("%c",p->elem);
    printf("\n");  //全部循环完换行
    
}


//查找:
int search( unsigned char elem)
{
    struct node *p;

    for (p = head; p; p = p->next)
        if(p->elem == elem)
            return 1;
    return 0;
}