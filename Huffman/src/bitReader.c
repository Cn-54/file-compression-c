// bitReader.c
#include "BitReader.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct BitReader {
    FILE *f;
    uint8_t  buffer;
    int      bitCount;
};

BitReader *createBitReader(FILE *f) {
    BitReader *br = malloc(sizeof(BitReader));
    br->f        = f;
    br->buffer   = 0;
    br->bitCount = 0;
    return br;
}

int readBit(BitReader *br) {
    if (br->bitCount == 0) {
        if (fread(&br->buffer, 1, 1, br->f) == 0)
            return -1; 
        br->bitCount = 8;
    }

    int bit = (br->buffer >> (br->bitCount - 1)) & 1;
    br->bitCount--;
    return bit;
}

uint8_t readByte(BitReader *br) {
    uint8_t byte = 0;
    for (int i = 7; i >= 0; i--)
        byte |= (readBit(br) & 1) << i;
    return byte;
}

void destroyBitReader(BitReader *br) {
    free(br);
}