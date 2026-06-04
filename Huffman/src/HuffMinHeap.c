#include "HuffMinHeap.h"
#include <stdlib.h>

struct Heap {
    HuffNode **nodes;
    int size;
    int capacity;
};

Heap *createHeap(int capacity) {
    Heap *heap = malloc(sizeof(Heap));
    heap->nodes = malloc(sizeof(HuffNode *) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

static void swapNodes(Heap *heap, int a, int b) {
    HuffNode *temp = heap->nodes[a];
    heap->nodes[a] = heap->nodes[b];
    heap->nodes[b] = temp;
}

static void heapifyUp(Heap *heap, int i) {
    int parent = (i - 1) / 2;
    while (i > 0 && heap->nodes[i]->freq < heap->nodes[parent]->freq) {
        swapNodes(heap, i, parent);
        i = parent;
        parent = (i - 1) / 2;
    }
}

static void heapifyDown(Heap *heap, int i) {
    int left  = 2 * i + 1;
    int right = 2 * i + 2;
    int smallest = i;

    if (left  < heap->size && heap->nodes[left]->freq  < heap->nodes[smallest]->freq)
        smallest = left;
    if (right < heap->size && heap->nodes[right]->freq < heap->nodes[smallest]->freq)
        smallest = right;

    if (smallest != i) {
        swapNodes(heap, i, smallest);
        heapifyDown(heap, smallest);
    }
}

void insertNode(Heap *heap, HuffNode *node) {
    heap->nodes[heap->size] = node;
    heapifyUp(heap, heap->size);
    heap->size++;
}

HuffNode *extractMin(Heap *heap) {
    if (heap->size == 0) return NULL;

    HuffNode *min = heap->nodes[0];
    heap->nodes[0] = heap->nodes[heap->size - 1];
    heap->size--;
    heapifyDown(heap, 0);
    return min;
}

int heapSize(Heap *heap) {
    return heap->size;
}

void destroyHeap(Heap *heap) {
    free(heap->nodes);
    free(heap);
}