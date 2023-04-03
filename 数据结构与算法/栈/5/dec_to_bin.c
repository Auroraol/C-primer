#include <stdio.h>
#include <string.h>

int stack[512];
int top = 0;

void push(int c);
char pop(void);
int is_empty(void);

int main(void)
{
    int num;
    printf("Please enter a calcuate experssion:");
    scanf("%d",&num);
    while(num)
    {
        push(num % 2); //余数入栈
        num /= 2;
    }
    while(!is_empty())
        printf("%d",pop());
    printf("\n");
    return 0;
}

//入栈
void push(int c)
{
    stack[top++] = c;

}

// 出栈
char pop(void)
{
    return stack[--top];
}

//判断
int is_empty(void)
{
    return top == 0;  
}
