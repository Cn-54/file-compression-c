// HuffTree.h
#ifndef HUFFTREE_H
#define HUFFTREE_H

#include <stdint.h>
#include "binaryTree.h"
#include "HuffMinHeap.h"

#include "HuffNode.h"

HuffNode *createHuffNode(uint8_t byte, unsigned int freq);
BT *buildHuffTree(Heap *heap);
void destroyHuffTree(BT *tree);

uint8_t getByte(HuffNode *n);
unsigned int getFreq(HuffNode *n);

#endif