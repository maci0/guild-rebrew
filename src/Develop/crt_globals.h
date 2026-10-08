/* CRT global declarations and reference addresses.
 * Stock LIBCMT owns runtime storage; this header allocates no bytes.
 * Historical analysis names describe views of that library storage.
 */
#ifndef CRT_GLOBALS_H
#define CRT_GLOBALS_H

#include "rebrew_types.h"

/* Verified stock _strupr aliases: TL 0x66080a (MT strupr.obj),
 * Gold 0x5eaad6 (ST strupr.obj). Full native bodies identify the member.
 * Use the SDK declaration; these macros allocate no runtime code/data. */
#include <string.h>
#define fcn_0066080a _strupr
#define fcn_005eaad6 _strupr

extern void * _FPinit; /* 0x100317D8, first init fnptr */
extern char g_lock_stream_table; /* Legacy one-byte view at _iob[0] (0x100317f8); stock FILE[20] owns storage. */
extern struct rterr_entry g_rterrlist[18]; /* 0x10033EF0, _NMSG_WRITE runtime-error table (0x1001fe31) */
extern void (__cdecl *g_crt_exit_hook)(int); /* 0x100317F0, _exit hook fnptr */
extern int __tlsindex; /* 0x10031B6C, TLS index */
extern char g_old_sbh_region_head; /* 0x10031B78, block allocator region-list head node */
extern OldSbhRegion * __old_sbh_p_starting_region; /* 0x10033B98, __old_sbh_p_starting_region (V5 sbh rover) */
extern unsigned int g_block_alloc_threshold; /* 0x10033B9C, block alloc threshold (allocator mode 2) */
extern unsigned int _osver; /* 0x100354B4, OS version dword (GetVersion) */
extern unsigned int _winver; /* 0x100354B8, (major << 8) | minor */
extern unsigned int _winmajor; /* 0x100354BC, OS major */
extern unsigned int _winminor; /* 0x100354C0, OS minor */
extern int __argc; /* 0x100354C4 */
extern char** __argv; /* 0x100354C8 */
extern char** __envp; /* 0x100354D0 */
extern char* _pgmptr; /* 0x100354E0 */
extern char g_crt_exit_tail_flag; /* 0x100354E8, 0x1001bb4c tail flag */
extern int _C_Termination_Done; /* 0x100354EC, _cexit-already-ran flag */
extern int __proc_attached; /* 0x100354FC, __CRT_INIT attach/detach refcount */
extern void * _aenvptr; /* 0x10035500, environment strings ptr */
extern int __error_mode; /* 0x10035508, __amsg_exit report-mode flag */
extern int __app_type; /* 0x1003550C, __amsg_exit report-mode flag 2 */
extern int g_new_handler_retry; /* 0x1003559C, new-handler retry flag (_callnewh) */
extern void * g_new_handler; /* 0x100355A0, _pnhheap new-handler fnptr (0x1001d238) */
extern int __old_sbh_decommitable_pages; /* 0x100355A4, fully-free page count (SBH) */
extern char g_crt_module_filename[0x104]; /* 0x100355D8, module filename buffer (0x104) */
extern int g_crt_env_mode; /* 0x100356DC, env mode: 0=uninit, 1=W, 2=A */
extern void (*g_crt_runtime_error_hook)(void); /* 0x100356E0, _crt_runtime_error user hook (0x1001fdf8) */
extern void * pfnMessageBoxA; /* 0x10035838, cached MessageBoxA proc (0x10022107) */
extern void * pfnGetActiveWindow; /* 0x1003583C, cached GetActiveWindow proc (0x10022107) */
extern void * pfnGetLastActivePopup; /* 0x10035840, cached GetLastActivePopup proc (0x10022107) */
extern int __sbh_sizeHeaderList; /* 0x11766430, __sbh_sizeHeaderList - allocated header-list size */
extern int __sbh_indGroupDefer; /* 0x11766434, __sbh_indGroupDefer - deferred group index */
extern void * __sbh_pHeaderScan; /* 0x11766438, pool: region scan cursor (ptr into array) */
extern void * __sbh_pHeaderDefer; /* 0x1176643C, __sbh_pHeaderDefer - deferred group header */
extern int __sbh_cntHeaderList; /* 0x11766440, pool: region count */
extern void * __sbh_pHeaderList; /* 0x11766444, pool: region descriptor array */
extern unsigned int g_max_pool_alloc_size; /* 0x11766448, max pool allocation size (allocator mode 3) */
extern void * _crtheap; /* 0x1176644C, process heap handle */
extern int __active_heap; /* 0x11766450, allocator mode: 3=pool, 2=block */
extern void * __pioinfo[0x40]; /* 0x11766460, LIBCMT COMMON ___pioinfo, 64 ioinfo block pointers */
extern int __nfile; /* 0x11766560, CRT file-handle count (init 0x20, bounds-checked) */
extern void ** __piob; /* 0x11766564, LIBCMT COMMON ___piob, per-handle file table - __flsall/_fcloseall walk this */
extern int __nstream; /* 0x11767580, tracked-block (stream) table count */
extern void * _acmdln; /* 0x11767584, GetCommandLineA result */
extern int (__stdcall *g_dllmain_user_handler)(void *, unsigned int, void *); /* 0x11767588, DllMain user handler fnptr */
extern int g_envp_built; /* 0x1176758C, __envp built flag */
extern int g_cmdline_parsed; /* 0x11767590, cmdline/env parsed flag */

extern struct _RTL_CRITICAL_SECTION *locktable[0x30]; /* 48 entries, cleanup bound 0x10031b6c. */


/* Address labels for native storage; metadata carries complete extents. */

#endif /* CRT_GLOBALS_H */
