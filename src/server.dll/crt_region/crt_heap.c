// SUPPORT: SERVER reversed mirror of stock LIBCMT heap-init/term code, compiled to supply the __sbh/heap symbols locally so sbheap.obj stays out of the link (it would import IsBadWritePtr). the 4-byte-larger fcn_1001d280 mirror and the asm strcmp-family fcn_10021200 cannot match in pure C; this file is scaffolding, not reversed game code
#include <windows.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

/* Game's CRT-startup overrides for the heap init/term pair (the binary
 * replaces the LIBCMT crt_heap_init/__heap_term with its own pool/block
 * allocator plumbing).  crt_heap_init creates the process heap and starts
 * the allocator variant selected by fcn_1001d280; __heap_term tears the
 * allocator down and destroys the heap. */

extern int __cdecl fcn_1001d280(void);   /* 0x1001d280 - allocator mode select */
extern int __cdecl fcn_1001d4cd(int);    /* 0x1001d4cd - pool allocator init */
extern int __cdecl fcn_1001e014(void);   /* 0x1001e014 - block allocator init */


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
    _crtheap = HeapCreate(mode == 0, 0x1000, 0);
    if (_crtheap == NULL)
        return 0;
    __active_heap = fcn_1001d280();
    if (__active_heap == 3)
    {
        if (fcn_1001d4cd(0x3f8) == 0)
        {
            HeapDestroy(_crtheap);
            return 0;
        }
    }
    else if (__active_heap == 2)
    {
        if (fcn_1001e014() == 0)
        {
            HeapDestroy(_crtheap);
            return 0;
        }
    }
    return 1;
}

void __cdecl __heap_term(void)
{
    int i;
    pool_region* region;

    if (__active_heap == 3)
    {
        region = (pool_region*)__sbh_pHeaderList;
        for (i = 0; i < __sbh_cntHeaderList; region++, i++)
        {
            VirtualFree(region->base, 0x100000, MEM_DECOMMIT);
            VirtualFree(region->base, 0, MEM_RELEASE);
            HeapFree(_crtheap, 0, region->header);
        }
        HeapFree(_crtheap, 0, __sbh_pHeaderList);
    }
    else if (__active_heap == 2)
    {
        void* node = &g_old_sbh_region_head;
        do
        {
            void* pv = *(void**)((char*)node + 0x10);
            if (pv != NULL)
                VirtualFree(pv, 0, MEM_RELEASE);
            node = *(void**)node;
        } while (node != &g_old_sbh_region_head);
    }
    HeapDestroy(_crtheap);
}

/* _heap_select: returns the allocator mode (3=pool/sbh, 2=block, 1=default).
 * NT5+ hosts return 1 directly; otherwise the __MSVCRT_HEAP_SELECT env var
 * (global select or per-module) is consulted, then the PE linker version
 * (>=6 → 3, else 2). */

extern void __cdecl fcn_1001d253(char*);            /* 0x1001d253 - read PE linker version */
extern int __cdecl fcn_10021200(const char*, const char*, unsigned int); /* 0x10021200 - strncmp */

extern char* __cdecl fcn_1001af30(const char*, int);                     /* 0x1001af30 - strchr */

int __cdecl fcn_1001d280(void)
{
    OSVERSIONINFOA osvi;
    char env[0x1090];
    char module[0x104];
    char major;
    char* env_cursor;
    char* comma;
    int value;
    unsigned int n;

    osvi.dwOSVersionInfoSize = 0x94;
    if (GetVersionExA(&osvi) != 0 && osvi.dwPlatformId == 2 && osvi.dwMajorVersion >= 5)
        return 1;
    if (GetEnvironmentVariableA("__MSVCRT_HEAP_SELECT", env, 0x1090) == 0)
        goto checkver;
    env_cursor = env;
    while (*env_cursor != 0)
    {
        if (*env_cursor >= 'a' && *env_cursor <= 'z')
            *env_cursor -= 0x20;
        env_cursor++;
    }
    if (fcn_10021200("__GLOBAL_HEAP_SELECTED", env, 0x16) == 0)
        env_cursor = env;
    else
    {
        if (GetModuleFileNameA(NULL, module, 0x104) != 0)
        {
            env_cursor = module;
            while (*env_cursor != 0)
            {
                if (*env_cursor >= 'a' && *env_cursor <= 'z')
                    *env_cursor -= 0x20;
                env_cursor++;
            }
            env_cursor = strstr(env, module);
        }
        else
            env_cursor = NULL;
    }
    if (env_cursor != NULL)
    {
        char* region;

        comma = fcn_1001af30(env_cursor, ',');
        if (comma != NULL)
        {
            comma++;
            region = comma;
            while (*region != 0)
            {
                if (*region == ';')
                {
                    *region = 0;
                    break;
                }
                region++;
            }
            value = fcn_10020fe1(comma, NULL, 10);
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


int __cdecl fcn_1001d4cd(unsigned int size)
{
    void* pentry;

    pentry = HeapAlloc(_crtheap, 0, 0x140);
    __sbh_pHeaderList = pentry;
    if (pentry == NULL)
        return 0;
    g_max_pool_alloc_size = size;
    __sbh_pHeaderDefer = 0;
    __sbh_cntHeaderList = 0;
    __sbh_pHeaderScan = pentry;
    __sbh_sizeHeaderList = 0x10;
    return 1;
}

/* crt_get_osver: reads the linker major/minor version from the module's PE
 * header (GetModuleHandleA(NULL)) into the 2-byte buffer. */

void __cdecl fcn_1001d253(char* out)
{
    char* module_base;

    *(int*)out = 0;
    module_base = (char*)GetModuleHandleA(NULL);
    if (*(unsigned short*)module_base == 0x5a4d)
    {
        unsigned int e = *(unsigned int*)(module_base + 0x3c);

        if (e != 0)
        {
            char* pe = module_base + e;

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
