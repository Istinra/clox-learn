#ifndef CHUNK_H
#define CHUNK_H

#include "common.h"

typedef enum {
    OP_RETURN
} OpCode;

typedef struct {
    int len;
    int count;
    uint8_t *code;
} Chunk;

void initChunk(Chunk *chunk);
void writeChunk(Chunk* chunk, uint8_t byte);
void freeChunk(Chunk* chunk);


#endif //CHUNK_H
