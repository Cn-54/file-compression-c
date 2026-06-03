# file-compression-c

A collection of file compression algorithms implemented in C. Each algorithm is a standalone CLI utility with its own build system

---

## Algorithms

| Algorithm | Status | Best suited for |
|---|---|---|
| Run-Length Encoding (RLE) |  Complete | Files with long runs of repeated bytes |
| Huffman Coding |  Planned | General-purpose text and source files |

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
        compile_flags.txt (to make sure the clangd error checker seea the headers)
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

This implementation operates on raw bytes — it works on any file type, not just text.

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
- Not suited for already-compressed formats (PNG, ZIP, JPEG) — these types will not shrink and will expand in size
---

## Planned: Huffman Coding

A entropy-based lossless compression algorithm that assigns shorter bit codes to more frequent bytes. More effective than RLE on general-purpose data.

Planned components:
- Min-heap priority queue
- Huffman tree construction
- Bit-level I/O with byte-aligned output
- File header with serialised tree for self-contained decompression

---

## Building All Modules

Each module has its own Makefile. To build everything:

```bash
cd run-length && make
# cd huffman && make   (once implemented)
```

---
