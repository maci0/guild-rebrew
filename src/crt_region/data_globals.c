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
 * with SHR in the reference; g_dllmain_user_handler is the DllMain user-handler
 * fnptr; locktable holds CRITICAL_SECTION* entries; g_lock_stream_table
 * anchors the stream lock-pointer table (lock index math uses its
 * address, reference VAs 0x100317f8..0x10031a58).
 */
#include <windows.h>
#include "rebrew_types.h"

void* _FPinit;          /* first init fnptr */
void (__cdecl* g_crt_exit_hook)(int); /* _exit hook fnptr */
char g_lock_stream_table;  /* stream lock-pointer table anchor */

/* 48 entries, not 64: the reference's own cleanup loop bounds this array with
 * `cmp esi,0x10031b6c; jl` (0x1001d00b), i.e. 0x10031aac + 0xc0 = 192 bytes.
 * Confirmed by a second method -- the only base+NN immediates in .text are
 * +0x0, +0xc0 (the bound) and +0xd0 (the next object); no +0x100 appears.  A
 * [0x40] spelling would overlap __tlsindex at 0x10031b6c. */
CRITICAL_SECTION* locktable[0x30]; /* per-lock CRITICAL_SECTION ptrs (48) */

/* --- additional globals referenced by the crt_region CRT-startup and
 * allocator functions (data_restore.c covers the .data raw gap; these live
 * in .bss and are pinned here so the .text data operands converge). --- */

int __tlsindex;            /* TLS index (__tlsindex) */
char g_old_sbh_region_head;           /* block allocator region-list head node */
unsigned int g_block_alloc_threshold;   /* block alloc threshold (mode 2) */

// SIZE 0x8
struct rterr_entry g_rterrlist[18];
unsigned int _osver;   /* OS version dword (GetVersion) */
unsigned int _winver;   /* (major << 8) | minor */
unsigned int _winmajor;   /* OS major */
unsigned int _winminor;   /* OS minor */
int __argc;            /* __argc */
char** __argv;          /* __argv */
char** __envp;          /* __envp */
char* _pgmptr;           /* _pgmptr */
char g_crt_exit_tail_flag;           /* 0x1001bb4c tail flag */
int _C_Termination_Done;            /* _cexit-already-ran flag */
int __proc_attached;            /* __CRT_INIT attach/detach refcount */
void* _aenvptr;          /* environment strings ptr */
int __error_mode;            /* __amsg_exit report-mode flag */
int __app_type;            /* __amsg_exit report-mode flag 2 */
int g_new_handler_retry;            /* new-handler retry flag (_callnewh) */

void* g_new_handler;          /* _pnhheap - new-handler fnptr (0x1001d238) */
int __old_sbh_decommitable_pages;            /* fully-free page count (SBH) */
char g_crt_module_filename[0x104];    /* module filename buffer */
int g_crt_env_mode;            /* env mode: 0=uninit, 1=W, 2=A */
void (*g_crt_runtime_error_hook)(void);  /* _crt_runtime_error user hook (0x1001fdf8) */
void* pfnMessageBoxA;          /* cached MessageBoxA proc (0x10022107) */
void* pfnGetActiveWindow;          /* cached GetActiveWindow proc (0x10022107) */
void* pfnGetLastActivePopup;          /* cached GetLastActivePopup proc (0x10022107) */
void* __sbh_pHeaderScan;          /* pool: region scan cursor (ptr into array) */
int __sbh_cntHeaderList = 0; /* pool: region count */
void* __sbh_pHeaderList = 0; /* pool: region descriptor array */
unsigned int g_max_pool_alloc_size;   /* max pool allocation size (mode 3) */
void* _crtheap;          /* process heap handle */
int __active_heap;            /* allocator mode: 3=pool, 2=block */
extern void *__pioinfo[0x40]; /* LIBCMT COMMON ___pioinfo, 64 ioinfo block pointers (0x11766460..0x11766560); the CRT owns it */
int __nfile;            /* current stream count */
extern void **__piob;      /* LIBCMT COMMON ___piob (0x11766564), stream table __flsall/_fcloseall walk; the CRT owns it */
int __nstream;            /* tracked-block table count */
void* _acmdln;          /* GetCommandLineA result */
int (__stdcall* g_dllmain_user_handler)(void* hmod, unsigned int reason, void* reserved); /* DllMain user handler */

int g_envp_built;            /* __envp built flag */
int g_cmdline_parsed;            /* cmdline/env parsed flag */
