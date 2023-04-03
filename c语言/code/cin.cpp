#include <iostream>
#include <cstring>
using namespace std;

void test1()
{
    cout << "a. annay client\n"
         << "b. buil client\n"
         << "c. alm client d. deceive client\n";
    cout << "Enter a, b, c, or q: ";
    char c;
    cin >> c;
    while (c != 'q')
    {
        while (cin.get() != '\n')
            continue;
        switch (c)
        {
        case 'a':
            cout << "annay client\n";
            break;
        case 'b':
            cout << "12345";
            break;
        case 'c':
            cout << "c1\n";
        case '#':
            cout << "c2\n";
            break;
        default:
            cout << "My is default";
        }
        cout << endl;
        cout << "Enter a, b, c, or q: ";
        cin >> c;
    }
}

void test2()
{
    // int a[6] = {1, 2, 3, 4, 5, 6};
    // for (int i = 2; i < 6; i++)
    // {
    //     // cout << a[i] << endl;
    //     cout << a[i];
    //     if (i % 2 == 3)
    //         cout << endl;
    // }
}

void test3()
{
    int size = 20;
    char name[size];
    cout << "please input:  ";
    // cin.getline(name, size);
    // cin >> name;
    cin.get(name, size);
}

void test04()
{
    int size = 20;
    char name[size];
    cin.get(name, size);
    while (cin && cin.get() != '\n')
        continue;
}

struct name
{
    int a;
    char b[122];
    int c[4];
};

void test05()
{
    // ÎÄ¼þÊäÈë
    name *p = new name;
    p->a = 10;
    strcpy(p->b, "bbb");
    int a[4] = {1, 2, 3, 4};
    for (int i = 0; i < 4; i++)
    {
        p->c[i] = a[i];
        cout << p->c[i] << endl;
    }
}

int main(void)
{
    // test1();
    test05();
    return 0;
}
