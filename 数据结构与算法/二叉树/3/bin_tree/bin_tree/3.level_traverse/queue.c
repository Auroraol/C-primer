#include "queue.h"

struct BinTree_node queue[SIZE]; //队列放置的

int head = 0, tail = 0;

void enqueue(struct BinTree_node c)  //入队列 
{
	queue[tail] = c;
	tail = (tail + 1) % SIZE;
}

struct BinTree_node dequeue(void) //出队列 返回值是struct BinTree_node
{
	struct BinTree_node ch;
	ch = queue[head];
	head = (head + 1) % SIZE;

	return ch;
}

int is_empty(void)
{
	return head == tail;
}

int is_full(void)
{
	return (tail + 1) % SIZE == head;
}
