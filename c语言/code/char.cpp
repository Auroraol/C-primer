#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>

using namespace std;

void fun1(char *pre)
{
    pre = new char[100];
    strcpy(pre, "dsgj");
    cout << pre << endl;
}
void fun0()
{
    const char *p = "dshgh";
    // // std::cout << *p;
    // std::string s = "sfdjaj";
    printf("%s", p);
    // s = "sdgj";
    // cout << p;
    // // FCC
    // // strcpy(p, "dsgh");
    string a = "fcc123";
    for (string::iterator it = a.begin(); it != a.end(); it++)
    {
        cout << *it << endl;
    }

    for (char n : a)
    {
        cout << n;
    }
}

int main(void)
{
    // char *c = NULL;
    // string s;
    // cout << "please input:";
    // cin >> s;
    // fun1(&c, s.c_str());
    // // cout << s;

    // if (c = NULL)
    //     cout << "wusdga";
    // else
    //     cout << *c;
    char *a = new char[22];
    fun1(a);
    cout << a;
    return 0;
}
