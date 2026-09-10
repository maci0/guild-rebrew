// CFLAGS: /O1 /Gd
// FUNCTION: SERVER 0x1001b8fb (was FUNCTION; provided by LIBCMT / library_msvc.h)
#include <windows.h>

/* __CRT_INIT — the CRT's process attach/detach init + shutdown logic as
 * compiled into the game.  It is called manually by the game's custom
 * DllMain (0x1001b9d4) with (hModule, reason, reserved).
 * NOTE: the task brief called this "srv_Init @ 0x1001b9a0"; that address
 * is this function's tail (misaligned disasm), not a function start, and
 * the exported "Init" is actually 0x10009320 (CreateThread wrapper).
 * Byte-match: RELOC 217/217 (all callees/globals extern — see below). */

extern int __cdecl crt_heap_init(int);        /* 0x1001d3c8 */
extern int __cdecl __mtinit(void);            /* 0x1001d0ac */
extern void __cdecl __heap_term(void);        /* 0x1001d425 */
extern void __cdecl _cexit(void);             /* 0x1001a692 */
extern void __cdecl _ioterm(void);            /* 0x1001cb61 */
extern void __cdecl crt_close_handle(void);   /* 0x1001d100 */
extern void __cdecl __freeptd(int);           /* 0x1001d198 */
extern void* __cdecl __crtGetEnvironmentStringsA(void); /* 0x1001fcc6 */
extern void __cdecl _ioinit(void);            /* 0x1001c9a5 */
extern void __cdecl _setargv(void);           /* 0x1001fa79 */
extern void __cdecl _setenvp(void);           /* 0x1001f9c0 */
extern void __cdecl fcn_1001a643(void);       /* 0x1001a643 - initterm helper */

extern unsigned int _osver; /* 0x100354b4 - OS version dword */
extern unsigned int _winver; /* 0x100354b8 - (major << 8) | minor */
extern unsigned int _winmajor; /* 0x100354bc - OS major */
extern unsigned int _winminor; /* 0x100354c0 - OS minor */
extern int _C_Termination_Done;          /* 0x100354ec - _cexit-already-ran flag */
extern int __proc_attached;          /* 0x100354fc - attach/detach refcount */
extern void* _aenvptr;        /* 0x10035500 - environment strings ptr */
extern void* _acmdln;        /* 0x11767584 - GetCommandLineA result */

int __stdcall __CRT_INIT(void* hmod, unsigned int reason, void* reserved)
{
    unsigned int major;
    unsigned int minor;

    if (reason == 1)
    {
        _osver = (unsigned int)GetVersion();
        if (!crt_heap_init(1))
            return 0;
        major = _osver & 0xff;
        minor = (_osver >> 8) & 0xff;
        _osver >>= 16;
        _winmajor = major;
        _winminor = minor;
        _winver = (major << 8) + minor;
        if (!__mtinit())
        {
            __heap_term();
            return 0;
        }
        _acmdln = (void*)GetCommandLineA();
        _aenvptr = (void*)__crtGetEnvironmentStringsA();
        _ioinit();
        _setargv();
        _setenvp();
        fcn_1001a643();
        __proc_attached++;
        return 1;
    }
    if (reason == 0)
    {
        if (__proc_attached > 0)
        {
            __proc_attached--;
            if (_C_Termination_Done == 0)
                _cexit();
            _ioterm();
            crt_close_handle();
            __heap_term();
            return 1;
        }
        return 0;
    }
    if (reason == 3)
        __freeptd(0);
    return 1;
}
