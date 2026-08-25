// CFLAGS: /O1 /Gd
// FUNCTION: SERVER 0x1001ba71
#include <windows.h>

/* Game's __amsg_exit override: writes the runtime error message and calls
 * the exit hook.  The g_10035508/g_1003550c check gates a pre-exit hook
 * (fcn_1001fdf8) on the C runtime's "report mode" flags. */

struct rterr_entry { int num; char* text; };   /* matches data_globals.c */

extern void __cdecl fcn_1001fdf8(void);   /* 0x1001fdf8 - pre-exit hook */
extern void __cdecl fcn_1001fe31(int);    /* 0x1001fe31 - _NMSG_WRITE */
extern int g_10035508;                    /* 0x10035508 - report-mode flag */
extern int g_1003550c;                    /* 0x1003550c - report-mode flag 2 */
extern void (__cdecl* g_100317f0)(int);   /* 0x100317f0 - _exit hook */

void __cdecl _amsg_exit(int msg)
{
    if (g_10035508 == 1 || (g_10035508 == 0 && g_1003550c == 1))
        fcn_1001fdf8();
    fcn_1001fe31(msg);
    g_100317f0(0xff);
}

// FUNCTION: SERVER 0x1001fdf8

/* _crt_runtime_error: gated on the report-mode flags; calls _NMSG_WRITE
 * twice (0xfc = "abort pressed", 0xff = generic) around an optional user
 * hook (g_100356e0).  Mirrors the game's copy of crt0msg.c. */

extern void (__cdecl* g_100356e0)(void);   /* 0x100356e0 - runtime-error hook */

void __cdecl fcn_1001fdf8(void)
{
    if (g_10035508 == 1 || (g_10035508 == 0 && g_1003550c == 1))
    {
        fcn_1001fe31(0xfc);
        if (g_100356e0 != NULL)
            g_100356e0();
        fcn_1001fe31(0xff);
    }
}

// FUNCTION: SERVER 0x1001fe31

/* _NMSG_WRITE: looks rterrnum up in _rterrlist (0x10033ef0), then either
 * writes the message text to stderr or shows the "Runtime Error!" box via
 * __crtMessageBoxA (0x10022107).  0xfc suppresses the box (abort path). */

extern struct rterr_entry g_rterrlist[18];   /* 0x10033ef0 - error table */
extern int __cdecl fcn_1001bdd0(const char*);             /* 0x1001bdd0 - strlen */
extern char* __cdecl fcn_1001f8d0(char*, const char*);    /* 0x1001f8d0 - strcpy */
extern char* __cdecl fcn_1001f8e0(char*, const char*);    /* 0x1001f8e0 - strcat */
extern void* __cdecl fcn_1001ae20(char*, const char*, unsigned int); /* 0x1001ae20 - strncpy */
extern int __cdecl fcn_10022107(const char*, const char*, unsigned int); /* 0x10022107 - __crtMessageBoxA */

void __cdecl fcn_1001fe31(int rterrnum)
{
    int i;
    char* text;
    struct rterr_entry* p;
    char buf[0x104];
    char buf2[0xa0];

    p = (struct rterr_entry*)0x10033ef0;
    i = 0;
    while (rterrnum != p->num)
    {
        p++;
        i++;
        if ((int)p >= 0x10033f80)
            break;
    }
    if (rterrnum != ((struct rterr_entry*)0x10033ef0)[i].num)
        return;
    if (g_10035508 == 1 || (g_10035508 == 0 && g_1003550c == 1))
    {
        unsigned long written;

        text = ((struct rterr_entry*)0x10033ef0)[i].text;
        WriteFile(GetStdHandle((DWORD)-12), text, fcn_1001bdd0(text),
                  (unsigned long*)&rterrnum, NULL);
        return;
    }
    if (rterrnum == 0xfc)
        return;
    if (GetModuleFileNameA(NULL, buf, 0x104) == 0)
        fcn_1001f8d0(buf, "<program name unknown>");
    if (fcn_1001bdd0(buf) + 1 > 0x3c)
        fcn_1001ae20(buf + fcn_1001bdd0(buf) - 0x3b, "...", 3);
    fcn_1001f8d0(buf2, "Runtime Error!\n\nProgram: ");
    fcn_1001f8e0(buf2, buf);
    fcn_1001f8e0(buf2, "\n\n");
    fcn_1001f8e0(buf2, ((struct rterr_entry*)0x10033ef0)[i].text);
    fcn_10022107(buf2, "Microsoft Visual C++ Runtime Library", 0x12010);
}

// FUNCTION: SERVER 0x1001f8e0

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

// FUNCTION: SERVER 0x1001ae20

/* _strncpy (game copy; functional C equivalent of the asm original). */

void* __cdecl fcn_1001ae20(void* dst, const void* src, unsigned int n)
{
    char* d = (char*)dst;
    const char* s = (const char*)src;

    while (n > 0 && *s != 0)
    {
        *d++ = *s++;
        n--;
    }
    while (n > 0)
    {
        *d++ = 0;
        n--;
    }
    return dst;
}

// FUNCTION: SERVER 0x10022107

/* __crtMessageBoxA: dynamically resolves user32.dll!MessageBoxA (plus the
 * GetActiveWindow/GetLastActivePopup owner-window chain) on first use and
 * forwards the (text, caption, type) triple. */

extern void* g_10035838;   /* 0x10035838 - cached MessageBoxA */
extern void* g_1003583c;   /* 0x1003583c - cached GetActiveWindow */
extern void* g_10035840;   /* 0x10035840 - cached GetLastActivePopup */

int __cdecl fcn_10022107(const char* text, const char* caption, unsigned int type)
{
    void* hwnd;

    if (g_10035838 == NULL)
    {
        HMODULE h;

        h = LoadLibraryA("user32.dll");
        if (h != NULL)
        {
            g_10035838 = (void*)GetProcAddress(h, "MessageBoxA");
            if (g_10035838 != NULL)
            {
                g_1003583c = (void*)GetProcAddress(h, "GetActiveWindow");
                g_10035840 = (void*)GetProcAddress(h, "GetLastActivePopup");
            }
        }
    }
    hwnd = NULL;
    if (g_1003583c != NULL)
    {
        hwnd = ((void* (__cdecl*)(void))g_1003583c)();
        if (hwnd != NULL && g_10035840 != NULL)
            hwnd = ((void* (__cdecl*)(void*))g_10035840)(hwnd);
    }
    return ((int (__stdcall*)(void*, const char*, const char*, unsigned int))g_10035838)(
        hwnd, text, caption, type);
}
