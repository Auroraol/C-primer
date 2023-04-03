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
		{//����
			printf("	-encode ����\n");
			printf("	-decode ����\n");
			printf("	-i �����ļ�\n");
			printf("	-o ����ļ�\n");
			printf("	example: main.exe -encode -i test.txt -o test1.txt \n");
		}

		if (strcmp(argv[1], "-encode") == 0)
		{//����
			if (strcmp(argv[2], "-i") == 0)
				input = argv[3];    //  Դ�ļ���test.txt
			if (strcmp(argv[4], "-o") == 0)
				output = argv[5];   //  Ŀ���ļ���test1.txt
			if (input && output)
				MS::getInstance()->encodePDF(input, output);
		}
		else if (strcmp(argv[1], "-decode") == 0)
		{//����
			if (strcmp(argv[2], "-i") == 0)
				input = argv[3];
			if (strcmp(argv[4], "-o") == 0)
				output = argv[5];
			if (input && output)
				MS::getInstance()->decodePDF(input, output);
		}
		else
		{
			printf("������������ͣ�");
		}

		if (input == nullptr || output == nullptr)
			printf("��������ȷ������");
	}


	system("pause");

	return 0;
}


/*
ʹ�õķ�ʽ�ͷǳ����ˣ���Ҫ������������
���� ��MS::getInstance()->encodePDF(input, output);
���� ��MS::getInstance()->decodePDF(input, output);
*/