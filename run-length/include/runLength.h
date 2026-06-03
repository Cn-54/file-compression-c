#ifndef runLength_H_
#define runLength_H_
#include <stdio.h>

void encode_RLE(FILE *file, const char *output);
void decode_RLE(FILE *file, const char *output);

#endif