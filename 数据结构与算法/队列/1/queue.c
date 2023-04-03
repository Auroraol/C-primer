#include <stdlib.h>
#include <stdio.h>
#define SIZE    512
char queue[SIZE];
int head = 0, tail = 0;

int is_empty();   
void enqueue(char c);
char dequeue(void);
int is_full();
int main(void)
{
    char c = 'a';
    for (int i = 0; i < 3; i++)
    {
        if (!is_full())
        {   
            enqueue(c);
            c++;     // c 从a--> b
        } 
    }
    while (!is_empty())
    {
        putchar(dequeue());
    }  
    printf("\n");
    return 0;
}

void enqueue(char c)
{
   // queue[tail++] = c;  //入队列就是把某一个运算压入到尾部再更新位置 //tail++ 表示 先用用完之后再++
    //考虑到循环队列
    queue[tail] = c;
    tail = (tail + 1) % SIZE; //到队列的数组下标的最大值后要从0开始了
}

char dequeue(void)
{
   // return queue[tail++];  //队列是先进先出
    char ch;
    ch = queue[head];
    head = (head + 1) % SIZE;
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

