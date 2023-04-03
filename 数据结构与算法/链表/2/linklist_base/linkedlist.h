#ifndef LINKEDLIST_H_
#define LINKEDLSIT_H_

struct node
{
    unsigned char elem;
    struct node *next;
};

int search( unsigned char elem);
void print_linklist(void);
void delete_node(int pos);
void insert_node(int pos, char elem);// pos 表示位置 前驱点   elem表示要处理的数据
void create_list(unsigned char elem);

#endif
