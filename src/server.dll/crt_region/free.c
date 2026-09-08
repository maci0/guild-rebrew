#include <windows.h>

// CFLAGS: /O1 /Gd
// FUNCTION: SERVER 0x1001ab81

/* Game override of CRT free.  mode 3 = pool allocator, mode 2 = block
 * allocator; both take lock 9 and dispatch through the header-walking
 * helpers under __try/__finally.  A non-NULL header means the block
 * belonged to that allocator and the function returns; otherwise the
 * pointer falls through to a HeapFree that reloads it from the parameter
 * slot.  Any other mode frees straight on the process heap from esi.
 *
 * Two properties are load-bearing for the byte match: the two allocator
 * arms share one fall-through HeapFree while the else arm has its own
 * (this is what produces the target's two distinct HeapFree call sites,
 * `push [ebp+8]` and `push esi`), and every local is declared inside the
 * arm that uses it.  Hoisting the locals to function scope reorders the
 * frame slots (ebp-0x1c/-0x24 swap) and costs 4 bytes in every
 * declaration permutation. */

extern void __cdecl _mlock(int);    /* 0x1001d036 */
extern void __cdecl _munlock(int);  /* 0x1001d097 */

extern void* __cdecl fcn_1001d515(void*);            /* 0x1001d515 - header lookup */
extern void __cdecl fcn_1001d540(void*, void*);      /* 0x1001d540 - block free */
extern void* __cdecl fcn_1001e270(void*, void**, int*); /* 0x1001e270 - block header walk */
extern void __cdecl fcn_1001e2c7(void*, int, void*);    /* 0x1001e2c7 - block release */

extern int g_11766450;    /* 0x11766450 - allocator mode: 3=pool, 2=block */
extern void* g_1176644c;  /* 0x1176644c - process heap handle */

void __cdecl free(void* ptr)
{
    if (ptr == NULL)
        return;

    if (g_11766450 == 3)
    {
        void* pHeader;

        _mlock(9);
        __try
        {
            pHeader = fcn_1001d515(ptr);
            if (pHeader != NULL)
                fcn_1001d540(pHeader, ptr);
        }
        __finally
        {
            _munlock(9);
        }
        if (pHeader != NULL)
            return;
    }
    else if (g_11766450 == 2)
    {
        void* pvBlock;
        void* reg;
        int grp;

        _mlock(9);
        __try
        {
            pvBlock = fcn_1001e270(ptr, &reg, &grp);
            if (pvBlock != NULL)
                fcn_1001e2c7(reg, grp, pvBlock);
        }
        __finally
        {
            _munlock(9);
        }
        if (pvBlock != NULL)
            return;
    }
    else
    {
        HeapFree(g_1176644c, 0, ptr);
        return;
    }

    HeapFree(g_1176644c, 0, ptr);
}
