//哈夫曼压缩编码.cpp :定义控制台应用程序的入口点。
//
// 压缩  打包
// 打包
// 压缩  有损压缩 无损压缩

/*
	从直接存储数据变成用某些编码表示数据例如:

	aabbccddeeff  12B == 96bit
	a  b   c  d   e   f
	1  10  11 110 111 1000

	111010 11111101 10111111 10001000  30bit

	压缩过程优化 ---> 哈夫曼压缩
	哈夫曼树  ---> 最佳搜索树
	数据出现: 有的出现得多 有的出现得少
		比如:不同的数去代表字符时:
			aaaabbbccdef
			1111 1010 1011 1111 0111 1000   24bit

			1000 1000 1000 1000 1111 1111 111011011011101
	故:
	出现次数多的编码位数少
	出现次数少的编码位数多
*/

/*
	哈夫曼压缩解压缩:  1. 编码表示数据  2. 出现次数多编码短出现次数少编码长
*/

/*
四个字节数据 整数 RGB() 消息句柄文件

	1.压缩过程
		待压缩文件
		压缩后文件
		1.1分析待压缩文件 获取文件中出现过的字符和出现次数  组合成字典(索引)

		1.2根据字典创建哈夫曼树 获得每个字符的哈夫曼编码 并存入字典中
			1.2.0 准备个数组，存储所有字符节点
			1.2.1 创建出现次数最小的节点和第二小的节点
			1.2.2 创建空的节点成为1.2.1中两个节点的父节点
			1.2.3   数组中1.2.2中创建的节点覆盖1.2.1中出现次数最小的节点，
					并且数组中 1.2.1中第二小的节点置空
			1.2.4 循环直到数组中所有节点都到了树中为止
		1.3 先把字典写入压缩后文件中
		1.4 根据字典中的编码把待压缩文件中的每个字符的哈夫曼编码写入压缩后文件中
		1.5 关闭两个文件

	2. 解压
		压缩后文件
		解压文件
			2.1 把字典读出来
			2.2 根据字典生成哈夫曼树
			2.3	接着读一个个字节读 然后一个个二进制位分析
				如果是叶子节点，就把对应字符写入解压文件中
			2.4 关闭
*/

#include <iostream>
#include <cstdio>

using namespace std;

// 字符
struct ZiFu
{
	unsigned char zf;    // 字符
	unsigned int count;  // 字符出现的次数
	char code[20];       // 哈夫曼压缩编码
	int idx;             // 在字典中的下标
};

// 字典
struct allZiFu
{
	ZiFu zf_arr[256];
	int zf_count;         //zf_count字典中字符个数
};

//哈夫曼树节点类型
struct treeNode
{
	ZiFu data;
	treeNode* pLeft;
	treeNode* pRight;
	treeNode* pParent;
};

// 数据打开规则
// .doc  用office wPS
// .png .jpeg .jpg
// .txt
// .exe .lib
const char* srcFileName = "1src.txt";
const char* dstFileName = "2dst.txt";
const char* FileName = "2src.txt";
treeNode* pRoot = NULL;

//分析待压缩文件, 获取字典
void analysisFile(const char* fileNaem, allZiFu* zd);
// 创建节点的函数
treeNode* createNode(ZiFu* pZf);
// 根据字典创建哈夫曼树
treeNode* createHaffmanTree(allZiFu* pZd);
//根据哈夫曼树创建哈夫曼编码并写入字典中
void createHaffmanCode(treeNode* root, allZiFu* pZd);  // 遍历树
bool isLeaf(treeNode* root);
void setHaffmannCode(treeNode* root, char* pCodeStr);

// 写压缩后文件(字典, 哈夫曼编码)
void writeCompressed(const char* srcFileName, const char* dstFileName, allZiFu* pZd);
void getHaffmanCode(unsigned char zf, allZiFu* zd, char* pCodeStr);

// 用来测试 analysisFile函数
void _testZd(allZiFu* pZd);

// 分析已压缩, 把字典读出来
void analydstFile(const char* fileNaem, allZiFu* zd);

int main(void)
{
	allZiFu zd;
	memset(&zd, 0, sizeof(struct allZiFu));
	analysisFile(srcFileName, &zd);
	//_testZd(&zd);

	pRoot = createHaffmanTree(&zd);

	createHaffmanCode(pRoot, &zd);
	_testZd(&zd);
	writeCompressed(srcFileName, dstFileName, &zd);
	while (1);
	return 0;
}

//分析待压缩文件
void analysisFile(const char* fileNaem, allZiFu* pZd)
{
	// 1打开文件
	FILE* fp = fopen(fileNaem, "rb");
	if (NULL == fp)
	{
		printf("analysisFile 打开 待压缩文件 %s 失败!\n", fileNaem);
		return;
	}
	// 2循环读取一字节的内容，读到文件末尾停止
	char c;
	int r;
	bool is;
	int i;
	while (1)
	{// 2.1 循环控制
		r = fread(&c, sizeof(char), 1, fp);  // 从文件读取一个字符
		if (1 != r) break;
		// 2.2 统计
		is = false;  // 字符没有出现过
		for (i = 0; i < pZd->zf_count; i++)
		{// 储存到下一个位置
			if (c == pZd->zf_arr[i].zf)
			{
				is = true;
				break;
			}
		}// end of for(i)

		if (!is)  // 如果没有出现过
		{
			pZd->zf_arr[i].zf = c;
			pZd->zf_count++;
		}
		pZd->zf_arr[i].count++;
	}// end of while(1)

	// 3关闭文件
	fclose(fp);
}

// 创建节点的函数
treeNode* createNode(ZiFu* pZf)
{
	treeNode* pNew = new treeNode;
	if (NULL == pNew) return NULL;
	memset(pNew, 0, sizeof(treeNode));
	pNew->data = *pZf;
	// or
	/*memcpy(pNew->data.code, pZf->code, sizeof(char) * 20);
	pNew->data.count = pZf->count;
	pNew->data.zf = pZf->zf;
	*/
	return pNew;
}

// 根据字典创建哈夫曼树
treeNode* createHaffmanTree(allZiFu* pZd)
{
	/*
			1.2.0 准备个数组，存储所有字符节点
			1.2.1 创建出现次数最小的节点 和 第二小的节点
			1.2.2 创建空的节点成为1.2.1中两个节点的父节点
			1.2.3 数组中1.2.2中创建的节点覆盖1.2.1中出现次数最小的节点(在数组中) 并且1.2.1 数组中第二小的节点置空
			1.2.4 循环直到数组中所有节点都到了树中为止
	*/

	// 1.2.0 准备个数组，存储所有字符节点
	treeNode** pArray = new treeNode * [pZd->zf_count];
	treeNode* pTemp = NULL;
	for (int i = 0; i < pZd->zf_count; i++)
	{
		pArray[i] = createNode(&(pZd->zf_arr[i]));
		pArray[i]->data.idx = i;  // 设置下标
	}

	// 1.2.1
	int minIdx, secMinIdx;
	int j;
	//1.2.1.0 循环找最小的和第二小的 循环n-1 次
	for (int i = 0; i < pZd->zf_count - 1; i++)
	{
		//1.2.1.1 找出最小的和第二小的
		// 找出最小的
		// 找到第一个非空
		j = 0;
		while (pArray[j] == NULL) j++;
		minIdx = j;
		for (j = 0; j < pZd->zf_count; j++)
		{
			if (pArray[j] &&
				pArray[j]->data.count < pArray[minIdx]->data.count)
				minIdx = j;
		}
		//找出第二小的，避开minIdx
		j = 0;
		while (pArray[j] == NULL || j == minIdx) j++;
		secMinIdx = j;
		for (j = 0; j < pZd->zf_count; j++)
		{
			if (pArray[j] &&
				j != minIdx &&
				pArray[j]->data.count < pArray[secMinIdx]->data.count)
				secMinIdx = j;
		}

		//1.2.2 创建树
		// 1.2.2.1 创建新节点
		ZiFu tempZf = {0, pArray[minIdx]->data.count + pArray[secMinIdx]->data.count};
		tempZf.idx = -1;
		pTemp = createNode(&tempZf);
		// 1.2.2.2 创建空的节点成为1.2.1中两个节点的父节点
		pArray[minIdx]->pParent = pTemp;
		pArray[secMinIdx]->pParent = pTemp;

		pTemp->pLeft = pArray[minIdx];
		pTemp->pRight = pArray[secMinIdx];

		// 1.2.1.2.3 pTemp覆盖数组中最小的位置 数组中第二小的位置置空
		pArray[minIdx] = pTemp;
		pArray[secMinIdx] = NULL;
	}

	return pTemp;
}

//根据哈夫曼树创建哈夫曼编码并写入字典中  code
void createHaffmanCode(treeNode* root, allZiFu* pZd)
{
	int idx;
	if (root)
	{
		if (isLeaf(root))
		{ //在字典中设置它的哈夫曼编码
			idx = root->data.idx;
			setHaffmannCode(root, pZd->zf_arr[idx].code);
		}
		else
		{
			//遍历左子树
			createHaffmanCode(root->pLeft, pZd);
			//遍历右子树
			createHaffmanCode(root->pRight, pZd);
		}
	}
}

bool isLeaf(treeNode* root)
{
	if (root && NULL == root->pLeft && NULL == root->pRight)
	{
		return true;
	}
	return false;
}

void setHaffmannCode(treeNode* root, char* pCodeStr)
{
	treeNode* pTemp = root;
	// 一路往上追溯判断是其父节点的左孩子还是右孩子，记录下来
	char buff[20] = {0};  // 临时数值
	int buffIdx = 0;      // buff数值下标
	while (pTemp->pParent)
	{
		if (pTemp == pTemp->pParent->pLeft)
		{//是其父节点左孩子
			buff[buffIdx] = 1;
		}
		else
		{//是其父节点右孩子
			buff[buffIdx] = 2;
		}
		buffIdx++;
		pTemp = pTemp->pParent;
	}
	//逆序存储到pCodeStr指向的内存段中
	char temp;
	for (int j = 0; j < buffIdx / 2; j++)
	{
		temp = buff[j];
		buff[j] = buff[buffIdx - j - 1];
		buff[buffIdx - j - 1] = temp;
	}
	// 赋值
	strcpy(pCodeStr, buff);
}

// 写压缩后文件(字典, 哈夫曼编码)
void writeCompressed(const char* srcFileName, const char* dstFileName, allZiFu* pZd)
{
	//1打开两个文件
	FILE* fpSrc = fopen(srcFileName, "rb");
	FILE* fpDst = fopen(dstFileName, "wb");
	if (NULL == fpSrc || NULL == fpDst)
	{
		printf("打开文件失败!\n");
		return;
	}
	// 2. 往dstFileName文件中写入字典
	fwrite(pZd, 1, sizeof(struct allZiFu), fpDst);
	// 3. 循环读取srcFileName文件中的字节 ― 找到其哈夫曼编码 ― 凑齐八个bit写入dstFileName文件中

	int r;  //fread函数返回值
	char c; //从srcFileName中读取的字节存放于此
	char charForwrite;  //用来存储写入dstFileName中的字节数据
	int idxForwrite;    //写入字节的索引
	int haffmanCodeIdx = 0;  //哈夫曼编码下标code数组下标
	char haffmanCode[20] = {0}; // 存储哈夫曼编码
	bool isEnd = false;
	while (1)
	{
		if (haffmanCode[haffmanCodeIdx] == 0)
		{
			r = fread(&c, 1, 1, fpSrc);
			if (1 != r) break;
			getHaffmanCode(c, pZd, haffmanCode);   // 获得对应字符的哈夫曼编码
			haffmanCodeIdx = 0;
		}

#if 0
		// 测试从字典中获取字符的哈夫曼编码
		printf("%c------------", c);
		for (int i = 0; i < 20; i++)
		{
			printf("%d", haffmanCode[i]);
		}
		printf("\n");
#endif // 0

		idxForwrite = 0;
		charForwrite = 0;

		while (idxForwrite < 8)  // 但他等于8时就进行写入
		{
			if (2 == haffmanCode[haffmanCodeIdx])
			{// 设置该位二进制位为0
				charForwrite &= ~(1 << (7 - idxForwrite));
				idxForwrite++;
				haffmanCodeIdx++;
			}
			else if (1 == haffmanCode[haffmanCodeIdx])
			{// 设置该位二进制位为1
				charForwrite |= (1 << (7 - idxForwrite));
				idxForwrite++;
				haffmanCodeIdx++;
			}
			else
			{//不为1 也不为2 当前字符哈夫曼编码操作完毕，读取下一个字符的哈夫曼编码
				r = fread(&c, 1, 1, fpSrc);
				if (1 != r)
				{
					isEnd = true;
					break;
				}

				getHaffmanCode(c, pZd, haffmanCode);
				haffmanCodeIdx = 0;
			}
		}//end of while (idxForwrite < 8)

		fwrite(&charForwrite, 1, 1, fpDst);//往文件中写入一个字节数据

#if 1
		//测试写入到目的文件中的字节是否正确
		for (int i = 0; i < 8; i++)
		{
			if ((charForwrite & 0x80) == 0x80)
				printf("%d", 1);     //0x80: 10000000
			else
				printf("%d", 0);
			charForwrite <<= 1;
		}
		printf("\n");
#endif // 0
		if (isEnd)
			break;
	}// end of whiel(1)

	// 4. 关闭两个文件
	fclose(fpSrc);
	fclose(fpDst);
}

void getHaffmanCode(unsigned char zf, allZiFu* zd, char* pCodeStr)
{
	for (int i = 0; i < zd->zf_count; i++)
	{
		if (zf == zd->zf_arr[i].zf)
			strcpy(pCodeStr, zd->zf_arr[i].code);
	}
}

// 用来测试 analysisFile函数
void _testZd(allZiFu* pZd)
{
	printf(" 待压缩文件中共有%d个字符\n", pZd->zf_count);
	//for (int i = 0; i < pZd->zf_count; i++)
	//{
	//	printf("%c :%d\n", pZd->zf_arr[i].zf, pZd->zf_arr[i].count);
	//}
	int j;
	for (int i = 0; i < pZd->zf_count; i++)
	{
		printf("%c: %d", pZd->zf_arr[i].zf, pZd->zf_arr[i].count);
		j = 0;
		printf(" : code: ");
		while (pZd->zf_arr[i].code[j])
		{
			printf("%d", pZd->zf_arr[i].code[j]);
			j++;
		}
		printf("\n");
	}
}

/*
2.1 把字典读出来
2.2 根据字典生成哈夫曼树
2.3	接着读一个个字节读 然后一个个二进制位分析
如果是叶子节点，就把对应字符写入解压文件中
2.4 关闭
*/
void analydstFile(const char* fileNaem, allZiFu* zd)
{
	//1打开两个文件
	FILE* fpSrc = fopen(dstFileName, "rb");
	FILE* fpDst = fopen(FileName, "wb");
	if (NULL == fpSrc || NULL == fpDst)
	{
		printf("打开文件失败!\n");
		return;
	}

	// 关闭
	fclose(fpDst);
	fclose(fpSrc);
}

/*
abcdefgaaaaabbdess 待压缩文件中共有8个字符
a : 6
b : 3
c : 1
d : 2
e : 2
f : 1
g : 1
s : 2

00010110
11011001
10011100
00000000
01001010
11000110
11000000

*/