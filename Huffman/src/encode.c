#include "encode.h"
#include "HuffNode.h"
#include "HuffMinHeap.h"
#include "HuffTree.h"
#include "binaryTree.h"
#include "bitWriter.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static void buildFrequencyTable(const char *input,unsigned int freq[256]){
    FILE *file = fopen(input,"rb"); // opens the file
    memset(freq, 0, sizeof(unsigned int) * 256);

    int c;
    while ((c = fgetc(file)) != EOF) // write frequency of each character to the table
        freq[c]++; 
    fclose(file); // close the file
}

static void buildCodeTable(Node *node, uint64_t code,uint8_t len, uint64_t codes[256], uint8_t lengths[256]){
    if (!node) return;
    HuffNode *hn = (HuffNode *)getData(node);
    printf("hn: %p left: %p right: %p\n", (void*)hn, (void*)getLeft(node), (void*)getRight(node));
    if (!hn) return;

    if (!getLeft(node) && !getRight(node)) { // stores the code on the leaf nodes
        codes[hn->byte] = code;
        lengths[hn->byte] = len;
        return;
    }
    
    // walk the tree if not at leaf nodes yet
    buildCodeTable(getLeft(node),  (code << 1) | 0,len + 1, codes, lengths);
    buildCodeTable(getRight(node), (code << 1) | 1,len + 1, codes, lengths);
}

static void serialiseTree(Node *node,BitWriter *bw){
    if (!node) return;
    HuffNode *hn = (HuffNode *)getData(node);
    if (!getLeft(node) && !getRight(node)) { // checks if we are at the leaf
        writeBit(bw, 1);
        writeByte(bw, hn->byte); //byte value
        return;
    }
    writeBit(bw, 0);
    serialiseTree(getLeft(node), bw);
    serialiseTree(getRight(node), bw);
}

void encode(const char *input,const char *output){
    char outName[512];
    snprintf(outName, sizeof(outName), "%s.HUFF", output);
    unsigned int freq[256];
    buildFrequencyTable(input, freq);

    Heap *heap = createHeap(256);
    printf("heap created\n");
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            HuffNode *node = createHuffNode((uint8_t)i, freq[i]);
            insertNode(heap, node);
        }
    }

    BT *tree = buildHuffTree(heap);


    uint64_t codes[256] = {0};
    uint8_t lengths[256] = {0};

    buildCodeTable(getRoot(tree),0, 0, codes,lengths);

    FILE *out = fopen(outName, "wb");

    FILE *in = fopen(input, "rb");
    fseek(in, 0, SEEK_END);
    uint32_t fileSize = ftell(in);
    rewind(in);
    fwrite(&fileSize, sizeof(uint32_t), 1, out);

    BitWriter *bw = createBitWriter(out);
    serialiseTree(getRoot(tree), bw);

    int c;
    while ((c = fgetc(in)) != EOF)
        writeBits(bw, codes[c], lengths[c]);

    flushBitWriter(bw);
    destroyBitWriter(bw);
    fclose(in);
    fclose(out);
    destroyHeap(heap);
    destroyTree(tree);

}