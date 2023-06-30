#ifndef ORI_ARENA
#define ORI_ARENA
#include "stdlib.h"
#include "stdint.h"



struct Arena {
    uint8_t* region;
    size_t size;
    size_t current;
};

Arena* create_arena(size_t size);

void* arena_malloc(Arena* arena, size_t size);

void arena_reset(Arena* r);

void arena_free(Arena *r);


#endif