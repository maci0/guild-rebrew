// SUPPORT: SERVER reversed mirror of stock LIBCMT amsg/crt0msg code, compiled to keep crt0msg.obj out of the link (its runtime-error strings duplicate rdata_restore.c). the strcat mirror (0x1001f8e0) is asm in the CRT and cannot match in pure C; this file is scaffolding, not reversed game code
#include <windows.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

/* NOT a game override: this is stock LIBCMT __amsg_exit from dllcrt0.obj.
 * The bytes at 0x1001ba71 are identical to the library body outside that
 * object's own relocation slots, so the original simply linked it. The same
 * holds for the other functions in this file (see
 * .scratch/libcmt_probe/SUMMARY.md).
 *
 * It stays in the build for a link-side reason only: compiling it keeps
 * LIBCMT crt0msg.obj out, and that object would add 0x2c2 bytes of
 * runtime-error message strings to .rdata which rdata_restore.c already
 * supplies. Linking both overshoots .rdata by 0x320 and postlink refuses the
 * image. Do not treat this file as reversing work to finish.
 *
 * Behaviour: writes the runtime error message and calls the exit hook. The
 * __error_mode/__app_type check gates a pre-exit hook (fcn_1001fdf8) on the C
 * runtime's "report mode" flags. */

/* rterr_entry: int num + char* text = 8 bytes. */
// SIZE 0x8

extern void __cdecl fcn_1001fdf8(void);   /* 0x1001fdf8 - pre-exit hook */
extern void __cdecl fcn_1001fe31(int);    /* 0x1001fe31 - __NMSG_WRITE */
extern void (__cdecl* g_100317f0)(int);   /* 0x100317f0 - _exit hook */

void __cdecl _amsg_exit(int msg)
{
    if (__error_mode == 1 || (__error_mode == 0 && __app_type == 1))
        fcn_1001fdf8();
    fcn_1001fe31(msg);
    g_100317f0(0xff);
}

/* _crt_runtime_error: gated on the report-mode flags; calls __NMSG_WRITE
 * twice (0xfc = "abort pressed", 0xff = generic) around an optional user
 * hook (g_100356e0).  Mirrors the game's copy of crt0msg.c. */

extern void (__cdecl* g_100356e0)(void);   /* 0x100356e0 - runtime-error hook */

void __cdecl fcn_1001fdf8(void)
{
    if (__error_mode == 1 || (__error_mode == 0 && __app_type == 1))
    {
        fcn_1001fe31(0xfc);
        if (g_100356e0 != NULL)
            g_100356e0();
        fcn_1001fe31(0xff);
    }
}

/* __NMSG_WRITE: looks rterrnum up in _rterrlist (0x10033ef0), then either
 * writes the message text to stderr or shows the "Runtime Error!" box via
 * __crtMessageBoxA (0x10022107).  0xfc suppresses the box (abort path). */

extern char* __cdecl fcn_1001f8e0(char*, const char*);    /* 0x1001f8e0 - strcat */
extern void* __cdecl fcn_1001ae20(char*, const char*, unsigned int); /* 0x1001ae20 - strncpy */
extern int __cdecl fcn_10022107(const char*, const char*, unsigned int); /* 0x10022107 - __crtMessageBoxA */

/* Local copies: setargv.c also defines these, but that TU is not linked. */
static unsigned int __cdecl fcn_1001bdd0(const char* str)
{
    const char* eos = str;

    while (*eos != 0)
        eos++;
    return (unsigned int)(eos - str);
}

static char* __cdecl fcn_1001f8d0(char* dst, const char* src)
{
    char* d = dst;

    while ((*d++ = *src++) != 0)
        ;
    return dst;
}

void __cdecl fcn_1001fe31(int rterrnum)
{
    struct rterr_entry* p;
    int i;
    int off;
    char* name;
    char buf[0x104];
    char buf2[0xa0];

    for (i = 0; i < 18; i++)
        if (rterrnum == ((struct rterr_entry*)0x10033ef0)[i].num)
            break;
    off = i * 8;
    if (rterrnum != *(int*)(0x10033ef0 + off))
        return;
    if (__error_mode == 1 || (__error_mode == 0 && __app_type == 1))
    {
        char* volatile* slot = &((char* volatile*)0x10033ef4)[off >> 2];

        WriteFile(GetStdHandle((DWORD)-12), *slot, fcn_1001bdd0(*slot),
                  (unsigned long*)&rterrnum, NULL);
        return;
    }
    if (rterrnum == 0xfc)
        return;
    if (GetModuleFileNameA(NULL, buf, 0x104) == 0)
        fcn_1001f8d0(buf, "<program name unknown>");
    name = buf;
    if (fcn_1001bdd0(buf) + 1 > 0x3c)
    {
        name = fcn_1001bdd0(buf) + (buf - 0x3b);
        fcn_1001ae20(name, "...", 3);
    }
    fcn_1001f8d0(buf2, "Runtime Error!\n\nProgram: ");
    fcn_1001f8e0(buf2, name);
    fcn_1001f8e0(buf2, "\n\n");
    fcn_1001f8e0(buf2, *(char**)(0x10033ef4 + off));
    fcn_10022107(buf2, "Microsoft Visual C++ Runtime Library", 0x12010);
}

/* _strcat (game copy of the CRT string helper; the target is the asm
 * version, this is a functional C equivalent). */

char* __cdecl fcn_1001f8e0(char* dst, const char* src)
{
    char* d = dst;

    while (*d != 0)
        d++;
    while ((*d++ = *src++) != 0)
        ;
    return dst;
}

/* _strncpy (game copy of the CRT asm original: src-align byte loop,
 * dword scan with 0x7efefeff null detection, partial-dword cascade,
 * dst-align + zero-dword fill, n&3 tail, rep-stos zero fill).
 * Full structural body, differential-tested vs glibc strncpy (20k cases).
 * Best 12/272 obj:265; entry gap open (frameless n-first-ecx + ebx copy). */

/* Structural reconstruction of the asm original (guards, align loop,
 * dword scan, partial cascade, dst-align, tail, dword+byte zfill).
 * Verified byte-for-byte against glibc strncpy on 20k differential cases
 * (all alignments, n 0-999, embedded zeros). Residue drivers found:
 * keep=n init + keep-test at dw gives push-edi-first frameless entry;
 * t-first scan order homes countdown in ecx; volatile second load keeps
 * the store-copy load from CSE. Probes: .scratch/probe_g*.c, probe_h*.c. */

void* __cdecl fcn_1001ae20(void* dst, const void* src, unsigned int n)
{
    char* d = (char*)dst;
    const char* s = (const char*)src;
    unsigned int m = n;
    unsigned int keep = n;
    char byte;
    if (m != 0)
    {
        if ((((unsigned int)s) & 3) == 0)
            goto dw;
    do
    {
        byte = *s++;
        *d++ = byte;
        if (--m == 0)
            goto mid;
        if (byte == 0)
            goto dstalign;
    } while ((((unsigned int)s) & 3) != 0);
dw:
    if ((keep & ~3) == 0)
        goto tail;
    for (;;)
    {
        unsigned int x = *(const unsigned int*)s;
        unsigned int t = 0x7efefeff;
        unsigned int word;
        t += x;
        x = ~x;
        t ^= x;
        word = *(volatile unsigned int*)s;
        s += 4;
        t &= 0x81010100;
        if (t == 0)
        {
            *(unsigned int*)d = word;
            d += 4;
            m -= 4;
            if ((m & ~3) == 0)
                goto tail;
            continue;
        }
        if ((word & 0xff) == 0)
        {
            word = 0;
            *(unsigned int*)d = word;
            d += 4;
            m -= 4;
            goto zfdwords;
        }
        if ((word & 0xff00) == 0)
        {
            word &= 0xff;
            *(unsigned int*)d = word;
            d += 4;
            m -= 4;
            goto zfdwords;
        }
        if ((word & 0xff0000) == 0)
        {
            word &= 0xffff;
            *(unsigned int*)d = word;
            d += 4;
            m -= 4;
            goto zfdwords;
        }
        *(unsigned int*)d = word;
        d += 4;
        m -= 4;
        if ((m & ~3) == 0)
            goto tail;
    }
tail:
    m &= 3;
    if (m == 0)
        goto mid;
    do
    {
        byte = *s++;
        *d++ = byte;
        if (byte == 0)
            goto zf0;
    } while (--m != 0);
    goto mid;
mid:
    goto out;
zf0:
    m--;
    goto zfbytes;
dstalign:
    for (;;)
    {
        d++;
        m--;
        if (m == 0)
            goto out;
        if ((((unsigned int)d) & 3) == 0)
            break;
    }
zfdwords:
    {
        unsigned int q = m >> 2;
        m &= 3;
        while (q-- != 0)
        {
            *(unsigned int*)d = 0;
            d += 4;
        }
    }
zfbytes:
    while (m-- != 0)
    {
        *d = 0;
        d++;
    }
out:
    return dst;
    }
end:
    return dst;
}

/* __crtMessageBoxA: dynamically resolves user32.dll!MessageBoxA (plus the
 * GetActiveWindow/GetLastActivePopup owner-window chain) on first use and
 * forwards the (text, caption, type) triple. */


int __cdecl fcn_10022107(const char* text, const char* caption, unsigned int type)
{
    void* hwnd = NULL;

    if (pfnMessageBoxA == hwnd)
    {
        HMODULE h;

        h = LoadLibraryA("user32.dll");
        if ((void*)h == hwnd ||
            (pfnMessageBoxA = (void*)GetProcAddress(h, "MessageBoxA")) == hwnd)
            goto fail;
        pfnGetActiveWindow = (void*)GetProcAddress(h, "GetActiveWindow");
        pfnGetLastActivePopup = (void*)GetProcAddress(h, "GetLastActivePopup");
    }
    if (pfnGetActiveWindow != NULL)
    {
        hwnd = ((void* (__stdcall*)(void))pfnGetActiveWindow)();
        if (hwnd != NULL && pfnGetLastActivePopup != NULL)
            hwnd = ((void* (__stdcall*)(void*))pfnGetLastActivePopup)(hwnd);
    }
    return ((int (__stdcall*)(void*, const char*, const char*, unsigned int))pfnMessageBoxA)(
        hwnd, text, caption, type);
fail:
    return 0;
}

/* LIBCMT dllcrt0 pulls these undecorated CRT names. Alias them to the game
 * copies above so crt0msg.obj / crtmbox.obj are not linked (their .rdata
 * strings inflate the IAT→IMPORT gap past the layout prefix). */
void __cdecl __NMSG_WRITE(int rterrnum)
{
    fcn_1001fe31(rterrnum);
}

void __cdecl _FF_MSGBANNER(void)
{
    fcn_1001fdf8();
}

int __cdecl __crtMessageBoxA(const char* text, const char* caption, unsigned int type)
{
    return fcn_10022107(text, caption, type);
}
