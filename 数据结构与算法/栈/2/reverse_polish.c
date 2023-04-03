#include <stdio.h>
#include <string.h>   // string.h

int stack[512];
int top = 0;

void push(int c);
int pop(void);
int is_empty(void);

int main(void)
{
    char a[100];
    int n;
    int i;
    int n1,n2;
    printf("Please enter a reverse polish expression:\n");
    gets(a);   //cin可以是多种类型 //  而get() a是字符串
    n = strlen(a);
    for (i = 0; i < n; i++)
    {
        if ((a[i] >= '0') && (a[i] <= '9'))      
            push(a[i] - '0');       // 字符j减 '0'得到 整数/ 
        else
        {
            n2 = pop();  //先出来的 
            n1 = pop();  //后弹出来的
            switch(a[i])
            {
                case '+':
                        push(n1 + n2);
                        break; 
                case '-': 
                        push(n1 - n2);
                        break;
                case '*':
                        push(n1 * n2);
                        break;
            }
        }
    }
    printf("result = %d\n", pop());
    return 0;
}

void push(int c)
{
    stack[top++] = c;

}

// 出栈
int pop(void)
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
