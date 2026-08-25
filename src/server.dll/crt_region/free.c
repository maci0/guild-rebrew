#include <windows.h>

// CFLAGS: /O1 /Gd
// FUNCTION: SERVER 0x1001ab81
// SIZE: 233

/* Game override of CRT free.  mode 3 = pool allocator (tracked blocks),
 * mode 2 = block allocator; both paths take lock 9 and call the
 * header-walking helpers; anything else is freed straight on the
 * process heap. */

extern void __cdecl _mlock(int);    /* 0x1001d036 */
extern void __cdecl _munlock(int);  /* 0x1001d097 */

extern void* __cdecl fcn_1001d515(void*);            /* 0x1001d515 - header lookup */
extern void __cdecl fcn_1001d540(void*, void*);      /* 0x1001d540 - block free */
extern unsigned char* __cdecl fcn_1001e270(void*, void**, void**); /* 0x1001e270 - block header walk */
extern void __cdecl fcn_1001e2c7(void*, void*, unsigned char*);    /* 0x1001e2c7 - block release */

extern int g_11766450;    /* 0x11766450 - allocator mode: 3=pool, 2=block */
extern void* g_1176644c;  /* 0x1176644c - process heap handle */

void __cdecl free(void* ptr)
{
    void* r1;
    void* r2;
    int a;
    int b;

    if (ptr == NULL)
        return;

    if (g_11766450 == 3)
    {
        _mlock(9);
        __try
        {
            r1 = fcn_1001d515(ptr);
            if (r1 != NULL)
                fcn_1001d540(r1, ptr);
        }
        __finally
        {
            _munlock(9);
        }
        if (r1 != NULL)
            return;
        HeapFree(g_1176644c, 0, ptr);
    }
    else if (g_11766450 == 2)
    {
        _mlock(9);
        __try
        {
            r2 = fcn_1001e270(ptr, &b, &a);
            if (r2 != NULL)
                fcn_1001e2c7(b, a, r2);
        }
        __finally
        {
            _munlock(9);
        }
        if (r2 != NULL)
            return;
        HeapFree(g_1176644c, 0, ptr);
    }
    else
    {
        HeapFree(g_1176644c, 0, ptr);
    }
}
