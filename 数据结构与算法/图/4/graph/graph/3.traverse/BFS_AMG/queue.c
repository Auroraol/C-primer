#include "queue.h"

int queue[SIZE];

int head = 0, tail = 0;

void enqueue(int n)
{
	queue[tail] = n;
	tail = (tail + 1) % SIZE;
}

int dequeue(void)
{
	int n;
	n = queue[head];
	head = (head + 1) % SIZE;

	return n;
}

int is_empty(void)
{
	return head == tail;
}

int is_full(void)
{
	return (tail + 1) % SIZE == head;
}
