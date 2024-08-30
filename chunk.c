#include "chunk.h"

#include <iso646.h>
#include <stdlib.h>
#include <string.h>

#include "memory.h"

void initChunk(Chunk *chunk) {
    chunk->count = 0;
    chunk->len = 0;
    chunk->code = nullptr;
}

void writeChunk(Chunk *chunk, uint8_t byte) {
    if (chunk->count > chunk->len - 1) {
        const int originalLen = chunk->len;
        chunk->len = GROW_CAPACITY(chunk->len);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code,
                                 originalLen, chunk->len);
    }
    chunk->code[chunk->count] = byte;
    chunk->count++;
}

void freeChunk(Chunk *chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->len);
    initChunk(chunk);
}
