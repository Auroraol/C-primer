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
		cout << "���ļ�ʧ�ܣ�����";
		return 0;
	}


	vector<int> target_1, target_2;		//���ڴ��Ŀ������
	vector<string> item;				//���ڴ���ļ��е�һ������
	string temp;						//���ļ��е�һ��������Ϊ�ַ�������������


	while (getline(fin, temp))          //����getline������ȡÿһ�У������뵽 item ��
	{
		item.push_back(temp);
	}

	for (auto it = item.begin(); it != item.end(); it++)
	{

		stringstream word(*it);                 //�������ǰ��ַ����ֽ�Ϊ����(�ڴ˴����ǰ�һ�����ݷ�Ϊ��������)
		string str;
		int count = 0;							 //ͳ��һ�������е������ݸ���

		//��ȡ�ļ��еĵ� 1��2 ������
		while (word >> str)                      //�Կո�Ϊ�磬��istringstream������ȡ�����뵽����s��
		{
			//��ȡ��1������
			if (count == 1)
			{
				int r = atoi(str.c_str());       //��������ת������string����ת����float,����ַ���������������ɣ����ַ���ת��Ϊ 0

				target_1.push_back(r);
			}

			//��ȡ��2������
			else if (count == 2)
			{
				int r = atoi(str.c_str());       //��������ת������string����ת����float

				target_2.push_back(r);
			}
			count++;
		}
	}


	// ����
	cout << "Ŀ�����ݴ�С: " << target_1.size() << endl;

	auto it = target_1.begin();
	auto itt = target_2.begin();

	for (; it != target_1.end(), itt != target_2.end(); it++, itt++)
	{
		cout << *it << "      \t" << *itt << endl;
	}


	return 0;
}