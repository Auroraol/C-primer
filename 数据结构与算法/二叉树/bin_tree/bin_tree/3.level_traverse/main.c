#include "binary_tree.h"

int main(void)
{
	struct BinTree_node *mytree;

	mytree = create_bintree();

	level_traverse(mytree);

	printf("\n");
	return 0;
}
