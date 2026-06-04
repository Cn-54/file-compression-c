#include <stdio.h>
#include <string.h>
#include "encode.h"

int main(int argc, char *argv[]) {

    if (argc < 4) {
        printf("Usage: %s <compress|decompress> <input> <output>\n", argv[0]);
        return 1;
    }

    const char *type = argv[1];
    const char *input = argv[2];
    const char *output = argv[3];

    if (strcmp(type, "encode") == 0) {
        encode(input, output);
    }
    else{
        printf("unknown mode: %s\n", type);
    }

    return 0;
}