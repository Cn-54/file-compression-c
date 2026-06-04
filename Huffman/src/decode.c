// decode.c
#include "decode.h"
#include "HuffNode.h"
#include "HuffTree.h"
#include "binaryTree.h"
#include "bitReader.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static Node *deserialiseTree(BitReader *br) {
    int bit = readBit(br);

    if (bit == 1) {
        // leaf node
        uint8_t byte = readByte(br);
        HuffNode *hn = createHuffNode(byte, 0);
        return newNode(hn);
    }

    HuffNode *hn = createHuffNode(0, 0);
    Node *node   = newNode(hn);

    Node *left  = deserialiseTree(br);
    Node *right = deserialiseTree(br);

    setLeft(node, left);
    setRight(node, right);

    return node;
}

void decode(const char *input, const char *output) {
    FILE *in = fopen(input, "rb");
    FILE *out = fopen(output, "wb");

    // read original file size from header
    uint32_t fileSize;
    fread(&fileSize, sizeof(uint32_t), 1, in);

    // deserialise tree
    BitReader *br = createBitReader(in);
    Node *root = deserialiseTree(br);

    uint32_t bytesWritten = 0;
    Node *curr = root;

    while (bytesWritten < fileSize) {
        int bit = readBit(br);

        if (bit == 0)
            curr = getLeft(curr);
        else
            curr = getRight(curr);

        if (!getLeft(curr) && !getRight(curr)) {
            HuffNode *hn = (HuffNode *)getData(curr);
            fputc(hn->byte, out);
            bytesWritten++;
            curr = root;
        }
    }

    destroyBitReader(br);
    fclose(in);
    fclose(out);

    BT *tree = createTree();
    setRoot(tree, root);
    destroyTree(tree);
}