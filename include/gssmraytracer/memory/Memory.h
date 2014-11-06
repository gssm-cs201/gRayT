#ifndef __MEMORY_H__
#define __MEMORY_H__
#include <stddef.h>
#include <stdint.h>
namespace gssmraytracer {
  namespace memory {
    #ifndef GRT_L1_CACHE_LINE_SIZE
    #define GRT_L1_CACHE_LINE_SIZE 64
    #endif

    void *AllocAligned(size_t size);
    void FreeAligned(void *ptr);
    template <typename T> T *AllocAligned(uint32_t count) {
      return (T *)AllocAligned(count * sizeof(T));
    }


  }
}
#endif // __MEMORY_H__
