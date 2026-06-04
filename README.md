# file-compression-c
A collection of file compression algorithms implemented in C. Each algorithm is a standalone CLI utility with its own build system.

---

## Algorithms

| Algorithm | Status | Best suited for |
|---|---|---|
| Run-Length Encoding (RLE) |  Complete | Files with long runs of repeated bytes |
| Huffman Coding |  complete | General-purpose text and source files |

---

## Project Structure

```
file-compression-c/
    run-length/
        src/
        │   rle.c
        │   runLength.c
        include/
        │   runLength.h
        tests/
        │   hello_world.txt
        │   repeated_text.txt
        │   repeated_text.rle
        Makefile
        compile_flags.txt
        .gitignore
    huffman/
        src/
        │   huffman.c
        │   encode.c
        │   decode.c
        │   HuffTree.c
        │   HuffMinHeap.c
        │   bitWriter.c
        │   bitReader.c
        include/
        │   HuffNode.h
        │   HuffTree.h
        │   HuffMinHeap.h
        │   encode.h
        │   decode.h
        │   bitWriter.h
        │   bitReader.h
        │   binaryTree.h
        lib/
        │   libds.a
        tests/
        Makefile
        compile_flags.txt
        .gitignore
    README.md
```

Each module compiles independently into its own executable.

---

## Run-Length Encoding (RLE)

RLE is a lossless compression algorithm that replaces consecutive repeated bytes with a count and value pair.

```
Input:   AAAAABBBCC
Output:  5A 3B 2C
```

This implementation operates on raw bytes so it works on any file type, not just text.

### Binary Format

Output is a packed binary stream of `(count, value)` pairs:

```
┌──────────────┬─────────────┐
│ uint16_t     │ uint8_t     │
│ count        │ byte value  │
└──────────────┴─────────────┘
```

Repeated for each run until end of file.

### Build

```bash
cd run-length
make
```

Produces: `./rle`

### Usage

**Compress:**
```bash
./rle compress <input> <output>
```

**Decompress:**
```bash
./rle decompress <input.rle> <output>
```

**Example:**
```bash
./rle compress tests/repeated_text.txt tests/output
# → produces tests/output.rle

./rle decompress tests/output.rle tests/restored.txt
# → original file restored
```

### Notes

- All files opened in binary mode (`rb` / `wb`)
- Output file gets `.rle` extension automatically
- Not suited for already-compressed formats (PNG, ZIP, JPEG) as these will not shrink and will expand in size

---

## Huffman Coding

Huffman coding is a lossless compression algorithm that assigns shorter bit codes to more frequent bytes. Built from a min-heap and binary tree, it achieves significantly better compression than RLE on general-purpose data.

### How it works

1. Scan the input file and build a frequency table of all 256 possible byte values
2. Insert all non-zero frequency bytes into a min-heap ordered by frequency
3. Repeatedly extract the two lowest-frequency nodes, combine them into a parent node, and reinsert until one node remains (the root)
4. Walk the tree assigning 0 for left and 1 for right to generate a variable-length code for each byte
5. Write the file header, serialise the tree, then encode the input byte by byte

### File Format

```
┌─────────────┬──────────────────┬──────────────┐
│ uint32_t    │ serialised tree  │ encoded data │
│ file size   │ (pre-order bits) │ (bitstream)  │
└─────────────┴──────────────────┴──────────────┘
```

The tree is serialised in pre-order: `1` followed by the byte value for leaf nodes, `0` for internal nodes. This allows the decoder to reconstruct the exact tree without any additional metadata.

### Dependencies

Huffman links against `libds.a` from [data-structures-C](https://github.com/Cn-54/data-structures-C), which provides the binary tree implementation.

### Build

```bash
cd huffman
make
```

Produces: `./huffman`

### Usage

**Compress:**
```bash
./huffman encode <input> <output>
```

**Decompress:**
```bash
./huffman decode <input.huff> <output>
```

**Example:**
```bash
./huffman encode tests/test.txt tests/test
# → produces tests/test.huff

./huffman decode tests/test.huff tests/restored.txt
# → original file restored
```

### Compression Results

Round-trip verified  `diff` of original and restored file produces no output.

| File | Original | Compressed | Reduction |
|---|---|---|---|
| test.txt (English text) | 2,202 bytes | 1,293 bytes | 41% |

### Notes
- Output file gets `.huff` extension automatically
- Not suited for already compressed formats (PNG, ZIP, JPEG)
- Compression effectiveness depends on byte frequency distribution so files with skewed distributions compress better

---

## Building All Modules

Each module has its own Makefile:

```bash
cd run-length && make
cd huffman && make
```

---
