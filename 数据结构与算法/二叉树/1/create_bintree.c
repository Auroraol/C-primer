#include <stdio.h>
#include <stdlib.h>

struct BinTree_node 
{
    unsigned char elem;
    struct BinTree_node *ltree, rtree;
};

struct BinTree_node *create_bintree(void);

int main(void)
{
    struct BinTree_node *mytree;
    mytree = ctrete_bintree();
    return 0;
}

struct BinTree_node *create_bintree(void)
{
    unsigned char flag;
    struct BinTree_node *tree;
       
}
