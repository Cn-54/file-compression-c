#ifndef BITREADER_H_
#define BITREADER_H_

#include <stdint.h>
#include <stdio.h>

typedef struct BitReader BitReader;

BitReader *createBitReader(FILE *f);
int readBit(BitReader *br);
uint8_t readByte(BitReader *br);
void destroyBitReader(BitReader *br);

#endif