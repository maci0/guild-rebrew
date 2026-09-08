#include <windows.h>

// FUNCTION: SERVER 0x1001b5cc (was FUNCTION; provided by LIBCMT / library_msvc.h)
// SIZE: 815

/* Game override of CRT realloc.  Mirrors malloc/free: mode 3 = pool
 * allocator, mode 2 = block allocator (both under lock 9 with header
 * walking); any other mode operates straight on the process heap.
 * Allocation failures retry through the CRT new-handler while the global
 * flag is set.
 *
 * Status: NEAR_MATCHING (805/815).  All 292 instructions match in mnemonic
 * and structure; the residual 10 bytes are stack-slot offsets (compiler
 * homes n2 at ebp-0x1c instead of ebp-0x34, b at ebp-0x34 instead of
 * -0x38, frame 0x24 vs 0x28) and three `je 0x31e`-vs-`je 0x320` branch
 * targets (the retry-loop "return NULL" folds to the epilogue in the
 * original).  Declaration order/scope, types, and /O1..2 flag sweeps were
 * exhausted without closing the gap; the mode-2 copy-size local insists on
 * the top frame slot in every configuration tried. */

extern void* __cdecl malloc(unsigned int);        /* 0x1001a7f7 */
extern void __cdecl free(void*);                  /* 0x1001ab81 */
extern void __cdecl _mlock(int);                  /* 0x1001d036 */
extern void __cdecl _munlock(int);                /* 0x1001d097 */

extern void* __cdecl fcn_1001d515(void*);                 /* 0x1001d515 - header lookup */
extern void __cdecl fcn_1001d540(void*, void*);           /* 0x1001d540 - block free */
extern int __cdecl fcn_1001dd1e(void*, void*, unsigned int); /* 0x1001dd1e - pool grow */
extern void* __cdecl fcn_1001d869(unsigned int);          /* 0x1001d869 - pool block alloc */
extern int __cdecl fcn_1001d238(unsigned int);            /* 0x1001d238 - retry gate */
extern void* __cdecl fcn_1001e270(void*, void**, int*);   /* 0x1001e270 - block header walk */
extern void __cdecl fcn_1001e2c7(void*, int, void*);      /* 0x1001e2c7 - block release */
extern int __cdecl fcn_1001e638(void*, int, void*, unsigned int); /* 0x1001e638 - block grow */
extern void* __cdecl __old_sbh_alloc_block(unsigned int);          /* 0x1001e30c - block alloc */
extern void* __cdecl fcn_1001eab0(void*, void*, unsigned int); /* 0x1001eab0 - memcpy */

extern int g_11766450;             /* 0x11766450 - allocator mode: 3=pool, 2=block */
extern unsigned int g_11766448;    /* 0x11766448 - max pool allocation size */
extern void* g_1176644c;           /* 0x1176644c - process heap handle */
extern int g_1003559c;             /* 0x1003559c - new-handler flag */
extern unsigned int g_10033b9c;    /* 0x10033b9c - block alloc threshold */

void* __cdecl realloc(void* ptr, unsigned int size)
{
    void* newptr;
    void* old;
    unsigned int n3;
    unsigned int n2;

    if (ptr == NULL)
        return malloc(size);
    if (size == 0)
    {
        free(ptr);
        return NULL;
    }

    if (g_11766450 == 3)
    {
        for (;;)
        {
            newptr = NULL;
            if (size <= 0xFFFFFFE0u)
            {
                _mlock(9);
                __try
                {
                    old = fcn_1001d515(ptr);
                    if (old != NULL)
                    {
                        if (size <= g_11766448)
                        {
                            if (fcn_1001dd1e(old, ptr, size))
                                newptr = ptr;
                            else
                            {
                                newptr = fcn_1001d869(size);
                                if (newptr != NULL)
                                {
                                    n3 = ((unsigned int*)ptr)[-1] - 1;
                                    fcn_1001eab0(newptr, ptr, n3 < size ? n3 : size);
                                    old = fcn_1001d515(ptr);
                                    fcn_1001d540(old, ptr);
                                }
                            }
                        }
                        if (newptr == NULL)
                        {
                            if (size == 0)
                                size = 1;
                            size = (size + 0xF) & ~0xF;
                            newptr = HeapAlloc(g_1176644c, 0, size);
                            if (newptr != NULL)
                            {
                                n3 = ((unsigned int*)ptr)[-1] - 1;
                                fcn_1001eab0(newptr, ptr, n3 < size ? n3 : size);
                                fcn_1001d540(old, ptr);
                            }
                        }
                    }
                }
                __finally
                {
                    _munlock(9);
                }
                if (old == NULL)
                {
                    if (size == 0)
                        size = 1;
                    size = (size + 0xF) & ~0xF;
                    newptr = HeapReAlloc(g_1176644c, 0, ptr, size);
                }
            }
            if (newptr != NULL)
                return newptr;
            if (g_1003559c == 0)
                return NULL;
            if (fcn_1001d238(size) == 0)
                return NULL;
        }
    }
    else if (g_11766450 == 2)
    {
        int a;      /* out-param of e270: block mask (ptr & 0xf000) */
        void* b;    /* out-param of e270: block header pointer */
        void* r;    /* e270 return: matched header */

        if (size <= 0xFFFFFFE0u)
        {
            if (size > 0)
                size = (size + 0xF) & ~0xF;
            else
                size = 0x10;
        }
        for (;;)
        {
            newptr = NULL;
            if (size <= 0xFFFFFFE0u)
            {
                _mlock(9);
                __try
                {
                    r = fcn_1001e270(ptr, &b, &a);
                    if (r != NULL)
                    {
                        if (size < g_10033b9c)
                        {
                            if (fcn_1001e638(b, a, r, size >> 4))
                                newptr = ptr;
                            else
                            {
                                newptr = __old_sbh_alloc_block(size >> 4);
                                if (newptr != NULL)
                                {
                                    n2 = (unsigned int)*(unsigned char*)r << 4;
                                    fcn_1001eab0(newptr, ptr, n2 < size ? n2 : size);
                                    fcn_1001e2c7(b, a, r);
                                }
                            }
                        }
                        if (newptr == NULL)
                        {
                            newptr = HeapAlloc(g_1176644c, 0, size);
                            if (newptr != NULL)
                            {
                                n2 = (unsigned int)*(unsigned char*)r << 4;
                                fcn_1001eab0(newptr, ptr, n2 < size ? n2 : size);
                                fcn_1001e2c7(b, a, r);
                            }
                        }
                    }
                    else
                    {
                        newptr = HeapReAlloc(g_1176644c, 0, ptr, size);
                    }
                }
                __finally
                {
                    _munlock(9);
                }
            }
            if (newptr != NULL)
                return newptr;
            if (g_1003559c == 0)
                return NULL;
            if (fcn_1001d238(size) == 0)
                return NULL;
        }
    }
    else
    {
        for (;;)
        {
            newptr = NULL;
            if (size <= 0xFFFFFFE0u)
            {
                if (size == 0)
                    size = 1;
                size = (size + 0xF) & ~0xF;
                newptr = HeapReAlloc(g_1176644c, 0, ptr, size);
            }
            if (newptr != NULL)
                return newptr;
            if (g_1003559c == 0)
                return NULL;
            if (fcn_1001d238(size) == 0)
                return NULL;
        }
    }
}
