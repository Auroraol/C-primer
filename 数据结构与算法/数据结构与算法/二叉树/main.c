#include <stdio.h>
#include <malloc.h>

typedef char BTData;

typedef struct tree
{
	BTData data;
	struct tree* left;
	struct tree* right;

}tree;

// ²¹¿Õ·¨
tree* create()
{
	char val;
	tree* myTree;
	scanf_s("%c", &val);
	if (val == '#')
	{
		myTree = NULL;
	}
	else
	{
		myTree = malloc(sizeof(struct tree));
		if (myTree)
		{
			myTree->data = val;
			myTree->left = create();
			myTree->right = create();
		}
	}
	return myTree;
}

void pre_order(tree* tree)
{
	if (tree)
	{
		printf("%c ", tree->data);
		pre_order(tree->left);
		pre_order(tree->right);
	}
}

int main(void)
{
	tree* tree;
	tree = create();
	pre_order(tree);
	while (1);
	return 0;
}