#include "memaligned.h"

#include <stdlib.h>

#ifdef __cplusplus
extern "C"{
#endif

void * malloc_aligned(const size_t size, const size_t alignment)
{
#if defined WIN32           // WIN32
    return _aligned_malloc(size, alignment);
#elif defined __linux__     // Linux
    return memalign(alignment, size);
#elif defined __MACH__      // Mac OS X
    return malloc(size);
#else                       // other (use valloc for page-aligned memory)
    return valloc(size);
#endif
}


void free_aligned(void* mem)
{
#if defined WIN32           // WIN32
    _aligned_free(mem);
#else
    free(mem);
#endif
}


#ifdef __cplusplus
}
#endif
