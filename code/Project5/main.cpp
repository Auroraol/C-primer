#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>


using namespace std;


int main()
{

	ifstream fin;
	fin.open("test.txt", ios::in);
	if (!fin.is_open())
	{
		cout << "打开文件失败！！！";
		return 0;
	}


	vector<int> target_1, target_2;		//用于存放目标数据
	vector<string> item;				//用于存放文件中的一行数据
	string temp;						//把文件中的一行数据作为字符串放入容器中


	while (getline(fin, temp))          //利用getline（）读取每一行，并放入到 item 中
	{
		item.push_back(temp);
	}

	for (auto it = item.begin(); it != item.end(); it++)
	{

		stringstream word(*it);                 //其作用是把字符串分解为单词(在此处就是把一行数据分为单个数据)
		string str;
		int count = 0;							 //统计一行数据中单个数据个数

		//获取文件中的第 1、2 列数据
		while (word >> str)                      //以空格为界，把istringstream中数据取出放入到依次s中
		{
			//获取第1列数据
			if (count == 1)
			{
				int r = atoi(str.c_str());       //数据类型转换，将string类型转换成float,如果字符串不是有数字组成，则字符被转化为 0

				target_1.push_back(r);
			}

			//获取第2列数据
			else if (count == 2)
			{
				int r = atoi(str.c_str());       //数据类型转换，将string类型转换成float

				target_2.push_back(r);
			}
			count++;
		}
	}


	// 遍历
	cout << "目标数据大小: " << target_1.size() << endl;

	auto it = target_1.begin();
	auto itt = target_2.begin();

	for (; it != target_1.end(), itt != target_2.end(); it++, itt++)
	{
		cout << *it << "      \t" << *itt << endl;
	}


	return 0;
}