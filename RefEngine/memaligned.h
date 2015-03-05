#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C"{
#endif

void* malloc_aligned(const size_t size, const size_t alignment);
void free_aligned(void * mem);


#ifdef __cplusplus
}
#endif
