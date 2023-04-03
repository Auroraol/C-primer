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

int main(void)
{
	struct BinTree_node *mytree;

	mytree = create_bintree();  //他的返回值是 struct BinTree_node *

//调用遍历
//	pre_order(mytree);
//	in_order(mytree);
	pos_order(mytree);   

	printf("\n");
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
// 先(前)序遍历
void pre_order(struct BinTree_node *tree)
{
	if(tree) //根节点存在
	{
		printf("%c", tree->elem); //显示内容根节点的内容
		pre_order(tree->ltree);   //访问左子树.嵌套
		pre_order(tree->rtree);
	}
}
//中序遍历
void in_order(struct BinTree_node *tree)
{
	if(tree)  //根节点存在
	{
		in_order(tree->ltree);  // 访问左子树.嵌套
		printf("%c", tree->elem); //显示内容根节点的内容
		in_order(tree->rtree);
	}
}
//后序遍历
void pos_order(struct BinTree_node *tree)
{
	if(tree)
	{
		pos_order(tree->ltree);
		pos_order(tree->rtree);
		printf("%c", tree->elem);
	}
}
