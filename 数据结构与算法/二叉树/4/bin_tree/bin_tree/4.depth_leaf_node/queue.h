#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdio.h>
#include "binary_tree.h"

#define SIZE	512

void enqueue(struct BinTree_node c);
struct BinTree_node dequeue(void);
int is_empty(void);
int is_full(void);

#endif
