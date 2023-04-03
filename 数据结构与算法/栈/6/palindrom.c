#include <stdio.h>
#include <string.h>
char stack[512];
int top = 0;

void push(char c);
char pop(void);
int is_empty(void);
int is_palindrom(char *pt);
int main(void)
{
    char str[100];
    printf("Please enter a string: ");
    gets(str);
    if (is_palindrom(str))
        printf("str is a palindrom.\n");
    else 
        printf("str is not a palindrom.\n");
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

int is_palindrom(char *pt)
{
    int len, i;
    len = strlen(pt);

    for (i = 0; i < len/2; i++)
        push(pt[i]);
    if (len % 2 ==1)  //奇数
        i++; //跳过中心点
    while (!is_empty())    // 为0循环
    {
        if(pop() == pt[i])
            i++;
        else 
            return 0;
    }
    return 1;
}
