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

// ����
void printArray(int **arr, int len) // arr ---> һ��ָ��  int *p[] = [1 2 3 4 5 ]
{
    for (int i = 0; i < len; i++)
    {
        printf("%d\n", *arr[i]); // arr[i] �洢���� int //  �Ƚ����� �ҵ����� �� ȡ��Ԫ��
    }
}
/*
// ����  ֱ����ͬ��ָ��
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

//  ֱ����ͬ��ָ��
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
//     printf("����ָ%d\n", p[3]);
// }

int main()
{
    int *p = NULL;
    allocateSpace(&p); // int *p = arr;

    printArray(p, 10);

    freeSpace(&p); // ��ָ��
    // freeSpace(p);    // Ұָ��  // ��Ϊ�ǰ�ֵ���ݵ�
    if (p == NULL)
    {
        printf("����ָ���Ѿ��ÿ�\n");
    }
    //     test();
}