#include <stdio.h>
#include <stdlib.h>

struct BinTree_node
{
	unsigned char elem;
	struct BinTree_node *ltree, *rtree;
	int lflag, rflag;  // 标志位
};

struct BinTree_node *pre = NULL;

void pre_order(struct BinTree_node *tree);
void in_order(struct BinTree_node *tree);
void pos_order(struct BinTree_node *tree);

struct BinTree_node *create_bintree(void); //ask_method
struct BinTree_node *Create_BinTree(void); //fill_blank_method
void In_order_Thread(struct BinTree_node *tree);
void Create_Inorder_Thread(struct BinTree_node *T);
void Traverse_Inorder_Thread(struct BinTree_node *tree);
struct BinTree_node *Search_Inorder_Thread(struct BinTree_node *tree, char ch);
struct BinTree_node *Prenode_Inorder_Thread(const struct BinTree_node *node);
struct BinTree_node *Succnode_Inorder_Thread(const struct BinTree_node *node);

int main(void)
{
	struct BinTree_node *mytree;
	char ch;
	struct BinTree_node *node, *precursor, *succeed;

	printf("Please input a preorder binary tree(with fill blank #):\n");
	mytree = Create_BinTree();  //使用补空法
	pre_order(mytree); //先序遍历一下,查看.
	printf("\n");

	Create_Inorder_Thread(mytree);  // 调用创建
	printf("Traverse Inorder_Thread Tree:");
	Traverse_Inorder_Thread(mytree);  // 调用遍历中序线索化
	printf("\n");

	printf("Please enter the node that you want to find it's pre & succ node:\n");  // 输入你要找的节点
	while((ch = getchar()) == '\n');   // 干掉回车
	node = Search_Inorder_Thread(mytree, ch);

	precursor = Prenode_Inorder_Thread(node);  //  调用找前驱点的函数
	if(precursor == NULL) // 如果有
		printf("node %c has no precursor node\n", node->elem);// 打印一下找到的node 的前驱点
	else
		printf("Precursor node = %c\n", precursor->elem);

	succeed = Succnode_Inorder_Thread(node);
	if(succeed == NULL)
		printf("node %c has not succeed node\n", node->elem);
	else
		printf("Succeed node = %c\n", succeed->elem);

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

struct BinTree_node *Create_BinTree(void) //fill_blank_method
{
	char ch;
	struct BinTree_node *tree;

	scanf("%c", &ch);

	if(ch == '#')
		tree = NULL;
	else
	{
		tree = (struct BinTree_node *)malloc(sizeof(struct BinTree_node));
		tree->elem = ch;
		tree->ltree = Create_BinTree();
		tree->rtree = Create_BinTree();
	}

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
//中序线索化
void In_order_Thread(struct BinTree_node *tree)
{
	if(tree)
	{
		//1.Do_Inorder_Thread to ltree
		In_order_Thread(tree->ltree);  //中序线索化左子树

		//2.Deal with current node, 
		if(!tree->ltree)  // 没有左子树
		{
			tree->lflag = 1;  //更新标志位
			//current node's ltree points to the pre node //当前节点的树指向前驱点
			tree->ltree = pre;
		}
		else
			tree->lflag = 0;


		if(pre)  // 如果有前驱点
		{
			if(!pre->rtree)  // 如果当前的前驱点右子树
			{
				pre->rflag = 1;
				pre->rtree = tree; // 指向当前操作的那点
			}
			else
				pre->rflag = 0;
		}
		pre = tree; // 更新前驱点的位置,最终指向最后的点.tree的位置通过递归的方式更新的

		//3.Do_Inorder_Thread to rtree
		In_order_Thread(tree->rtree); //中序线索化右子树
	}
}
//创建中序线索化二叉树
void Create_Inorder_Thread(struct BinTree_node *T)
{
	if(T) // 判断二叉树存在
	{
		In_order_Thread(T);  //中序创建
		// 最终节点的:
		pre->rtree = NULL;
		pre->rflag = 1;
	}
}
//遍历中序线索化
void Traverse_Inorder_Thread(struct BinTree_node *tree)
{
	while(tree)
	{
		while(tree->lflag == 0)  // 一直往下找左子树,找前的左子树
			tree = tree->ltree;  //更新内容
		printf("%c ", tree->elem);  //打印一下

		while((tree->rflag == 1) && (tree->rtree))  // tree->rtree表示后继节点为空
		{
			tree = tree->rtree;  // 找到后继节点
			printf("%c ", tree->elem);
		}
		tree = tree->rtree;
	} 
}
//查找中序线索化
struct BinTree_node *Search_Inorder_Thread(struct BinTree_node *tree, char ch)
{
	while(tree)
	{	//在前驱点里找
		while(tree->lflag == 0)  // 一直更新找到最左下的
			tree = tree->ltree;
		if(tree->elem == ch)  // 如果当前的节点就是要找的就直接返回当前节点
			return tree;
		// 在后继节点找
		while((tree->rflag == 1) && (tree->rtree))
		{
			tree = tree->rtree;
			if(tree->elem == ch)  // 如果当前的节点就是要找的就直接返回当前节点
				return tree;
		}
		tree = tree->rtree;
	} 	
}
//找前驱点
struct BinTree_node *Prenode_Inorder_Thread(const struct BinTree_node *node)   // const 用的时候不能改,因为改了再找后继就不对了
{
	struct BinTree_node *nd;

	if(node->lflag == 1) //左子树指向的是前驱点
		return node->ltree;  // 以为当前左子树的指针域就是指向前驱点的
	else
	{// 没有前驱点则当前节点左子树最右下的
		nd = node->ltree;
		while(nd->rflag == 0)
			nd = nd->rtree;
		return nd;
	}
}
//找后继点
struct BinTree_node *Succnode_Inorder_Thread(const struct BinTree_node *node)
{
	struct BinTree_node *nd;

	if(node->rflag == 1)  //右子树指向的是后继点
		return node->rtree;
	else
	{// 没有后继点则当前节点右子树最左下的
		nd = node->rtree;
		while(nd->lflag == 0)
			nd = nd->ltree;
		return nd;
	}
}
