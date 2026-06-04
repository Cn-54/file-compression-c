#ifndef HUFFNODE_H
#define HUFFNODE_H

#include <stdint.h>
#include "binaryTree.h"

typedef struct HuffNode {
    uint8_t      byte;
    unsigned int freq;
    Node *treeNode;
} HuffNode;

#endif