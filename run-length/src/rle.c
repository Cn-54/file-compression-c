#include <stdio.h>
#include <string.h>
#include "runLength.h"

int main(int argc, char *argv[]) {

    if (argc < 4) {
        printf("Usage: %s <compress|decompress> <input> <output>\n", argv[0]);
        return 1;
    }

    const char *type = argv[1];
    const char *input = argv[2];
    const char *output = argv[3];

    FILE *file = fopen(input, "rb");
    if (!file) {
        perror("input open failed");
        return 1;
    }

    if (strcmp(type, "compress") == 0) {
        encode_RLE(file, output);
    }
    else if (strcmp(type, "decompress") == 0) {
        decode_RLE(file, output);
    }
    else {
        printf("unknown mode: %s\n", type);
    }

    fclose(file);
    return 0;
}