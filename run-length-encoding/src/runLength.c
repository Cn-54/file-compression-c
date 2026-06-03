#include "runLength.h"
#include <stdint.h>
#include <stdio.h>


#include <stdint.h>
#include <stdio.h>

void encode_RLE(FILE *file, const char *output) {
    char outName[512];
    snprintf(outName, sizeof(outName), "%s.rle", output);

    FILE *out = fopen(outName, "wb");
    if (!out) return;

    int c = fgetc(file);
    if (c == EOF) {
        fclose(out);
        return;
    }

    uint8_t key = (uint8_t)c;
    uint16_t count = 1;

    while ((c = fgetc(file)) != EOF) {
        uint8_t byte = (uint8_t)c;

        if (byte == key) {
            count++;
        } else {
            fwrite(&count, sizeof(count), 1, out);
            fwrite(&key, sizeof(key), 1, out);

            key = byte;
            count = 1;
        }
    }

    fwrite(&count, sizeof(count), 1, out);
    fwrite(&key, sizeof(key), 1, out);

    fclose(out);
}

void decode_RLE(FILE *in, const char *output) {

    FILE *out = fopen(output, "wb");
    if (!out) return;

    while (1) {

        uint16_t count;
        uint8_t value;

        size_t r1 = fread(&count, sizeof(count), 1, in);
        if (r1 != 1) break;

        size_t r2 = fread(&value, sizeof(value), 1, in);
        if (r2 != 1) break;

        for (uint16_t i = 0; i < count; i++) {
            fputc(value, out);
        }
    }

    fclose(out);
}