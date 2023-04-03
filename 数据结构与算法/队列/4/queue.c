#include <stdio.h>
#include <string.h>
#define SIZE    512
char queue[SIZE];
int head = 0, tail = 0;

int is_empty();   
void tail_enqueue(char c);
char tail_dequeue(void);
void haed_enqueue(char c);
char head_dequeue(void);
int is_palindrom(char *pt);
int is_full();
int main(void)
{
    char str[100];
    printf("PLease enter a string");
    gets(str);
    
    if (is_palindrom(str))
        printf("str is a palindrom\n");

    else 
        printf("str is not a palindorm\n");
    return 0;
}

void tail_enqueue(char c)
{
   // queue[tail++] = c;  //入队列就是把某一个运算压入到尾部再更新位置 //tail++ 表示 先用用完之后再++
    //考虑到循环队列
    queue[tail] = c;
    tail = (tail + 1) % SIZE; //到队列的数组下标的最大值后要从0开始了
}

char tail_dequeue(void)
{
   // return queue[tail++];  //队列是先进先出
    tail = (tail - 1 + SIZE) % SIZE;  
    return queue[tail];
}

void head_enqueue(char c)
{
    head = (head - 1 + SIZE) % SIZE;  // +size 是考虑到负数的情况 
    queue[head] = c;
}

char head_dequeue(void)
{
    char ch;
    ch = queue[head];
    head = (head + 1)% SIZE;
    return ch;
}
int is_empty()   // 队头和对尾相等就为空
{
    return head == tail;
}

int is_full()
{
    return (tail + 1) % SIZE == head;
}

int is_palindrom(char *pt)
{
    int i, len;
    len = strlen(pt);
    char c1, c2;
    for (i = 0; i < len; i++)
        if (!is_full())
            tail_enqueue(pt[i]);
   
    while (!is_empty())
    {
        c1 = head_dequeue();
        if (!is_empty())
            c2 = tail_dequeue();
        else
            break;

        if (c1 == c2)
            continue;
        else
            return 0;
    }
    return 1;
}
