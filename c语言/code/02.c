#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

void allocateSpace(int **p)
{
    int *arr = malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++)
    {
        arr[i] = i;
    }
    *p = arr;
}

// 堆区
void printArray(int **arr, int len) // arr ---> 一级指针  int *p[] = [1 2 3 4 5 ]
{
    for (int i = 0; i < len; i++)
    {
        printf("%d\n", *arr[i]); // arr[i] 存储的是 int //  先解引用 找到数组 再 取出元素
    }
}
/*
// 或者  直接用同级指针
void printArray(int * arr, int len)
{
    for (int i = 0; i < len;i++)
    {
        printf("%d\n", arr[i]);
    }
}
*/

void freeSpace(int **arr)
{
    if (*arr != NULL)
    {
        free(*arr);
        *arr = NULL;
    }
}

//  直接用同级指针
void freeSpace2(int *arr)
{
    if (arr != NULL)
    {
        free(arr);
        arr = NULL;
    }
}

// void test()
// {
//     int *p[5] = {1, 2, 3, 4, 5};
//     printf("数组指%d\n", p[3]);
// }

int main()
{
    int *p = NULL;
    allocateSpace(&p); // int *p = arr;

    printArray(p, 10);

    freeSpace(&p); // 空指针
    // freeSpace(p);    // 野指针  // 因为是按值传递的
    if (p == NULL)
    {
        printf("数组指针已经置空\n");
    }
    //     test();
}