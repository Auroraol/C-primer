#include <stdio.h>
#include <stdlib.h>

struct BinTree_node
{
	unsigned char elem;
	struct BinTree_node *ltree, *rtree;
};

void pre_order(struct BinTree_node *tree);
void in_order(struct BinTree_node *tree);
void pos_order(struct BinTree_node *tree);

struct BinTree_node *create_bintree(void);
struct BinTree_node *pre_in_CreateBinTree(char *pre, char *in, int len);
struct BinTree_node *in_post_CreateBinTree(char *in, char *post, int len);

int main(void)
{
	struct BinTree_node *mytree;

	char pre[100], in[100], post[100];  //  存放 先序,中序,后续 的字符串
	int choose, n;
	
	while (scanf("%d", &choose))  //接受输入的数字
	{
		// 两个选项
		printf("1. Revert BinaryTree through pre & in order:\n");   // 先序+中序的方式  恢复二叉树
		printf("2. Revert BinaryTree through in & post order:\n");  // 先序+中序的方式  恢复二叉树
		switch(choose)
		{
			case 1:
				printf("Please enter the number of nodes:");
				scanf("%d", &n);
				getchar(); //干掉回车
				printf("Please enter the pre order:");
				gets(pre);  //用scanf也行
				printf("Please enter the in order:");
				gets(in);

				mytree = pre_in_CreateBinTree(pre, in, n);  // 恢复的二叉树
				printf("After revert, show the bintree in post order:");
				pos_order(mytree); //以后序的方式打印一下,恢复判断是否正确
				printf("\n");
				break;
			case 2:
				printf("Please enter the number of nodes:");
				scanf("%d", &n);
				getchar();
				printf("Please enter the in order:");
				gets(in);
				printf("Please enter the post order:");
				gets(post);

				mytree = in_post_CreateBinTree(in, post, n);
				printf("After revert, show the bintree in pre order:");
				pre_order(mytree);  //以先序的方式打印一下,恢复判断是否正确
				printf("\n");
				break;
		}
	}
	return 0;
}

struct BinTree_node *create_bintree(void)
{
	unsigned char flag;
	struct BinTree_node *tree;

	tree = (struct BinTree_node *)malloc(sizeof(struct BinTree_node));
	printf("Please input the node elem:\n");
	while((tree->elem = getchar()) == '\n');
	printf("Do you want to insert l_tree for %c, (Y/N)?\n", tree->elem);
	while((flag = getchar()) == '\n');

	if(flag == 'Y')
		tree->ltree = create_bintree();
	else
		tree->ltree = NULL;

	printf("Do you want to insert r_tree for %c, (Y/N)?\n", tree->elem);
	while((flag = getchar()) == '\n');

	if(flag == 'Y')
		tree->rtree = create_bintree();
	else
		tree->rtree = NULL;

	return tree;
}

void pre_order(struct BinTree_node *tree)
{
	if(tree)
	{
		printf("%c", tree->elem);
		pre_order(tree->ltree);
		pre_order(tree->rtree);
	}
}

void in_order(struct BinTree_node *tree)
{
	if(tree)
	{
		in_order(tree->ltree);
		printf("%c", tree->elem);
		in_order(tree->rtree);
	}
}

void pos_order(struct BinTree_node *tree)
{
	if(tree)
	{
		pos_order(tree->ltree);
		pos_order(tree->rtree);
		printf("%c", tree->elem);
	}
}
// 还原遍历二叉树 (先序+中序的方式)
struct BinTree_node *pre_in_CreateBinTree(char *pre, char *in, int len)    // char *pre 先序的字符串, char *in中序的字符串, int len 个数
{
	struct BinTree_node *tree;

	if(len == 0)    //(最后写出来的) 递归退出条件(左右子树长度为零了就结束)
		return NULL;

	char ch = pre[0]; //先序遍历的根节点
	int index = 0; // 索引编号

	while(in[index] != ch)  // 在中序的字符串中找到根节点
		index++;  // 找到编号
	
	tree = (struct BinTree_node *)malloc(sizeof(struct BinTree_node));  //创建一个二叉树
	tree->elem = ch;  // 把找到的总根节点存入
	// 递归去找左右子树的根节点:
	tree->ltree = pre_in_CreateBinTree(pre+1, in, index);  // pre+1 相当于从A到B了() pre+1指针移动  index : 左子树的长度(正好是从中序遍历根节点开始非左右)
	tree->rtree = pre_in_CreateBinTree(pre+index+1, in+index+1, len-index-1);  // pre+index+1 指针移动到右子树的位置   in+index+1 同理   len-index-1 右子树的长度

	return tree;
}
// 还原遍历二叉树 (先序+中序的方式)(中序+后序)
struct BinTree_node *in_post_CreateBinTree(char *in, char *post, int len)
{
	struct BinTree_node *tree;

	if(len == 0) //(最后写出来的) 递归退出条件(左右子树长度为零了就结束)
		return NULL;

	char ch = post[len-1];  //后序遍历的根节点
	int index = 0;
	while(in[index] != ch)   // 在中序的字符串中找到根节点
		index++;

	tree = (struct BinTree_node *)malloc(sizeof(struct BinTree_node));
	tree->elem = ch;
	tree->ltree = in_post_CreateBinTree(in, post, index);   // in 相当于从A开始  index : 左子树的长度(正好是从中序遍历根节点开始非左右)
	tree->rtree = in_post_CreateBinTree(in+index+1, post+index, len-index-1); // in+index+1 指针移动到右子树的位置   post+index 同理   len-index-1 右子树的长度


	return tree;
}
