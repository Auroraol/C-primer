#include <stdio.h>

char stack[512];
int top = 0;

void push(char c);
char pop(void);
int is_empty(void);

int main(void)
{
    push('a');
    push('b');
    push('c');

    while (!is_empty())
    { 
        putchar(pop());
    }
    printf("\n");
    return 0;
}

void push(char c)
{
    stack[top++] = c;

}

// 出栈
char pop(void)
{
    return stack[--top];
}

//判断
/*
int is_empty(void)
{
    if (top == 0)
    {
        return 1;
    }
    else 
        return 0;
}
*/

//改进
int is_empty(void)
{
    return top == 0;  //因为这个关系表达式本身 就可以判断 
}
