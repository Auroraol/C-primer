#include "queue.h"

struct BinTree_node queue[SIZE];

int head = 0, tail = 0;

void enqueue(struct BinTree_node c)
{
	queue[tail] = c;
	tail = (tail + 1) % SIZE;
}

struct BinTree_node dequeue(void)
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
