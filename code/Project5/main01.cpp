#include <fstream>
#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
	ifstream fs("test01.txt");  // 第一行是文件的根目录，第二行开始是文件名、人数、以及每个人的坐标。

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
		fs.getline(buff, 256);	//读取文件中的一行
		if (index == 1)
		{
			memcpy(RootPath, buff, sizeof(buff));
			cout << "根目录: " << RootPath << endl;
			index++;
		}
		else
		{
			char* p;
			char ImgName[256];
			/************ImgPath************/  //1500.jpg	1	 [192, 132, 213, 205]
			char ImgPath[256];
			p = strtok(buff, "	");   // 得到第一个被" "分隔的字符串 	//以制表符为分隔，分隔出第一个字符串，即1500.jpg


			string ImgName_str = p;
			ImgName_str.erase(ImgName_str.size() - 4, ImgName_str.size());
			sprintf(ImgName, "%s", ImgName_str.data());

			sprintf(ImgPath, "%s\\%s", RootPath, p);   // C:\Users\Administrator\Desktop\liuwei\1501.jpg
			cout << "图片路径:  " << ImgPath << endl;

			/*************PersonNum********/
			p = strtok(NULL, "	");
			int PersonNum = atoi(p);
			cout << "PersonNum:  " << PersonNum << endl;   	//以制表符为分隔，分隔出第二个字符串，即1

			/*************Point************/
			for (int i = 0; i < PersonNum; i++)
			{
				int pt[4];
				p = strtok(NULL, "	");  //以制表符为分隔，分隔出字符串[192, 132, 213, 205]

				//num1
				string str = p;
				str.erase(0, 1);   //消除[
				for (int j = 0; j < 4; j++)
				{
					int pos = str.find(", ");  	//寻找,的位置
					string point = str.substr(0, pos);  	//提取数字字符串
					pt[j] = atoi(point.data());   //将提取出来的字符串转换成数字
					str.erase(0, pos + 2);    //将提取出来的字符串转换成数字
				}

				//计算roi位置
				int start_x, start_y;
				int height, width;
				start_x = pt[0];
				start_y = pt[1];
				height = pt[3] - pt[1];
				width = pt[2] - pt[0];

				char savePath[256];
				sprintf(savePath, "Images/person_%s_%d.jpg", ImgName, i + 1);
				cout << savePath << endl;
				cout << "坐标: (" << start_x << ", " << start_y << ")  高" << height << " 宽" << width;
				/*
				//保存图像
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