// SUPPORT: SERVER reversed mirror of stock LIBCMT heap-init/term code, compiled to supply the __sbh/heap symbols locally so sbheap.obj stays out of the link (it would import IsBadWritePtr). the 4-byte-larger fcn_1001d280 mirror and the asm strcmp-family fcn_10021200 cannot match in pure C; this file is scaffolding, not reversed game code
#include <windows.h>

/* Game's CRT-startup overrides for the heap init/term pair (the binary
 * replaces the LIBCMT crt_heap_init/__heap_term with its own pool/block
 * allocator plumbing).  crt_heap_init creates the process heap and starts
 * the allocator variant selected by fcn_1001d280; __heap_term tears the
 * allocator down and destroys the heap. */

extern int __cdecl fcn_1001d280(void);   /* 0x1001d280 - allocator mode select */
extern int __cdecl fcn_1001d4cd(int);    /* 0x1001d4cd - pool allocator init */
extern int __cdecl fcn_1001e014(void);   /* 0x1001e014 - block allocator init */

extern void* g_1176644c;   /* 0x1176644c - process heap handle */
extern int g_11766450;     /* 0x11766450 - allocator mode: 3=pool, 2=block */
extern int g_11766440;     /* 0x11766440 - pool region count */
extern void* g_11766444;   /* 0x11766444 - pool region descriptor array */
extern void* g_10031b78;   /* 0x10031b78 - block allocator region-list head */

/* 0x14-byte pool region descriptor: base = 1MB VirtualAlloc'd region,
 * header = separately heap-allocated region struct. */
// SIZE 0x14
typedef struct
{
    int field0;
    int field4;
    int field8;
    void* base;    /* 0xc */
    void* header;  /* 0x10 */
} pool_region;

int __cdecl crt_heap_init(int mode)
{
    g_1176644c = HeapCreate(mode == 0, 0x1000, 0);
    if (g_1176644c == NULL)
        return 0;
    g_11766450 = fcn_1001d280();
    if (g_11766450 == 3)
    {
        if (fcn_1001d4cd(0x3f8) == 0)
        {
            HeapDestroy(g_1176644c);
            return 0;
        }
    }
    else if (g_11766450 == 2)
    {
        if (fcn_1001e014() == 0)
        {
            HeapDestroy(g_1176644c);
            return 0;
        }
    }
    return 1;
}

void __cdecl __heap_term(void)
{
    int i;
    pool_region* r;

    if (g_11766450 == 3)
    {
        r = (pool_region*)g_11766444;
        for (i = 0; i < g_11766440; r++, i++)
        {
            VirtualFree(r->base, 0x100000, MEM_DECOMMIT);
            VirtualFree(r->base, 0, MEM_RELEASE);
            HeapFree(g_1176644c, 0, r->header);
        }
        HeapFree(g_1176644c, 0, g_11766444);
    }
    else if (g_11766450 == 2)
    {
        void* node = &g_10031b78;
        do
        {
            void* pv = *(void**)((char*)node + 0x10);
            if (pv != NULL)
                VirtualFree(pv, 0, MEM_RELEASE);
            node = *(void**)node;
        } while (node != &g_10031b78);
    }
    HeapDestroy(g_1176644c);
}

/* _heap_select: returns the allocator mode (3=pool/sbh, 2=block, 1=default).
 * NT5+ hosts return 1 directly; otherwise the __MSVCRT_HEAP_SELECT env var
 * (global select or per-module) is consulted, then the PE linker version
 * (>=6 → 3, else 2). */

extern void __cdecl fcn_1001d253(char*);            /* 0x1001d253 - read PE linker version */
extern int __cdecl fcn_10021200(const char*, const char*, unsigned int); /* 0x10021200 - strncmp */
extern char* __cdecl fcn_1001aff0(const char*, const char*);             /* 0x1001aff0 - strstr */
extern char* __cdecl fcn_1001af30(const char*, int);                     /* 0x1001af30 - strchr */

int __cdecl fcn_1001d280(void)
{
    OSVERSIONINFOA osvi;
    char env[0x1090];
    char module[0x104];
    char major;
    char* p;
    char* q;
    int value;
    unsigned int n;

    osvi.dwOSVersionInfoSize = 0x94;
    if (GetVersionExA(&osvi) != 0 && osvi.dwPlatformId == 2 && osvi.dwMajorVersion >= 5)
        return 1;
    if (GetEnvironmentVariableA("__MSVCRT_HEAP_SELECT", env, 0x1090) == 0)
        goto checkver;
    p = env;
    while (*p != 0)
    {
        if (*p >= 'a' && *p <= 'z')
            *p -= 0x20;
        p++;
    }
    if (fcn_10021200("__GLOBAL_HEAP_SELECTED", env, 0x16) == 0)
        p = env;
    else
    {
        if (GetModuleFileNameA(NULL, module, 0x104) != 0)
        {
            p = module;
            while (*p != 0)
            {
                if (*p >= 'a' && *p <= 'z')
                    *p -= 0x20;
                p++;
            }
            p = fcn_1001aff0(env, module);
        }
        else
            p = NULL;
    }
    if (p != NULL)
    {
        char* r;

        q = fcn_1001af30(p, ',');
        if (q != NULL)
        {
            q++;
            r = q;
            while (*r != 0)
            {
                if (*r == ';')
                {
                    *r = 0;
                    break;
                }
                r++;
            }
            value = fcn_10020fe1(q, NULL, 10);
            if (value == 2 || value == 3 || value == 1)
                return value;
        }
    }
checkver:
    fcn_1001d253(&major);
    if (major >= 6)
        return 3;
    return 2;
}

/* _sbh_heap_init: allocates the region-header table from the process heap
 * and initializes the pool-allocator globals. */

extern void* g_1176644c;   /* process heap handle */
extern void* g_11766444;   /* pool region descriptor array */
extern int g_1176643c;     /* deferred header ptr (low word used) */
extern int g_11766440;     /* pool region count */
extern void* g_11766438;   /* pool region scan cursor */
extern unsigned int g_11766448;  /* max pool allocation size */
extern int g_11766430;     /* pool header-list allocated size */

int __cdecl fcn_1001d4cd(unsigned int size)
{
    void* pentry;

    pentry = HeapAlloc(g_1176644c, 0, 0x140);
    g_11766444 = pentry;
    if (pentry == NULL)
        return 0;
    g_11766448 = size;
    g_1176643c = 0;
    g_11766440 = 0;
    g_11766438 = pentry;
    g_11766430 = 0x10;
    return 1;
}

/* crt_get_osver: reads the linker major/minor version from the module's PE
 * header (GetModuleHandleA(NULL)) into the 2-byte buffer. */

void __cdecl fcn_1001d253(char* out)
{
    char* h;

    *(int*)out = 0;
    h = (char*)GetModuleHandleA(NULL);
    if (*(unsigned short*)h == 0x5a4d)
    {
        unsigned int e = *(unsigned int*)(h + 0x3c);

        if (e != 0)
        {
            char* pe = h + e;

            out[0] = pe[0x1a];
            out[1] = pe[0x1b];
        }
    }
}

/* _strncmp (game copy; functional C equivalent of the asm original). */

int __cdecl fcn_10021200(const char* s1, const char* s2, unsigned int n)
{
    while (n > 0 && *s1 != 0 && *s1 == *s2)
    {
        s1++;
        s2++;
        n--;
    }
    if (n == 0)
        return 0;
    return (unsigned char)*s1 - (unsigned char)*s2;
}

/* strtoul wrapper: forwards to the internal _strtoxl with a NULL locale. */

extern unsigned long __cdecl fcn_10020ff8(const char*, char**, int, void*); /* 0x10020ff8 */

unsigned long __cdecl fcn_10020fe1(const char* str, char** endptr, int base)
{
    return fcn_10020ff8(str, endptr, base, NULL);
}
