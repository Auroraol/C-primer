#include <fstream>
#include <string>
#include "MasterEncoder.h"

using namespace std;
using MS = MasterEncoder;

int main(int argc, char* argv[])
{
	system("COLOR 0A");

	const char* sign = "master";
	MS::getInstance()->setSignAndKey((char*)sign, strlen(sign), 100);

	char* input = nullptr;
	char* output = nullptr;

	printf("argc = %d\n", argc);
	if (argc >= 2)
	{
		if (strcmp(argv[1], "-help") == 0)
		{//帮助
			printf("	-encode 加密\n");
			printf("	-decode 解密\n");
			printf("	-i 输入文件\n");
			printf("	-o 输出文件\n");
			printf("	example: main.exe -encode -i test.txt -o test1.txt \n");
		}

		if (strcmp(argv[1], "-encode") == 0)
		{//加密
			if (strcmp(argv[2], "-i") == 0)
				input = argv[3];    //  源文件名test.txt
			if (strcmp(argv[4], "-o") == 0)
				output = argv[5];   //  目标文件名test1.txt
			if (input && output)
				MS::getInstance()->encodePDF(input, output);
		}
		else if (strcmp(argv[1], "-decode") == 0)
		{//解密
			if (strcmp(argv[2], "-i") == 0)
				input = argv[3];
			if (strcmp(argv[4], "-o") == 0)
				output = argv[5];
			if (input && output)
				MS::getInstance()->decodePDF(input, output);
		}
		else
		{
			printf("请输入操作类型！");
		}

		if (input == nullptr || output == nullptr)
			printf("请输入正确参数！");
	}


	system("pause");

	return 0;
}


/*
使用的方式就非常简单了，主要是两个方法：
加密 ：MS::getInstance()->encodePDF(input, output);
解密 ：MS::getInstance()->decodePDF(input, output);
*/