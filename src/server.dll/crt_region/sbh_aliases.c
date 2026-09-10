/* Link-support TU: provides the __sbh_* / _*_sbh_threshold symbol names the
 * reversed LIBCMT heap code references, so sbheap.obj is never pulled into
 * the link (it would import IsBadWritePtr, which the reference does not
 * have). The wrapper bodies forward to the game-VA implementations in
 * sbh_pool.c / crt_heap.c; only the symbols matter. */
// SUPPORT: SERVER LIBCMT sbheap names keep sbheap.obj (IsBadWritePtr import) out of the link

/* Map LIBCMT sbheap public names onto the game's sbh_pool / globals.
 * Without these, the linker pulls LIBCMT:sbheap.obj, which imports
 * IsBadWritePtr — an import the original server.dll does not have. */
#include <windows.h>
#include <stddef.h>

/* Opaque sbh declarations only; full layouts with SIZE markers live in
 * sbh_pool.c / sbh_globals.c (SbhHeader 0x14, OldSbhPage 0x1000,
 * OldSbhRegion 0x2020). */
// SIZE 0x14 (SbhHeader; layout in sbh_pool.c)
typedef struct SbhHeader SbhHeader;
// SIZE 0x1000 (OldSbhPage; layout in sbh_pool.c)
typedef struct __old_sbh_page OldSbhPage;
// SIZE 0x2020 (OldSbhRegion; layout in sbh_pool.c)
typedef struct __old_sbh_region OldSbhRegion;

/* --- game bodies (sbh_pool.c / crt_heap.c) --- */
extern SbhHeader* __cdecl fcn_1001d515(void* pvAlloc);
extern void __cdecl fcn_1001d540(SbhHeader* pHeader, void* pvAlloc);
extern void* __cdecl fcn_1001d869(int intSize);
extern SbhHeader* __cdecl fcn_1001db72(void);
extern int __cdecl fcn_1001dc23(SbhHeader* pHeader);
extern int __cdecl fcn_1001dd1e(SbhHeader* pHeader, void* pvAlloc, int intNew);
extern int __cdecl fcn_1001d4cd(unsigned int size);

extern OldSbhRegion* __cdecl fcn_1001e014(void);
extern void __cdecl fcn_1001e158(OldSbhRegion* preg);
extern void __cdecl fcn_1001e1ae(int count);
extern unsigned char* __cdecl fcn_1001e270(void* pblck, OldSbhRegion** ppreg, OldSbhPage** pppage);
extern void __cdecl fcn_1001e2c7(OldSbhRegion* preg, OldSbhPage* ppage, unsigned char* pmap);
extern void* __cdecl __old_sbh_alloc_block(size_t para_req); /* already LIBCMT-named in sbh_pool.c */
extern void* __cdecl fcn_1001e514(OldSbhPage* ppage, size_t free_para_count, size_t para_req);
extern int __cdecl fcn_1001e638(OldSbhRegion* preg, OldSbhPage* ppage, unsigned char* pmap, size_t new_para_sz);

/* --- game globals (sbh_globals.c / data_globals.c) --- */
extern int __sbh_sizeHeaderList;                 /* __sbh_sizeHeaderList */
extern int __sbh_indGroupDefer;                 /* __sbh_indGroupDefer */
extern void* __sbh_pHeaderScan;               /* __sbh_pHeaderScan */
extern void* __sbh_pHeaderDefer;               /* __sbh_pHeaderDefer */
/* Header-list symbols use LIBCMT names so heapinit.obj resolves without sbheap.obj. */
extern int __sbh_cntHeaderList;        /* was __sbh_cntHeaderList */
extern void* __sbh_pHeaderList;        /* was __sbh_pHeaderList */
extern OldSbhRegion* __old_sbh_p_starting_region;       /* __old_sbh_p_starting_region */
extern int __old_sbh_decommitable_pages;                 /* __old_sbh_decommitable_pages */

/* Threshold / init flags + old-sbh enable flag (LIBCMT data symbols).
 * MSVC6 ignores /alternatename, so these must be real definitions. */
unsigned int __sbh_threshold;
unsigned int __old_sbh_threshold;
int __sbh_initialized;
int __old_small_block_heap;

unsigned int __cdecl _get_sbh_threshold(void)
{
    return __sbh_threshold;
}

int __cdecl _set_sbh_threshold(unsigned int threshold)
{
    if (threshold > 1016)
        return 0;
    __sbh_threshold = threshold;
    return 1;
}

unsigned int __cdecl _get_old_sbh_threshold(void)
{
    return __old_sbh_threshold;
}

int __cdecl _set_old_sbh_threshold(unsigned int threshold)
{
    if (threshold > 1016)
        return 0;
    __old_sbh_threshold = threshold;
    return 1;
}

int __cdecl __sbh_heap_init(unsigned int size)
{
    int ok;
    ok = fcn_1001d4cd(size);
    if (ok)
        __sbh_initialized = 1;
    return ok;
}

SbhHeader* __cdecl __sbh_find_block(void* pvAlloc)
{
    return fcn_1001d515(pvAlloc);
}

void __cdecl __sbh_free_block(SbhHeader* pHeader, void* pvAlloc)
{
    fcn_1001d540(pHeader, pvAlloc);
}

void* __cdecl __sbh_alloc_block(unsigned int size)
{
    return fcn_1001d869((int)size);
}

SbhHeader* __cdecl __sbh_alloc_new_region(void)
{
    return fcn_1001db72();
}

int __cdecl __sbh_alloc_new_group(SbhHeader* pHeader)
{
    return fcn_1001dc23(pHeader);
}

int __cdecl __sbh_resize_block(SbhHeader* pHeader, void* pvAlloc, int intNew)
{
    return fcn_1001dd1e(pHeader, pvAlloc, intNew);
}

int __cdecl __sbh_heapmin(void)
{
    return 0;
}

int __cdecl __sbh_heap_check(void)
{
    return 0;
}

OldSbhRegion* __cdecl __old_sbh_new_region(void)
{
    return fcn_1001e014();
}

void __cdecl __old_sbh_release_region(OldSbhRegion* preg)
{
    fcn_1001e158(preg);
}

void __cdecl __old_sbh_decommit_pages(int count)
{
    fcn_1001e1ae(count);
}

unsigned char* __cdecl __old_sbh_find_block(void* pblck, OldSbhRegion** ppreg, OldSbhPage** pppage)
{
    return fcn_1001e270(pblck, ppreg, pppage);
}

void __cdecl __old_sbh_free_block(OldSbhRegion* preg, OldSbhPage* ppage, unsigned char* pmap)
{
    fcn_1001e2c7(preg, ppage, pmap);
}

void* __cdecl __old_sbh_alloc_block_from_page(OldSbhPage* ppage, size_t free_para_count, size_t para_req)
{
    return fcn_1001e514(ppage, free_para_count, para_req);
}

int __cdecl __old_sbh_resize_block(OldSbhRegion* preg, OldSbhPage* ppage, unsigned char* pmap, size_t new_para_sz)
{
    return fcn_1001e638(preg, ppage, pmap, new_para_sz);
}

int __cdecl __old_sbh_heap_check(void)
{
    return 0;
}
