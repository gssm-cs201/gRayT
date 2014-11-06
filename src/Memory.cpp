#include "gssmraytracer/memory/Memory.h"
#include <malloc.h>

namespace gssmraytracer {
  namespace memory {
    // Memory Allocation Functions
    void *AllocAligned(size_t size) {
    #if defined(WIN32)
        return _aligned_malloc(size, GRT_L1_CACHE_LINE_SIZE);
    #elif defined (__OPENBSD__) || defined(__APPLE__)
        // Allocate excess memory to ensure an aligned pointer can be returned
        void *mem = malloc(size + (GRT_L1_CACHE_LINE_SIZE-1) + sizeof(void*));
        char *amem = ((char*)mem) + sizeof(void*);
    #if (GRT_POINTER_SIZE == 8)
        amem += GRT_L1_CACHE_LINE_SIZE - (reinterpret_cast<uint64_t>(amem) &
                                           (GRT_L1_CACHE_LINE_SIZE - 1));
    #else
        amem += GRT_L1_CACHE_LINE_SIZE - (reinterpret_cast<uint32_t>(amem) &
                                           (GRT_L1_CACHE_LINE_SIZE - 1));
    #endif
        ((void**)amem)[-1] = mem;
        return amem;
    #else
        return memalign(GRT_L1_CACHE_LINE_SIZE, size);
    #endif
    }


    void FreeAligned(void *ptr) {
        if (!ptr) return;
    #if defined(WIN32)
        _aligned_free(ptr);
    #elif defined (__OPENBSD__) || defined(__APPLE__)
        free(((void**)ptr)[-1]);
    #else
        free(ptr);
    #endif
    }
  }
}
