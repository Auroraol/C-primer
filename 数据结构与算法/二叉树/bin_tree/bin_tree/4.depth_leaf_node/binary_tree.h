#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

#include <stdio.h>
#include <stdlib.h>

struct BinTree_node
{
	unsigned char elem;
	struct BinTree_node *ltree, *rtree;
};

#include "queue.h"

struct BinTree_node *create_bintree(void);
void pre_order(struct BinTree_node *tree);
void in_order(struct BinTree_node *tree);
void pos_order(struct BinTree_node *tree);
void level_traverse(struct BinTree_node *tree);
unsigned int depth(struct BinTree_node *tree);
unsigned int leaf_num(struct BinTree_node *tree);
unsigned int node_num(struct BinTree_node *tree);

#endif
