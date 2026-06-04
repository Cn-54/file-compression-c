// HuffMinHeap.h
#ifndef HUFFMINHEAP_H
#define HUFFMINHEAP_H

#include "HuffNode.h"

typedef struct Heap Heap;

Heap *createHeap(int capacity);
void insertNode(Heap *heap, HuffNode *node);
HuffNode *extractMin(Heap *heap);
int heapSize(Heap *heap);
void destroyHeap(Heap *heap);

#endif