#ifndef M_ALLOC_H
#define M_ALLOC_H

#include "../../game_common.h"

/* Memory Allocation Functions */
extern void* __cdecl AllocateTrackedHeapBlock(int size, char* tag, int line);
extern void __cdecl FreeTrackedHeapBlock(void* ptr);

/* Pool Functions */
extern void* __cdecl pool_alloc(void* pool);
extern void __cdecl pool_free(void* pool, void* ptr);

#endif /* M_ALLOC_H */
