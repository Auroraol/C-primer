#include <stdio.h>
#include <string.h>

char stack[512];
int top = 0;

void push(char c);
char pop(void);
int is_empty(void);

int main(void)
{
    char str[100];
    int i,len;

    printf("Please enter a calcuate experssion:");
    gets(str);

    len = strlen(str);
    for (i=0; i < len; i++)
    {
        if (str[i] == '(')
           continue;
        else if ((str[i] >= '0') && (str[i] <= '9'))
           printf("%c",str[i]);
        else if ((str[i] == '+') || (str[i] == '-') || (str[i] == '*'))
           push(str[i]);   
        else if (str[i] == ')')
            printf("%c",pop());

    }
    printf("\n");
    return 0;
}

//入栈
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
int is_empty(void)
{
    return top == 0;  
}
