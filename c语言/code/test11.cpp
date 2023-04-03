#include <iostream>
#include <cstring>

using namespace std;

void fun(char *pre)
{
    pre = new char[100];
    strcpy(pre, "dsgj");
    cout << pre << endl;
}

int main(void)
{
    char *p = NULL;
    fun(p);
    cout << "2" << p;
    return 0;
}
