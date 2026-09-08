#include <windows.h>

// CFLAGS: /O1 /Gd
// FUNCTION: SERVER 0x1001a7f7

/* Game override of CRT malloc.  Small allocations are routed through the
 * game's own pool allocator (fcn_1001a835); on failure the CRT new-handler
 * (_callnewh) is consulted once per retry while the global flag is set. */

extern int g_1003559c; /* 0x1003559c - new-handler flag (non-zero enables _callnewh retry) */

void* __cdecl fcn_1001a809(unsigned int size, int f_newh); /* 0x1001a809 */

void* __cdecl malloc(unsigned int size)
{
    return fcn_1001a809(size, g_1003559c);
}

// FUNCTION: SERVER 0x1001a809

extern void* __cdecl fcn_1001a835(unsigned int); /* 0x1001a835 - pool_alloc */
extern int __cdecl _callnewh(unsigned int);      /* CRT new handler invocation */

void* __cdecl fcn_1001a809(unsigned int size, int nhFlag)
{
    void* pvReturn;

    for (; size <= 0xFFFFFFE0u; )
    {
        pvReturn = fcn_1001a835(size);
        if (pvReturn || !nhFlag)
            return pvReturn;
        if (_callnewh(size) == 0)
            return NULL;
    }
    return NULL;
}

// FUNCTION: SERVER 0x1001a835

extern void __cdecl _lock(int);  /* 0x1001d036 -> symbol __lock */
extern void __cdecl _unlock(int); /* 0x1001d097 -> symbol __unlock */
extern void* __cdecl __sbh_alloc_block(unsigned int); /* 0x1001d869 -> ___sbh_alloc_block */
extern void* __cdecl __old_sbh_alloc_block(unsigned int); /* 0x1001e30c - block alloc */

extern int g_11766450;          /* 0x11766450 - allocator mode: 3=pool, 2=block */
extern unsigned int g_11766448; /* 0x11766448 - max pool allocation size */
extern void* g_1176644c;        /* 0x1176644c - process heap handle */
extern unsigned int g_10033b9c; /* 0x10033b9c - block alloc threshold */

void* __cdecl fcn_1001a835(unsigned int size)
{
    void* p;

    if (g_11766450 == 3)
    {
        if (size <= g_11766448)
        {
            _lock(9);
            __try
            {
                p = __sbh_alloc_block(size);
            }
            __finally
            {
                _unlock(9);
            }
            if (p != NULL)
                return p;
        }
    }
    else if (g_11766450 == 2)
    {
        if (size != 0)
            size = (size + 0xF) & ~0xF;
        else
            size = 0x10;

        if (size > g_10033b9c)
            return HeapAlloc(g_1176644c, 0, size);

        _lock(9);
        __try
        {
            p = __old_sbh_alloc_block(size >> 4);
        }
        __finally
        {
            _unlock(9);
        }
        if (p != NULL)
            return p;
        return HeapAlloc(g_1176644c, 0, size);
    }

    if (size == 0)
        size = 1;
    return HeapAlloc(g_1176644c, 0, (size + 0xF) & ~0xF);
}
