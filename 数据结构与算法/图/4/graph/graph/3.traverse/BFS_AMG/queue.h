#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdio.h>

#define SIZE	512

void enqueue(int n);
int dequeue(void);
int is_empty(void);
int is_full(void);

extern int queue[SIZE];

#endif
