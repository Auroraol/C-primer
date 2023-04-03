#include "binary_tree.h"

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

void level_traverse(struct BinTree_node *tree)
{
	struct BinTree_node node;

	enqueue(*tree);

	while(!is_empty())
	{
		node = dequeue();
		printf("%c", node.elem);
		if(node.ltree)
			enqueue(*node.ltree);
		if(node.rtree)
			enqueue(*node.rtree);
	}
}

unsigned int depth(struct BinTree_node *tree)
{
	unsigned int l_depth;
	unsigned int r_depth;

	if(tree == NULL)
		return 0;
	else
	{
		l_depth = depth(tree->ltree);
		r_depth = depth(tree->rtree);

		return (l_depth > r_depth) ? (l_depth + 1) : (r_depth + 1);
	}
}

unsigned int leaf_num(struct BinTree_node *tree)
{
	if(tree == NULL)
		return 0;
	else if((tree->ltree == NULL) && (tree->rtree == NULL))
		return 1;
	else
		return leaf_num(tree->ltree) + leaf_num(tree->rtree);
}

unsigned int node_num(struct BinTree_node *tree)
{
	if(tree == NULL)
		return 0;
	else
		return node_num(tree->ltree) + node_num(tree->rtree) + 1;
}
