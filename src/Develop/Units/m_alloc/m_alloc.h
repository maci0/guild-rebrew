#ifndef M_ALLOC_H
#define M_ALLOC_H

#include "../../game_common.h"

/* Memory Allocation Functions */
extern void* __cdecl m_AllocTracked(unsigned int size, const char* tag);
extern void __cdecl m_FreeTracked(void* ptr);

/* Pool Functions */
extern void* __cdecl m_PoolAlloc(void* head, int size, int max_items);
extern void __cdecl m_PoolFree(void* pool, void* item);

#endif /* M_ALLOC_H */
