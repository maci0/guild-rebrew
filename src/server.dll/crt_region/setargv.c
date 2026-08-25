// CFLAGS: /O1 /Gd
// FUNCTION: SERVER 0x1001f9c0
#include <windows.h>

/* Game's CRT-startup overrides for command-line/environment parsing:
 * _setenvp copies the raw environment block into a malloc'd array,
 * _setargv parses the command line into argv/argc, and
 * __crtGetEnvironmentStringsA returns the environment as an ANSI block
 * (cached per-process via g_100356dc). */

extern int g_11767590;      /* 0x11767590 - cmdline/env already parsed flag */
extern void __cdecl fcn_100220eb(void);      /* 0x100220eb - getcmdln helper */
extern int __cdecl fcn_1001bdd0(const char*); /* 0x1001bdd0 - strlen */
extern void* __cdecl malloc(unsigned int);    /* 0x1001a7f7 - game malloc */
extern void __cdecl free(void*);              /* 0x1001ab81 - game free */
extern void __cdecl _amsg_exit(int);        /* 0x1001ba71 - fatal error exit */
extern char* __cdecl fcn_1001f8d0(char*, const char*); /* 0x1001f8d0 - strcpy */

extern void* g_10035500;   /* 0x10035500 - environment strings ptr */
extern int g_100354d0;     /* 0x100354d0 - __envp */
extern int g_1176758c;     /* 0x1176758c - envp built flag */

void __cdecl _setenvp(void)
{
    char* env;
    char** dst;
    int count;

    if (g_11767590 == 0)
        fcn_100220eb();
    env = (char*)g_10035500;
    count = 0;
    while (*env != 0)
    {
        if (*env != '=')
            count++;
        env += fcn_1001bdd0(env) + 1;
    }
    dst = (char**)malloc(count * 4 + 4);
    g_100354d0 = (int)dst;
    if (dst == NULL)
        _amsg_exit(9);
    env = (char*)g_10035500;
    if (*env != 0)
    {
        do
        {
            int len = fcn_1001bdd0(env) + 1;
            if (*env != '=')
            {
                *dst = (char*)malloc(len);
                if (*dst == NULL)
                    _amsg_exit(9);
                fcn_1001f8d0(*dst, env);
                dst++;
            }
            env += len;
        } while (*env != 0);
    }
    free(g_10035500);
    g_10035500 = NULL;
    *dst = NULL;
    g_1176758c = 1;
}

// FUNCTION: SERVER 0x1001fa79

extern char g_100355d8[];    /* 0x100355d8 - module filename buffer */
extern int g_100354e0;       /* 0x100354e0 - _pgmptr */
extern void* g_11767584;     /* 0x11767584 - GetCommandLineA result */
extern int g_100354c4;       /* 0x100354c4 - __argc */
extern int g_100354c8;       /* 0x100354c8 - __argv */
extern void __cdecl fcn_1001fb12(char*, char**, char**, int*, int*); /* 0x1001fb12 - argv parser */

void __cdecl _setargv(void)
{
    int argc;
    int size;
    char** argv;
    char* cmdline;

    if (g_11767590 == 0)
        fcn_100220eb();
    GetModuleFileNameA(NULL, g_100355d8, 0x104);
    g_100354e0 = (int)g_100355d8;
    cmdline = (char*)g_11767584;
    if (*cmdline == 0)
        cmdline = g_100355d8;
    fcn_1001fb12(cmdline, NULL, NULL, &argc, &size);
    argv = (char**)malloc(size + argc * 4);
    if (argv == NULL)
        _amsg_exit(8);
    fcn_1001fb12(cmdline, argv, argv + argc, &argc, &size);
    g_100354c8 = (int)argv;
    g_100354c4 = argc - 1;
}

// FUNCTION: SERVER 0x1001fcc6

extern int g_100356dc;       /* 0x100356dc - env mode: 0=uninit, 1=W, 2=A */
extern void* __cdecl fcn_1001eab0(void*, const void*, int); /* 0x1001eab0 - memcpy */

void* __cdecl __crtGetEnvironmentStringsA(void)
{
    char* aenv;
    char* envp;
    WCHAR* wenv;
    int mode;

    aenv = NULL;
    envp = NULL;
    wenv = NULL;
    mode = g_100356dc;
    if (mode == 0)
    {
        wenv = GetEnvironmentStringsW();
        if (wenv != NULL)
        {
            g_100356dc = 1;
            goto wide;
        }
        aenv = GetEnvironmentStrings();
        if (aenv == NULL)
            return NULL;
        g_100356dc = 2;
        goto ansi;
    }
    if (mode == 1)
        goto wide;
    if (mode == 2)
        goto ansi;
    return NULL;

wide:
    if (wenv == NULL)
    {
        wenv = GetEnvironmentStringsW();
        if (wenv == NULL)
            return NULL;
    }
    {
        WCHAR* p;
        int wlen;
        int mblen;

        p = wenv;
        if (*p != 0)
        {
            for (;;)
            {
                p += 2;
                if (*p != 0)
                    continue;
                p += 2;
                if (*p == 0)
                    break;
            }
        }
        wlen = (int)(p - wenv) / 2 + 1;
        mblen = WideCharToMultiByte(0, 0, wenv, wlen, NULL, 0, NULL, NULL);
        if (mblen != 0)
        {
            envp = (char*)malloc(mblen);
            if (envp != NULL)
                WideCharToMultiByte(0, 0, wenv, (int)envp, envp, mblen, NULL, NULL);
        }
        FreeEnvironmentStringsW(wenv);
        return envp;
    }

ansi:
    if (aenv == NULL)
    {
        aenv = GetEnvironmentStrings();
        if (aenv == NULL)
            return NULL;
    }
    {
        char* p;
        int len;

        p = aenv;
        if (*p != 0)
        {
            for (;;)
            {
                p++;
                if (*p != 0)
                    continue;
                p++;
                if (*p == 0)
                    break;
            }
        }
        len = (int)(p - aenv) + 1;
        envp = (char*)malloc(len);
        if (envp == NULL)
            envp = NULL;
        else
            fcn_1001eab0(envp, aenv, len);
        FreeEnvironmentStringsA(aenv);
        return envp;
    }
}

// CFLAGS: /O1 /Gd
// FUNCTION: SERVER 0x1001bdd0

/* _strlen (game copy of the CRT asm strlen: alignment loop then the
 * 0x7efefeff dword null-detection scan). */

size_t __cdecl fcn_1001bdd0(const char* str)
{
    const char* eos = str;
    unsigned int x;

    while (((unsigned int)eos & 3) != 0)
    {
        if (*eos++ == 0)
            return (size_t)(eos - 1 - str);
    }
    for (;;)
    {
        x = *(const unsigned int*)eos;
        eos += 4;
        if ((((x + 0x7efefeff) ^ ~x) & 0x81010100) != 0)
        {
            if ((x & 0xff) == 0)
                return (size_t)(eos - 4 - str);
            if ((x & 0xff00) == 0)
                return (size_t)(eos - 3 - str);
            if ((x & 0xff0000) == 0)
                return (size_t)(eos - 2 - str);
            return (size_t)(eos - 1 - str);
        }
    }
}

// FUNCTION: SERVER 0x1001f8d0

/* _strcpy (game copy; functional C equivalent of the asm original which
 * tail-jumps into the shared strcat copy loop). */

char* __cdecl fcn_1001f8d0(char* dst, const char* src)
{
    char* d = dst;

    while ((*d++ = *src++) != 0)
        ;
    return dst;
}

// FUNCTION: SERVER 0x1001fb12

/* _parse_cmdline (game copy): scans the program name, then the argument
 * list, into the string buffer argend; counts args (argc) and copied bytes
 * (numargs).  Uses the game's char-type table at 0x11766321 (bit 4 = the
 * char starts a double-byte sequence). */

void __cdecl fcn_1001fb12(char* cmdstart, char** argv, char** argend, int* argc, int* numargs)
{
    char* sbuf;
    char** ap;
    unsigned int numslash;
    int copychar;
    int inquote;
    char c;

    *numargs = 0;
    *argc = 1;
    ap = argv;
    sbuf = (char*)argend;
    if (ap != NULL)
    {
        *ap++ = (char*)argend;
        argv = ap;
    }
    inquote = 0;
    if (*cmdstart == '"')
    {
        c = *++cmdstart;
        while (c != '"' && c != 0)
        {
            if ((*(unsigned char*)(0x11766321 + (unsigned char)c) & 4) != 0)
            {
                (*numargs)++;
                if (sbuf != NULL)
                {
                    *sbuf++ = *cmdstart;
                    cmdstart++;
                }
            }
            (*numargs)++;
            if (sbuf != NULL)
            {
                *sbuf++ = *cmdstart;
                cmdstart++;
            }
            c = *cmdstart;
        }
        (*numargs)++;
        if (sbuf != NULL)
            *sbuf++ = 0;
        if (*cmdstart == '"')
            cmdstart++;
    }
    else
    {
        for (;;)
        {
            (*numargs)++;
            if (sbuf != NULL)
                *sbuf++ = *cmdstart;
            c = *cmdstart++;
            if ((*(unsigned char*)(0x11766321 + (unsigned char)c) & 4) != 0)
            {
                (*numargs)++;
                if (sbuf != NULL)
                {
                    *sbuf++ = *cmdstart;
                    cmdstart++;
                }
            }
            if (c == 0)
            {
                cmdstart--;
                break;
            }
            if (c == ' ' || c == '\t')
            {
                if (sbuf != NULL)
                    sbuf[-1] = 0;
                break;
            }
        }
    }
    for (;;)
    {
        if (*cmdstart == 0)
            break;
        c = *cmdstart;
        if (c == ' ' || c == '\t')
        {
            cmdstart++;
            continue;
        }
        if (*cmdstart == 0)
            break;
        if (ap != NULL)
        {
            *ap++ = sbuf;
            argv = ap;
        }
        (*argc)++;
        copychar = 1;
        numslash = 0;
        while (*cmdstart == '\\')
        {
            cmdstart++;
            numslash++;
        }
        if (*cmdstart == '"' && (numslash & 1) == 0)
        {
            if (inquote != 0)
            {
                if (cmdstart[1] == '"')
                    cmdstart++;
            }
            copychar = 0;
            inquote = !inquote;
        }
        numslash >>= 1;
        while (numslash != 0)
        {
            if (sbuf != NULL)
                *sbuf++ = '\\';
            (*numargs)++;
            numslash--;
        }
        c = *cmdstart;
        if (c == 0)
            goto argend;
        if (inquote == 0 && (c == ' ' || c == '\t'))
            goto argend;
        if (copychar != 0)
        {
            if (sbuf != NULL)
            {
                if ((*(unsigned char*)(0x11766321 + (unsigned char)c) & 4) != 0)
                {
                    *sbuf++ = c;
                    cmdstart++;
                    (*numargs)++;
                }
                *sbuf++ = *cmdstart;
                cmdstart++;
            }
            else
            {
                if ((*(unsigned char*)(0x11766321 + (unsigned char)c) & 4) != 0)
                {
                    cmdstart++;
                    (*numargs)++;
                }
            }
            (*numargs)++;
            cmdstart++;
        }
        else
            cmdstart++;
        continue;
    argend:
        if (sbuf != NULL)
        {
            *sbuf++ = 0;
        }
        (*numargs)++;
    }
    if (ap != NULL)
        *ap = NULL;
    (*argc)++;
}

// FUNCTION: SERVER 0x100220eb

/* __crtinitcommandline: on first use, sets the multibyte codepage to the
 * locale default (-3) and marks the command line as parsed. */

extern int __cdecl _setmbcp(int);   /* LIBCMT */

void __cdecl fcn_100220eb(void)
{
    if (g_11767590 == 0)
    {
        _setmbcp(-3);
        g_11767590 = 1;
    }
}
