#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C"{
#endif

// Portable aligned memory allocation/deallocation functions.
void* aligned_malloc(const size_t size, const size_t alignment);
void aligned_free(void * mem);

#ifdef __cplusplus
}
#endif


void* aligned_new(const size_t size, const size_t alignment);
void aligned_delete(void* p);
void* aligned_new_array(const size_t size, size_t alignment);
void aligned_delete_array(void* p, size_t alignment);
