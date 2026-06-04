#include "HuffTree.h"
#include "binaryTree.h"
#include <stdlib.h>


HuffNode *createHuffNode(uint8_t byte, unsigned int freq) {
    HuffNode *node = malloc(sizeof(HuffNode));
    node->byte = byte;
    node->freq = freq;
    node->treeNode = NULL;
    return node;
}

BT *buildHuffTree(Heap *heap) {
    while (heapSize(heap) > 1) {
        HuffNode *left  = extractMin(heap);
        HuffNode *right = extractMin(heap);

        HuffNode *parent = createHuffNode(0, left->freq + right->freq);

        if (!left->treeNode)  left->treeNode  = newNode(left);
        if (!right->treeNode) right->treeNode = newNode(right);

        parent->treeNode = newNode(parent);

        setLeft(parent->treeNode, left->treeNode);
        setRight(parent->treeNode, right->treeNode);

        insertNode(heap, parent);
    }

    HuffNode *root = extractMin(heap);
    BT *tree = createTree();
    setRoot(tree, root->treeNode);
    return tree;
}

void destroyHuffTree(BT *tree) {
    destroyTree(tree);
}