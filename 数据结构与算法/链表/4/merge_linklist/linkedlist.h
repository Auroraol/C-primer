#ifndef LINKEDLIST_H_
#define LINKEDLSIT_H_

extern struct node *head;  // 当链接器在一个全局变量声明前看到extern关键字，
//它会尝试在其他文件中寻找这个变量的定义。这里强调全局且非常量的原因是，全局非常量的变量默认是外部链接的。
extern struct node *tail;

struct node
{
    unsigned int elem;
    struct node *next;
};

int search( unsigned int elem);
void print_linklist(struct node *linklist_head);
void delete_node(int pos);
void insert_node(int pos, int elem);// pos 表示位置 前驱点   elem表示要处理的数据
void create_list(unsigned int elem);
int find_mid(struct node *head);
#endif
