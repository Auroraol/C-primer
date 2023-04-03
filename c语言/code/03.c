#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

void printArray(int **arr, int len) // int arr[] ====  int * arr 前者可读性高
{
    *arr[1] = 18;
    printf("p[-1] = %d\n", arr[1]);
}

void test01()
{

    int arr[5] = {1, 2, 3, 4, 5};

    // 1、当sizeof数组名时候，统计是整个数组的大小
    // printf("sizeof(arr) = %d\n", sizeof(arr));

    // // 2、当对数组名 取地址的时候
    // printf("%d\n", &arr);     // arr --> int*  ---> &arr --> int**
    // printf("%d\n", &arr + 1); //步长 跳越的整个数组长度

    //除了以上两种情况外 ， 数组名都指向数组中的首地址
    int *p = arr; // 直接对int*p进行赋值，也不会报错

    //数组名 是个指针常量  // 故指向针不能改, 指向的值可以改
    // arr = NULL;  //err
    // *arr = 10;  //ok

    int len = sizeof(arr) / sizeof(int);
    // printArray(arr, len);
    printArray(&p, len);

    printf("p[-1] = %d\n", arr[1]);

    // //数组下标是否可以为负数?
    // p = p + 3;
    // printf("p[-1] = %d\n", p[-1]);
    // //上述代码等价于
    // printf("p[-1] = %d\n", *(p - 1));
}

int main(void)
{
    test01();
    return 0;
}