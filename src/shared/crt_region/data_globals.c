/* data_globals.c — GROUP C: CRT-startup + allocator-pool data globals.
 *
 * Plain C definitions for the game's global data objects that the
 * crt_region functions reference as externs.  Each // DATA: marker pins
 * the symbol to its original VA (rebrew DATA mechanism; NAME/SECTION live
 * in src/rebrew-data.toml).  rebrew postlink converges the linked layout
 * onto the reference (copies the reference's .data raw bytes, rewrites
 * .text data operands to reference values), so these definitions mainly
 * need to make the link resolve; leaving them uninitialized keeps them in
 * .bss (zero raw bytes, the PE stays at the reference's raw .data size).
 *
 * Types follow the byte-verified extern declarations in this directory
 * (crt_init.c, dllmain.c, malloc.c, free.c, realloc.c, lock_streams.c,
 * mlock.c): _osver/b8/bc/c0 are unsigned — __CRT_INIT shifts them
 * with SHR in the reference; g_11767588 is the DllMain user-handler
 * fnptr; locktable holds CRITICAL_SECTION* entries; g_lock_stream_table
 * anchors the stream lock-pointer table (lock index math uses its
 * address, reference VAs 0x100317f8..0x10031a58).
 */
#include <windows.h>
#include "rebrew_types.h"

// DATA: SERVER 0x100317d8
void* _FPinit;          /* first init fnptr */
// DATA: SERVER 0x100317f0
void (__cdecl* g_100317f0)(int); /* _exit hook fnptr */
// DATA: SERVER 0x100317f8
char g_lock_stream_table;  /* stream lock-pointer table anchor */

// DATA: SERVER 0x10031aac
/* 48 entries, not 64: the reference's own cleanup loop bounds this array with
 * `cmp esi,0x10031b6c; jl` (0x1001d00b), i.e. 0x10031aac + 0xc0 = 192 bytes.
 * Confirmed by a second method -- the only base+NN immediates in .text are
 * +0x0, +0xc0 (the bound) and +0xd0 (the next object); no +0x100 appears.  A
 * [0x40] spelling would overlap __tlsindex at 0x10031b6c. */
CRITICAL_SECTION* locktable[0x30]; /* per-lock CRITICAL_SECTION ptrs (48) */

/* --- additional globals referenced by the crt_region CRT-startup and
 * allocator functions (data_restore.c covers the .data raw gap; these live
 * in .bss and are pinned here so the .text data operands converge). --- */

// DATA: SERVER 0x10031b6c
int __tlsindex;            /* TLS index (__tlsindex) */
// DATA: SERVER 0x10031b78
char g_old_sbh_region_head;           /* block allocator region-list head node */
// DATA: SERVER 0x10033b9c
unsigned int g_10033b9c;   /* block alloc threshold (mode 2) */

// DATA: SERVER 0x10033ef0
// SIZE 0x8
struct rterr_entry g_rterrlist[18];
// DATA: SERVER 0x100354b4
unsigned int _osver;   /* OS version dword (GetVersion) */
// DATA: SERVER 0x100354b8
unsigned int _winver;   /* (major << 8) | minor */
// DATA: SERVER 0x100354bc
unsigned int _winmajor;   /* OS major */
// DATA: SERVER 0x100354c0
unsigned int _winminor;   /* OS minor */
// DATA: SERVER 0x100354c4
int __argc;            /* __argc */
// DATA: SERVER 0x100354c8
char** __argv;          /* __argv */
// DATA: SERVER 0x100354d0
char** __envp;          /* __envp */
// DATA: SERVER 0x100354e0
char* _pgmptr;           /* _pgmptr */
// DATA: SERVER 0x100354e8
char g_100354e8;           /* 0x1001bb4c tail flag */
// DATA: SERVER 0x100354ec
int _C_Termination_Done;            /* _cexit-already-ran flag */
// DATA: SERVER 0x100354fc
int __proc_attached;            /* __CRT_INIT attach/detach refcount */
// DATA: SERVER 0x10035500
void* _aenvptr;          /* environment strings ptr */
// DATA: SERVER 0x10035508
int __error_mode;            /* __amsg_exit report-mode flag */
// DATA: SERVER 0x1003550c
int __app_type;            /* __amsg_exit report-mode flag 2 */
// DATA: SERVER 0x1003559c
int g_1003559c;            /* new-handler retry flag (_callnewh) */

// DATA: SERVER 0x100355a0
void* g_100355a0;          /* _pnhheap - new-handler fnptr (0x1001d238) */
// DATA: SERVER 0x100355a4
int __old_sbh_decommitable_pages;            /* fully-free page count (SBH) */
// DATA: SERVER 0x100355d8
char g_100355d8[0x104];    /* module filename buffer */
// DATA: SERVER 0x100356dc
int g_100356dc;            /* env mode: 0=uninit, 1=W, 2=A */
// DATA: SERVER 0x100356e0
void (*g_100356e0)(void);  /* _crt_runtime_error user hook (0x1001fdf8) */
// DATA: SERVER 0x10035838
void* pfnMessageBoxA;          /* cached MessageBoxA proc (0x10022107) */
// DATA: SERVER 0x1003583c
void* pfnGetActiveWindow;          /* cached GetActiveWindow proc (0x10022107) */
// DATA: SERVER 0x10035840
void* pfnGetLastActivePopup;          /* cached GetLastActivePopup proc (0x10022107) */
// DATA: SERVER 0x11766438
void* __sbh_pHeaderScan;          /* pool: region scan cursor (ptr into array) */
// DATA: SERVER 0x11766440
int __sbh_cntHeaderList; /* was __sbh_cntHeaderList */            /* pool: region count */
// DATA: SERVER 0x11766444
void* __sbh_pHeaderList; /* was __sbh_pHeaderList */          /* pool: region descriptor array */
// DATA: SERVER 0x11766448
unsigned int g_max_pool_alloc_size;   /* max pool allocation size (mode 3) */
// DATA: SERVER 0x1176644c
void* _crtheap;          /* process heap handle */
// DATA: SERVER 0x11766450
int __active_heap;            /* allocator mode: 3=pool, 2=block */
// DATA: SERVER 0x11766460
int g_11766460[0x40];      /* stream group ptr table (0x11766460..0x1176655c) */
// DATA: SERVER 0x11766560
int __nfile;            /* current stream count */
// DATA: SERVER 0x11766564
void** __pioinfo;         /* tracked-block (stream) table ptr - __flsall/_fcloseall walk this */
// DATA: SERVER 0x11767580
int __nstream;            /* tracked-block table count */
// DATA: SERVER 0x11767584
void* _acmdln;          /* GetCommandLineA result */
// DATA: SERVER 0x11767588
int (__stdcall* g_11767588)(void* hmod, unsigned int reason, void* reserved); /* DllMain user handler */

// DATA: SERVER 0x1176758c
int g_1176758c;            /* __envp built flag */
// DATA: SERVER 0x11767590
int g_11767590;            /* cmdline/env parsed flag */
