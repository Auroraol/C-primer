#include <iostream>
#include <string>
#include <cstring>
using namespace std;

void fun1()
{
    int a = 2;
    double b = 5;
    string s1, s2;
    const char *c = "67";
    s1 = to_string(a);
    s1 = to_string(b);
    stoi(s1);
    atoi(c);
}

void fun2()
{
    string s = "abcd";
    for (int i = 0; i < 4; i++)
    {
        int a = s[i] - 'a' + 1;
        cout << a;
    }
}

void fun3()
{
    bool a = false;
    bool b = true;
    if (a == b)
        cout << "不相等";
    else
        cout << "相等";
}

void fun4(int *arr)
{

    int len = 4;

    for (int i = 0; i < len; i++)
    {
        arr[i] += 1;
    }
}

int main(void)
{
    int a[4] = {1, 2, 3, 4};
    int len = sizeof(a) / sizeof(int);
    fun4(a);
    for (int i = 0; i < 4; i++)
    {
        cout << a[i] << endl;
    }
    cout << endl;
    const char *b = "4444";
    for (int i = 0; i < 4; i++)
    {
        cout << b[i];
    }

    return 0;
}