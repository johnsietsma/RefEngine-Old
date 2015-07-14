#include "memaligned.h"

#if defined WIN32           // WIN32
#include <crtdbg.h>
#else
#include <stdlib.h>
#endif

#include <assert.h>
#include <new>


#ifdef __cplusplus
extern "C"{
#endif

void * aligned_malloc(const size_t size, const size_t alignment)
{
	assert(((alignment)&(alignment - 1)) == 0);

#if defined WIN32           // WIN32
    return _aligned_malloc_dbg(size, alignment, __FILE__, __LINE__);
#elif defined __linux__     // Linux
    return memalign(alignment, size);
#elif defined __MACH__      // Mac OS X
	// TODO Add alignment
    return malloc(size);
#else                       // other (use valloc for page-aligned memory)
    return valloc(size);
#endif
}


void aligned_free(void* mem)
{
	if (mem == NULL) return;
#if defined WIN32           // WIN32
    _aligned_free_dbg(mem);
#else
    free(mem);
#endif
}


#ifdef __cplusplus
}
#endif



void* aligned_new(const size_t size, size_t alignment)
{
	void* p = aligned_malloc(size, alignment);
	if (!p){
		std::bad_alloc ba;
		throw ba;
	}
	return p;
}

void aligned_delete(void* p)
{
	aligned_free(p);
}


void* aligned_new_array(const size_t size, size_t alignment)
{
	void* p = aligned_malloc(size + alignment, alignment);
	if (!p){
		std::bad_alloc ba;
		throw ba;
	}
	return (void *)((intptr_t)p + alignment - sizeof(size_t));;
}

void aligned_delete_array(void* p, size_t alignment )
{
	if (p == nullptr) return;
	void* ret = (void *)((intptr_t)p - alignment + sizeof(size_t));
	aligned_free(ret);
}
