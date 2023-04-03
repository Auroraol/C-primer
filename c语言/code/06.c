#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printText(void *data, void (*func)(void *))
{
    func(data);
}

void myPrintInt(void *data) //参数就是每个元素的地址
{
    int *num = data;
    printf("%d\n", *num);
}

void test01()
{
    double a = 10;
    printText(&a, myPrintInt);
}

struct Person
{
    char name[64];
    int age;
};
void myPrintPerson(void *data) //参数就是每个元素的地址
{
    struct Person *p = data;
    printf("姓名：%s 年龄： %d \n", p->name, p->age);
}
void test02()
{
    struct Person p = {"Tom", 100};
    printText(&p, myPrintPerson);
}

void fun()
{
    for (int i = 1; i < 10; i++)
    {
        printf("%d", i + 1);
        if (i % 3 == 2)
            printf("\n");
    }
}

void test03()
{
    // char b[] = "hello"; //定义字符串,用双引号括起, '/0'计算机去完成
    // char *p = b;
    // printf("%c", *p);
    int a[10] = {0};
    int length = sizeof(a) / sizeof(int);
    printf("%d", length);
    char b[] = "1";
    char c[] = "c";
    if (strcmp(b, c) > 0)
    {
        printf("b");
    }
    else
        printf("c");
}

void fun2()
{
    char ch[] = "777";
    char *p = ch;
    while (*p)
    {
        printf("%c", *p);
        p++;
    }
    // char a = '77';
    // printf("%d", a);
}

void fun1()
{
    // int a[] = {1, 2, 3, 4};
    // int len = sizeof(a) / sizeof(int);
    // printf("%d", len);

    // char *p = "sdgjj";
    char *p = "Hello world";
    // strcpy(p, "1111");
    printf("%s", *p);
}

int main(void)
{
    // test01();
    // double n = 3.914;
    // int a = n;
    // printf("%d", a);
    // fun();
    // // test03();
    // fun1();

    char *p = "dshgh";
    // // std::cout << *p;
    // std::string s = "sfdjaj";
    printf("%s", p);
    // s = "sdgj";
    return 0;
}