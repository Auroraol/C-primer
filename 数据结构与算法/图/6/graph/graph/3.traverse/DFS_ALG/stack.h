#ifndef __STACK_H__
#define __STACK_H__

#include <stdio.h>

extern int stack[512];
extern int top;

void push(int c);
int pop(void);
int is_empty(void);

#endif
