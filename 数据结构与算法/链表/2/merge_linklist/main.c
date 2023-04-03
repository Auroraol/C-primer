#include <stdio.h>
#include "linkedlist.h"

int main(void)
{ 
    // 创建两个结构体的指针头
    struct node *head1 = NULL;  
    struct node *head2 = NULL;
    struct node *p = NULL;
    struct node *q = NULL;
    
    //创建两个链表:
    create_list(1);
    create_list(9);
    create_list(13);
    create_list(27);
    head1 = head; //让head1指向默认的头
    print_linklist(head1);  //显示

    head = NULL; //先复制头空指针在进行创建
    create_list(3);
    create_list(5);
    create_list(14);
    create_list(81);
    create_list(95);
    create_list(99);
    head2 = head;
    print_linklist(head2);
	
    
    //合并链表,(有序的排列)
    head = NULL;
    p = head1;
    q = head2;
     
    while (p && q)   // 只要 q , p 两个链表任意一个取完了,就退出
    {
        //第一次,找到链表头应该是什么
        if (p->elem <= q->elem)
        {
            if (head == NULL)  // 头是不变的
                head = p;      // 头是不变的
            else
                tail->next = p; //尾节点的下一个尾节点 = 新来的
            tail = p;  //新来的全部内容.  尾,用来指向追加的尾(可以理解成next的前身)
            p = p->next;  //更新位置 , p->next指向的下一个位置   
        }
        else
        {
            if (head == NULL)
                head = q;
            else
                tail->next = q;   
            tail = q;
            q = q->next;   
        }
    }
    //有没比较的追加剩下的
    tail->next = p == NULL ? p: q;  //p为空就取q // tail->next表示后面的内容
    print_linklist(head);  //合并之后的
    return 0;
}
