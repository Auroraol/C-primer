#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
const char *fileNaem = "file.txt";

void read(const char *file)
{

    ifstream fin(file);
    if (!fin.is_open())
    {
        cout << "打开失败";
    }
    char buff[1024] = {0};
    // while (fin >> buff)
    // {
    //     cout << buff << endl;
    // }
    // while (fin.getline(buff, sizeof(buff)))
    // {
    //     /* code */
    //     cout << buff << endl;
    // }

    // char a1, a2, a3, a4;
    // fin >> a1 >> a2 >> a3 >> a4;
    // cout << a2;
    int a, b, c;
    while (fin.getline(buff, sizeof(buff)))
    {
        stringstream word(buff);
        word >> a >> b >> c;
        cout << a << endl;
    }
    cout << "???";

    fin.close();
}

void write()
{
    ofstream fout(fileNaem, ios::app | ios::out);
    if (!fout.is_open())
    {
        cerr << "Can't open" << fileNaem << "file for output.\n";
    }
    fout << "历史失败\n"
         << "你是猪"
         << "??";
    fout.close();
}

int main(void)
{
    read(fileNaem);
    write();
    return 0;
}