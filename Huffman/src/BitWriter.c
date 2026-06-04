#include "bitWriter.h"
#include <stdlib.h>

struct BitWriter {
    FILE    *f;
    uint8_t  buffer;
    uint8_t  bitCount;
};

BitWriter *createBitWriter(FILE *f) {
    BitWriter *bw = malloc(sizeof(BitWriter));
    bw->f        = f;
    bw->buffer   = 0;
    bw->bitCount = 0;
    return bw;
}

void writeBit(BitWriter *bw, int bit) {
    bw->buffer = (bw->buffer << 1) | (bit & 1);
    bw->bitCount++;
    if (bw->bitCount == 8) {
        fwrite(&bw->buffer, 1, 1, bw->f);
        bw->buffer   = 0;
        bw->bitCount = 0;
    }
}

void writeByte(BitWriter *bw, uint8_t byte) {
    for (int i = 7; i >= 0; i--)
        writeBit(bw, (byte >> i) & 1);
}

void writeBits(BitWriter *bw, uint64_t code, uint8_t len) {
    for (int i = len - 1; i >= 0; i--)
        writeBit(bw, (code >> i) & 1);
}

void flushBitWriter(BitWriter *bw) {
    if (bw->bitCount > 0) {
        bw->buffer <<= (8 - bw->bitCount);
        fwrite(&bw->buffer, 1, 1, bw->f);
    }
}

void destroyBitWriter(BitWriter *bw) {
    free(bw);
}