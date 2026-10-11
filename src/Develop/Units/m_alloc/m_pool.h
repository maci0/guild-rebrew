#ifndef M_POOL_H
#define M_POOL_H

struct M_POOL_BLOCK;
extern void* __cdecl m_pool_next(int* it);
extern void* __cdecl m_pool_first(struct M_POOL_BLOCK* head, int* it);

#endif /* M_POOL_H */
