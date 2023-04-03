#include <iostream>
#include <cmath>
using namespace std;

int fun1(int a, int b)
{
    cout << "fun1\n";
    return a + b;
}

int fun2(int a, int b)
{
    cout << "fun2\n";
    return a - b;
}

void test1()
{
    int a = 5;
    int count = 0;
    while (--a)
    {
        cout << a;
        count++;
    }
    cout << count;
}

int main(void)
{
    // int (*pf)(int, int);
    // pf = fun1;
    // int a = pf(1, 2);
    // cout << a << endl;
    // pf = fun2;
    // int b = pf(4, 2);
    // cout << b << endl;
    // int a = 5; // 0101
    // while (a)
    // {
    //     int d = (a & 1);
    //     cout << d << endl;
    //     a >>= 1;
    // }
    // int n = 30;
    // int a[3] = {2, 3, 5};
    // for (int i = 0; i < 3; i++)
    // {
    //     while (n % a[i] == 0)
    //     {
    //         /* code */
    //         n /= a[i];
    //     }
    // }
    // if (n == 1)
    //     cout << "整除";
    // else
    //     cout << "不整除";

    // int a = 124;
    // for (int i = 1; i <= sqrt(a); i++)
    // {
    //     if (a % i == 0)
    //     {
    //         cout << i << endl;
    //         if ((a / i) != i)
    //         {
    //             cout << a / i << endl;
    //         }
    //     }
    // }
    // int len = 10;
    // int a[len] = {0};
    // for (int i = 0; i < len; i++)
    // {
    //     a[i] = i;
    // }
    // // // for (int c : a)
    // // // {
    // // //     cout << c;
    // // // }
    // int i = 10; // for (int i = 9; i >= 1; --i)
    // while (--i)

    // {
    //     int index = rand() % i;
    //     // cout << a[len] << a[index];
    //     swap(a[i], a[index]);
    //     // cout << a[len] << a[index];
    //     // cout << endl;
    // }
    // int count = 0;
    // for (int i = 0; i < len; i++)
    // {
    //     cout << a[i] << endl;
    //     count++;
    // }
    // cout << count;
    test1();

    return 0;
}