#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
int *getSpace()
{
    int *p = malloc(sizeof(int) * 5);
    if (!p)
    {
        printf("分配内存");
    }
    for (int i = 0; i < 5; i++)
    {
        p[i] = i + 100; //所有在连续空间上开辟的数据，都可以利用下标进行索引
    }
    return p;
}

void allocateSpace(char *p)
{
    // char *temp = malloc(100);
    // memset(temp, 0, 100); //空间清零
    // strcpy(temp, "hello world");
    printf("%s\n", p);
}

//利用返回值
char *allocateSpace3()
{
    char *temp = malloc(100);
    memset(temp, 0, 100);
    temp = "hello world";
    return temp;
}
void test03()
{
    char *p = NULL;
    p = allocateSpace3();
    printf("%s\n", p);
}

void test02()
{
    char *p = "cxhah"; // char *temp = malloc(100);
    // memset(temp, 0, 100); //空间清零
    // strcpy(temp, "hello world");
    allocateSpace(p);
}

void test01()
{
    int *p = getSpace();
    for (int i = 0; i < 5; i++)
    {
        printf("%d\n", p[i]);
    }
    //堆区的数据  自己开辟，自己管理释放
    free(p);
    p = NULL;
}

struct Person
{
    char a;       // 0 ~ 3
    int b;        // 4 ~ 7
    char buf[64]; // 8 ~ 71  // char buf[64]-->64个字节
    int d;        // 72 ~ 75  // int 4字节
};

void test04()
{
    struct Person p = {'A', 10, "hello world", 10000};

    //自定义数据类型找偏移量 可以通过函数寻找
    printf("%d\n", offsetof(struct Person, d)); // 72 //#include <stddef.h>    // std标准  def宏

    //打印d的数字
    printf("d = %d\n", *(int *)((char *)&p + offsetof(struct Person, d))); // 10000
    // &p <---  struct Person*  // 强转(char *)--->可以得到跳跃字节为1, 强转(int *)--->可以得到跳跃字节为4 //
    printf("d = %d\n", *(int *)((int *)&p + 18));                       // 10000
    printf("buff = %s\n", ((char *)&p + offsetof(struct Person, buf))); //"hello world"
}

void test05()
{
    char *p = malloc(sizeof(char *) * 64);
    char *temp = p;
    for (int i = 0; i < 10; i++)
    {
        *temp = i + 97;
        printf("%c\t", *temp);
        temp++;
    }
    if (p)
    {
        free(p);
        p = NULL;
    }
}

// 打印数组
void printArray(int **arr, int len)
{

    for (int i = 0; i < len; i++)
    {
        printf("数组中第%d个元素的值为%d \n", i + 1, *arr[i]); //值
    }
}

void test06()
{
    int **pArray = malloc(sizeof(int *) * 5); //堆区开辟空间 在32位系统中，所有指针都是4B  [int** int** int** int** int**]

    //在栈中分配数据
    int a1 = 100;
    int a2 = 200;
    int a3 = 300;
    int a4 = 400;
    int a5 = 500;

    pArray[0] = &a1; // int** -->
    pArray[1] = &a2;
    pArray[2] = &a3;
    pArray[3] = &a4;
    pArray[4] = &a5;
    // pArray[1] = 102;

    for (int i = 0, j = 0; i < 5; i++, j++)
    {
        if (j < 4)
        {
            pArray[j] = malloc(4); //代表申请4个字节的内存空间
            *(pArray[j]) = j + 100;
        }
        else
            pArray[j] = &a1;
    }

    // int len = sizeof(pArray)/ sizeof(int *)  err 4/ 4 = 1 // sizeof(pArray)-->计算int * 大小
    // int len = 5;
    printArray(pArray, 5);

    //释放堆区空间
    if (pArray != NULL)
    {
        free(pArray);
        pArray = NULL;
    }
}

void test07()
{
    int a = 15;
    int *pArray[5]; //开辟到栈中  // 指针类型的数组  [int* int* int* int* int*]
                    // pArray[1] = &a;
                    // printf("数组元素:%d\n", *pArray[1]); //值

    for (int i = 0, j = 0; i < 5; i++, j++)
    {
        if (j < 4)
        {
            pArray[j] = malloc(4); //代表申请4个字节的内存空间
            *(pArray[j]) = j + 100;
            // pArray[j] = 100;
        }
        else
            pArray[j] = &a;
    }

    // int len = sizeof(pArray)/ sizeof(int *) ok 20 / 4 = 5  // sizeof(pArray) -->计算整个数组大小
    // 打印数组  //
    printArray(pArray, 5); // ok
                           /*
                           void printArray(int **arr, int len)   // 一级传二级 相当于按指针传递  //次数 aar 就相当于 一个一级指针
                       
                               for (int i = 0; i < len; i++)
                               {
                                   printf("数组中第%d个元素的值为%d \n", i + 1, *arr[i]); //值
                               }
                           }
                           */
    //释放堆区空间
    for (int i = 0; i < 5; i++)
    {
        if (pArray[i] != NULL)
        {
            free(pArray[i]);
            pArray[i] = NULL;
        }
    }
}

void test10()
{
    int a = 10;
    int *q;  //指针p指向 int类型
    int **p; //指针p指向int * 类型    // 二级指针 指向 一级指针的地址
    int *t;

    q = &a; // q 指向 a
    p = &q; // p 指向q， q是一个int类型指针
    t = q;
}

int main(void)
{
    // test01();
    // test02();
    // test03();
    // char *p1 = NULL;
    // p1 = "hello world";
    // // strcpy(p1, "1111"); // err
    // printf("%d\n", p1);
    // test06();
    test07();
    // test08();
    return 0;
}