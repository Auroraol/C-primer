#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
int *getSpace()
{
    int *p = malloc(sizeof(int) * 5);
    if (!p)
    {
        printf("�����ڴ�");
    }
    for (int i = 0; i < 5; i++)
    {
        p[i] = i + 100; //�����������ռ��Ͽ��ٵ����ݣ������������±��������
    }
    return p;
}

void allocateSpace(char *p)
{
    // char *temp = malloc(100);
    // memset(temp, 0, 100); //�ռ�����
    // strcpy(temp, "hello world");
    printf("%s\n", p);
}

//���÷���ֵ
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
    // memset(temp, 0, 100); //�ռ�����
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
    //����������  �Լ����٣��Լ������ͷ�
    free(p);
    p = NULL;
}

struct Person
{
    char a;       // 0 ~ 3
    int b;        // 4 ~ 7
    char buf[64]; // 8 ~ 71  // char buf[64]-->64���ֽ�
    int d;        // 72 ~ 75  // int 4�ֽ�
};

void test04()
{
    struct Person p = {'A', 10, "hello world", 10000};

    //�Զ�������������ƫ���� ����ͨ������Ѱ��
    printf("%d\n", offsetof(struct Person, d)); // 72 //#include <stddef.h>    // std��׼  def��

    //��ӡd������
    printf("d = %d\n", *(int *)((char *)&p + offsetof(struct Person, d))); // 10000
    // &p <---  struct Person*  // ǿת(char *)--->���Եõ���Ծ�ֽ�Ϊ1, ǿת(int *)--->���Եõ���Ծ�ֽ�Ϊ4 //
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

// ��ӡ����
void printArray(int **arr, int len)
{

    for (int i = 0; i < len; i++)
    {
        printf("�����е�%d��Ԫ�ص�ֵΪ%d \n", i + 1, *arr[i]); //ֵ
    }
}

void test06()
{
    int **pArray = malloc(sizeof(int *) * 5); //�������ٿռ� ��32λϵͳ�У�����ָ�붼��4B  [int** int** int** int** int**]

    //��ջ�з�������
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
            pArray[j] = malloc(4); //��������4���ֽڵ��ڴ�ռ�
            *(pArray[j]) = j + 100;
        }
        else
            pArray[j] = &a1;
    }

    // int len = sizeof(pArray)/ sizeof(int *)  err 4/ 4 = 1 // sizeof(pArray)-->����int * ��С
    // int len = 5;
    printArray(pArray, 5);

    //�ͷŶ����ռ�
    if (pArray != NULL)
    {
        free(pArray);
        pArray = NULL;
    }
}

void test07()
{
    int a = 15;
    int *pArray[5]; //���ٵ�ջ��  // ָ�����͵�����  [int* int* int* int* int*]
                    // pArray[1] = &a;
                    // printf("����Ԫ��:%d\n", *pArray[1]); //ֵ

    for (int i = 0, j = 0; i < 5; i++, j++)
    {
        if (j < 4)
        {
            pArray[j] = malloc(4); //��������4���ֽڵ��ڴ�ռ�
            *(pArray[j]) = j + 100;
            // pArray[j] = 100;
        }
        else
            pArray[j] = &a;
    }

    // int len = sizeof(pArray)/ sizeof(int *) ok 20 / 4 = 5  // sizeof(pArray) -->�������������С
    // ��ӡ����  //
    printArray(pArray, 5); // ok
                           /*
                           void printArray(int **arr, int len)   // һ�������� �൱�ڰ�ָ�봫��  //���� aar ���൱�� һ��һ��ָ��
                       
                               for (int i = 0; i < len; i++)
                               {
                                   printf("�����е�%d��Ԫ�ص�ֵΪ%d \n", i + 1, *arr[i]); //ֵ
                               }
                           }
                           */
    //�ͷŶ����ռ�
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
    int *q;  //ָ��pָ�� int����
    int **p; //ָ��pָ��int * ����    // ����ָ�� ָ�� һ��ָ��ĵ�ַ
    int *t;

    q = &a; // q ָ�� a
    p = &q; // p ָ��q�� q��һ��int����ָ��
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