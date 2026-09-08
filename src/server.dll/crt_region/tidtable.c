// CFLAGS: /O1 /Gd
// FUNCTION: SERVER 0x1001d0ac (was FUNCTION; provided by LIBCMT / library_msvc.h)
#include <windows.h>

/* Game's CRT-startup overrides of the per-thread data machinery:
 * __mtinit allocates the TLS slot and the initial _ptd; crt_close_handle
 * frees the TLS slot; __freeptd frees a _ptd and its buffers. */

extern void __cdecl fcn_1001cfa1(void);             /* 0x1001cfa1 - ptd list init */
extern void* __cdecl calloc(unsigned int, unsigned int); /* 0x1001ff84 - calloc */
extern void __cdecl fcn_1001d11e(void*);            /* 0x1001d11e - link ptd into list */
extern void __cdecl fcn_1001cfca(void);             /* 0x1001cfca - ptd list teardown */

extern int g_10031b6c;   /* 0x10031b6c - TLS index (__tlsindex) */

int __cdecl __mtinit(void)
{
    void* ptd;

    fcn_1001cfa1();
    g_10031b6c = TlsAlloc();
    if (g_10031b6c == -1)
        return 0;
    ptd = calloc(1, 0x74);
    if (ptd == NULL)
        return 0;
    if (TlsSetValue(g_10031b6c, ptd))
    {
        fcn_1001d11e(ptd);
        *(int*)ptd = GetCurrentThreadId();
        *(int*)((char*)ptd + 4) = -1;
        return 1;
    }
    return 0;
}

// FUNCTION: SERVER 0x1001d100 (was FUNCTION; provided by LIBCMT / library_msvc.h)

void __cdecl crt_close_handle(void)
{
    fcn_1001cfca();
    if (g_10031b6c != -1)
    {
        TlsFree(g_10031b6c);
        g_10031b6c = -1;
    }
}

// FUNCTION: SERVER 0x1001d198 (was FUNCTION; provided by LIBCMT / library_msvc.h)

extern void __cdecl free(void*);   /* 0x1001ab81 - game free override */

void __cdecl __freeptd(int ptd)
{
    char* p;

    if (g_10031b6c == -1)
        return;
    if (ptd == 0)
        ptd = (int)TlsGetValue(g_10031b6c);
    p = (char*)ptd;
    if (p != NULL)
    {
        if (*(void**)(p + 0x24) != NULL)
            free(*(void**)(p + 0x24));
        if (*(void**)(p + 0x28) != NULL)
            free(*(void**)(p + 0x28));
        if (*(void**)(p + 0x30) != NULL)
            free(*(void**)(p + 0x30));
        if (*(void**)(p + 0x38) != NULL)
            free(*(void**)(p + 0x38));
        if (*(void**)(p + 0x40) != NULL)
            free(*(void**)(p + 0x40));
        if (*(void**)(p + 0x44) != NULL)
            free(*(void**)(p + 0x44));
        if (*(void**)(p + 0x50) != (void*)0x100340a0)
            free(*(void**)(p + 0x50));
        free(p);
    }
    TlsSetValue(g_10031b6c, NULL);
}

// CFLAGS: /O1 /Gd
// FUNCTION: SERVER 0x1001cfa1 (was FUNCTION; provided by LIBCMT / library_msvc.h)

/* __mtinitlocks (game copy): initializes the four static critical sections
 * embedded in the lock-pointer table. */

extern CRITICAL_SECTION* locktable[];   /* 0x10031aac - per-lock CS ptrs */

void __cdecl fcn_1001cfa1(void)
{
    InitializeCriticalSection(locktable[17]);
    InitializeCriticalSection(locktable[13]);
    InitializeCriticalSection(locktable[9]);
    InitializeCriticalSection(locktable[1]);
}

// FUNCTION: SERVER 0x1001cfca (was FUNCTION; provided by LIBCMT / library_msvc.h)

/* __mtdeletelocks (game copy): walks the per-lock CS pointer table
 * (0x10031aac..0x10031b6c), deleting+frees entries except the four static
 * CSs, which are deleted last. */

extern void __cdecl free(void*);   /* 0x1001ab81 - game free override */

void __cdecl fcn_1001cfca(void)
{
    CRITICAL_SECTION** p;

    for (p = locktable; (int)p < (int)&g_10031b6c; p++)
    {
        if (*p != NULL && p != &locktable[17] && p != &locktable[13] &&
            p != &locktable[9] && p != &locktable[1])
        {
            DeleteCriticalSection(*p);
            free(*p);
        }
    }
    DeleteCriticalSection(locktable[9]);
    DeleteCriticalSection(locktable[13]);
    DeleteCriticalSection(locktable[17]);
    DeleteCriticalSection(locktable[1]);
}

// FUNCTION: SERVER 0x1001d11e (was FUNCTION; provided by LIBCMT / library_msvc.h)

/* set_vtable: stamps the _ptd's vtable pointer and refcount. */

void __cdecl fcn_1001d11e(void* ptd)
{
    *(void**)((char*)ptd + 0x50) = (void*)0x100340a0;
    *(int*)((char*)ptd + 0x14) = 1;
}

// FUNCTION: SERVER 0x1001d238 (was FUNCTION; provided by LIBCMT / library_msvc.h)

/* _callnewh: invokes the new-handler (g_100355a0) when installed; returns 1
 * if the handler handled the allocation, else 0. */

extern void* g_100355a0;   /* 0x100355a0 - _pnhheap */

int __cdecl fcn_1001d238(unsigned int size)
{
    if (g_100355a0 != NULL &&
        ((int (__cdecl*)(unsigned int))g_100355a0)(size) != 0)
        return 1;
    return 0;
}

// FUNCTION: SERVER 0x1001ff84 (was FUNCTION; provided by LIBCMT / library_msvc.h)
// SIZE: 153

/* calloc (game copy): rounds the byte count up to 16, dispatches to the
 * pool (mode 3) / block (mode 2) allocators under _mlock(9), falls back to
 * HeapAlloc, and retries via _callnewh. */

extern int g_11766450;            /* 0x11766450 - allocator mode */
extern unsigned int g_11766448;   /* 0x11766448 - max pool size */
extern unsigned int g_10033b9c;   /* 0x10033b9c - block threshold */
extern void* g_1176644c;          /* 0x1176644c - process heap */
extern int g_1003559c;            /* 0x1003559c - new-handler retry flag */
extern void* __cdecl fcn_1001d869(unsigned int);  /* 0x1001d869 - pool alloc */
extern void* __cdecl __old_sbh_alloc_block(unsigned int);  /* 0x1001e30c - block alloc */
extern void* __cdecl fcn_10021240(void*, int, unsigned int); /* 0x10021240 - memset */
extern void __cdecl _mlock(int);
extern void __cdecl _munlock(int);

void* __cdecl calloc(unsigned int num, unsigned int size)
{
    void* result;
    unsigned int bytes;
    int mode;

    size = num * size;
    bytes = size;
    if (size <= 0xFFFFFFE0u)
    {
        if (size == 0)
            size = 1;
        size = (size + 15) & ~15u;
    }
    for (;;)
    {
        result = NULL;
        if (size <= 0xFFFFFFE0u)
        {
            mode = g_11766450;
            if (mode == 3)
            {
                if (bytes <= g_11766448)
                {
                    _mlock(9);
                    __try { result = fcn_1001d869(bytes); }
                    __finally { _munlock(9); }
                    if (result != NULL)
                        fcn_10021240(result, 0, bytes);
                }
            }
            else if (mode == 2)
            {
                if (size <= g_10033b9c)
                {
                    _mlock(9);
                    __try { result = __old_sbh_alloc_block(size >> 4); }
                    __finally { _munlock(9); }
                    if (result != NULL)
                        fcn_10021240(result, 0, size);
                }
            }
            if (result == NULL)
                result = HeapAlloc(g_1176644c, 8, size);
        }
        if (result != NULL)
            return result;
        if (g_1003559c == 0)
            return NULL;
        if (fcn_1001d238(size) == 0)
            return NULL;
    }
}
