#include "grayt/memory/Memory.h"
#include <malloc.h>
#include <vector>

namespace grayt {
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

/*
    class MemoryArena::Impl {
    public:
      uint32_t curBlockPos, blockSize;
      char *currentBlock;
      std::vector<char *> usedBlocks, availableBlocks;
    };

    MemoryArena::MemoryArena(uint32_t bs) : mImpl(new Impl) {
      mImpl->blockSize = bs;
      mImpl->curBlockPos = 0;
      mImpl->currentBlock = AllocAligned<char>(mImpl->blockSize);
    }


    void MemoryArena::FreeAll() {
      mImpl->curBlockPos = 0;
      while (mImpl->usedBlocks.size()) {
        mImpl->availableBlocks.push_back(mImpl->usedBlocks.back());
        mImpl->usedBlocks.pop_back();
      }
    }
    */
  }
}
