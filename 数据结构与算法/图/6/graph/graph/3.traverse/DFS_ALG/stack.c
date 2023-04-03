#include "stack.h"

int stack[512];
int top = 0;

void push(int c)
{
	stack[top++] = c;
}

int pop(void)
{
	return stack[--top];
}

int is_empty(void)
{
	return top == 0;
}
