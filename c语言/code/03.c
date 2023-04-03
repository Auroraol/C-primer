#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

void printArray(int **arr, int len) // int arr[] ====  int * arr ǰ�߿ɶ��Ը�
{
    *arr[1] = 18;
    printf("p[-1] = %d\n", arr[1]);
}

void test01()
{

    int arr[5] = {1, 2, 3, 4, 5};

    // 1����sizeof������ʱ��ͳ������������Ĵ�С
    // printf("sizeof(arr) = %d\n", sizeof(arr));

    // // 2������������ ȡ��ַ��ʱ��
    // printf("%d\n", &arr);     // arr --> int*  ---> &arr --> int**
    // printf("%d\n", &arr + 1); //���� ��Խ���������鳤��

    //����������������� �� ��������ָ�������е��׵�ַ
    int *p = arr; // ֱ�Ӷ�int*p���и�ֵ��Ҳ���ᱨ��

    //������ �Ǹ�ָ�볣��  // ��ָ���벻�ܸ�, ָ���ֵ���Ը�
    // arr = NULL;  //err
    // *arr = 10;  //ok

    int len = sizeof(arr) / sizeof(int);
    // printArray(arr, len);
    printArray(&p, len);

    printf("p[-1] = %d\n", arr[1]);

    // //�����±��Ƿ����Ϊ����?
    // p = p + 3;
    // printf("p[-1] = %d\n", p[-1]);
    // //��������ȼ���
    // printf("p[-1] = %d\n", *(p - 1));
}

int main(void)
{
    test01();
    return 0;
}