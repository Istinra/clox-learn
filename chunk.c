#include "chunk.h"

#include <iso646.h>
#include <stdlib.h>
#include <string.h>

#include "memory.h"

void initChunk(Chunk *chunk) {
    chunk->count = 0;
    chunk->len = 0;
    chunk->code = nullptr;
    chunk->linesCount = 0;
    chunk->linesLen = 0;
    chunk->lines = nullptr;
    initValueArray(&chunk->constants);
}

void writeChunk(Chunk *chunk, uint8_t byte, int line) {
    if (chunk->count > chunk->len - 1) {
        const int originalLen = chunk->len;
        chunk->len = GROW_CAPACITY(chunk->len);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code,
                                 originalLen, chunk->len);
    }
    if (chunk->linesLen > 0 && chunk->lines[chunk->linesCount - 1] == line) {
        chunk->lines[chunk->linesCount - 2]++;
    } else {
        if (chunk->linesCount > chunk->linesLen - 2) {
            const int originalLen = chunk->linesLen;
            chunk->linesLen = GROW_CAPACITY(chunk->linesLen);
            chunk->lines = (int *) GROW_ARRAY(int, chunk->lines,
                                              originalLen, chunk->linesLen);
        }
        chunk->lines[chunk->linesCount] = 1;
        chunk->lines[chunk->linesCount + 1] = line;
        chunk->linesCount += 2;
    }
    chunk->code[chunk->count] = byte;
    chunk->count++;
}

void freeChunk(Chunk *chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->len);
    FREE_ARRAY(int, chunk->lines, chunk->linesLen);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

int addConstant(Chunk *chunk, Value value) {
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}
