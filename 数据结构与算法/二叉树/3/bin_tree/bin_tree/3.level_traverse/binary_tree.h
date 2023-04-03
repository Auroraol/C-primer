#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

#include <stdio.h>
#include <stdlib.h>

struct BinTree_node
{
	unsigned char elem;
	struct BinTree_node *ltree, *rtree;
};

#include "queue.h"   // 包含队列的头文件 //放在这里的原因,要用到队列里的 void enqueue(struct BinTree_node c)的形参在这里刚好声明了  

struct BinTree_node *create_bintree(void);
void pre_order(struct BinTree_node *tree);
void in_order(struct BinTree_node *tree);
void pos_order(struct BinTree_node *tree);
void level_traverse(struct BinTree_node *tree);  //层次遍历

#endif
