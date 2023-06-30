#include "arena_allocator.h"




Arena* create_arena(size_t size){
    Arena* arena = (Arena*) calloc(1, sizeof(Arena));
    if (!arena) return NULL;
    arena->region =  (uint8_t*) calloc(size, sizeof(uint8_t));
    arena->size = size;
    if (!arena->region) {
        free(arena);
        return NULL;
    }
    return arena;
}


void* arena_malloc(Arena* arena, size_t size){
    arena->current += size;
    return arena->region + (arena->current - size);
}

void arena_reset(Arena* r){
    r->current = 0;
}


void arena_free(Arena *r){
    free(r->region);
    free(r);
}