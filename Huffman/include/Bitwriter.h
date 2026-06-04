#ifndef BITWRITER_H
#define BITWRITER_H

#include <stdio.h>
#include <stdint.h>

typedef struct BitWriter BitWriter;

BitWriter *createBitWriter(FILE *f);
void writeBit(BitWriter *bw, int bit);
void writeByte(BitWriter *bw, uint8_t byte);
void writeBits(BitWriter *bw, uint64_t code, uint8_t len);
void flushBitWriter(BitWriter *bw);
void destroyBitWriter(BitWriter *bw);

#endif