#include <fstream>
#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
	ifstream fs("test01.txt");  // ��һ�����ļ��ĸ�Ŀ¼���ڶ��п�ʼ���ļ������������Լ�ÿ���˵����ꡣ

	if (!fs.is_open())
	{
		cout << "Error in open file!" << endl;
		return -1;
	}

	char buff[256];
	char RootPath[256];
	int index = 1;
	while (!fs.eof())
	{
		fs.getline(buff, 256);	//��ȡ�ļ��е�һ��
		if (index == 1)
		{
			memcpy(RootPath, buff, sizeof(buff));
			cout << "��Ŀ¼: " << RootPath << endl;
			index++;
		}
		else
		{
			char* p;
			char ImgName[256];
			/************ImgPath************/  //1500.jpg	1	 [192, 132, 213, 205]
			char ImgPath[256];
			p = strtok(buff, "	");   // �õ���һ����" "�ָ����ַ��� 	//���Ʊ��Ϊ�ָ����ָ�����һ���ַ�������1500.jpg


			string ImgName_str = p;
			ImgName_str.erase(ImgName_str.size() - 4, ImgName_str.size());
			sprintf(ImgName, "%s", ImgName_str.data());

			sprintf(ImgPath, "%s\\%s", RootPath, p);   // C:\Users\Administrator\Desktop\liuwei\1501.jpg
			cout << "ͼƬ·��:  " << ImgPath << endl;

			/*************PersonNum********/
			p = strtok(NULL, "	");
			int PersonNum = atoi(p);
			cout << "PersonNum:  " << PersonNum << endl;   	//���Ʊ��Ϊ�ָ����ָ����ڶ����ַ�������1

			/*************Point************/
			for (int i = 0; i < PersonNum; i++)
			{
				int pt[4];
				p = strtok(NULL, "	");  //���Ʊ��Ϊ�ָ����ָ����ַ���[192, 132, 213, 205]

				//num1
				string str = p;
				str.erase(0, 1);   //����[
				for (int j = 0; j < 4; j++)
				{
					int pos = str.find(", ");  	//Ѱ��,��λ��
					string point = str.substr(0, pos);  	//��ȡ�����ַ���
					pt[j] = atoi(point.data());   //����ȡ�������ַ���ת��������
					str.erase(0, pos + 2);    //����ȡ�������ַ���ת��������
				}

				//����roiλ��
				int start_x, start_y;
				int height, width;
				start_x = pt[0];
				start_y = pt[1];
				height = pt[3] - pt[1];
				width = pt[2] - pt[0];

				char savePath[256];
				sprintf(savePath, "Images/person_%s_%d.jpg", ImgName, i + 1);
				cout << savePath << endl;
				cout << "����: (" << start_x << ", " << start_y << ")  ��" << height << " ��" << width;
				/*
				//����ͼ��
				Mat Img = imread(ImgPath);
				Rect rect(start_x, start_y, width, height);
				Mat roi = Img(rect);
				IplImage* saveImg = new IplImage(roi);
				cvSaveImage(savePath, saveImg);
				*/

			}

			index++;
		}
	}
	return 0;
}