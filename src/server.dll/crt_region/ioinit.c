// CFLAGS: /O1 /Gd
// FUNCTION: SERVER 0x1001c9a5 (was FUNCTION; provided by LIBCMT / library_msvc.h)
#include <windows.h>

/* Game's _ioinit override: builds the stream lock/descriptor table
 * (0x11766460 group pointers, 0x24-byte stream entries), imports the
 * parent's fd table from the STARTUPINFO reserved2 block, and wires the
 * three standard handles. */

extern void* __cdecl malloc(unsigned int);   /* 0x1001a7f7 - game malloc */
extern void __cdecl _amsg_exit(int);       /* 0x1001ba71 - fatal error exit */

extern int g_11766460[];   /* 0x11766460 - stream group ptr table */
extern int g_11766560;     /* 0x11766560 - current stream count */
extern int g_10033b9c;     /* 0x10033b9c - (block threshold; unused here) */

void __cdecl _ioinit(void)
{
    STARTUPINFO si;
    int n;
    int i;
    char* fl;
    char* hp;
    char* p;
    void* blk;
    int* gptr;

    blk = malloc(0x480);
    if (blk == NULL)
        _amsg_exit(0x1b);
    g_11766460[0] = (int)blk;
    g_11766560 = 0x20;
    for (p = (char*)blk; p < (char*)g_11766460[0] + 0x480; p += 0x24)
    {
        *(char*)(p + 4) = 0;
        *(int*)p = -1;
        *(int*)(p + 8) = 0;
        *(char*)(p + 5) = 0xa;
    }
    GetStartupInfoA(&si);
    if (si.cbReserved2 != 0 && si.lpReserved2 != NULL)
    {
        n = *(int*)si.lpReserved2;
        fl = (char*)si.lpReserved2 + 4;
        hp = fl + n;
        if (n > 0x800)
            n = 0x800;
        if (g_11766560 < n)
        {
            gptr = &g_11766460[1];
            do
            {
                blk = malloc(0x480);
                if (blk == NULL)
                {
                    n = g_11766560;
                    break;
                }
                g_11766560 += 0x20;
                *gptr = (int)blk;
                for (p = (char*)blk; p < (char*)*gptr + 0x480; p += 0x24)
                {
                    *(char*)(p + 4) = 0;
                    *(int*)p = -1;
                    *(int*)(p + 8) = 0;
                    *(char*)(p + 5) = 0xa;
                }
                gptr++;
            } while (g_11766560 < n);
        }
        for (i = 0; i < n; i++)
        {
            int h = *(int*)(hp + i * 4);
            int f = *(unsigned char*)(fl + i);
            if (h != -1 && (f & 1) != 0)
            {
                int* slot;
                if ((f & 8) == 0 && GetFileType((void*)h) == 0)
                    continue;
                slot = (int*)(g_11766460[i >> 5] + (i & 0x1f) * 0x24);
                *slot = h;
                *(char*)(slot + 1) = (char)f;
            }
        }
    }
    for (i = 0; i < 3; i++)
    {
        int* slot = (int*)(g_11766460[0] + i * 0x24);
        if (*(int*)slot == -1)
        {
            int h;
            int ft;
            *(char*)(slot + 1) = 0x81;
            if (i == 0)
                h = (int)GetStdHandle(-10);
            else if (i == 1)
                h = (int)GetStdHandle(-11);
            else
                h = (int)GetStdHandle(-12);
            if (h != -1)
            {
                ft = (int)GetFileType((void*)h);
                if (ft != 0)
                {
                    *slot = h;
                    if ((ft & 0xff) == 2)
                        *(char*)(slot + 1) |= 0x40;
                    else if ((ft & 0xff) == 3)
                        *(char*)(slot + 1) |= 8;
                }
                else
                    *(char*)(slot + 1) |= 0x40;
            }
            else
                *(char*)(slot + 1) |= 0x40;
        }
        else
            *(char*)(slot + 1) |= 0x80;
    }
    SetHandleCount(g_11766560);
}

// FUNCTION: SERVER 0x1001cb61 (was FUNCTION; provided by LIBCMT / library_msvc.h)

extern void __cdecl free(void*);   /* 0x1001ab81 - game free override */

/* RELOC 84/84. Single 0x24-stride cursor with the lock at b+8/b+0xc: a split
 * b/q pair emits lea/add prologues and register copies the target lacks. */
void __cdecl _ioterm(void)
{
    char** p;
    char* b;

    for (p = (char**)0x11766460; (int)p < 0x11766560; p++)
    {
        if (*p == NULL)
            continue;
        for (b = *p; b < *p + 0x480; b += 0x24)
        {
            if (*(int*)(b + 8) != 0)
                DeleteCriticalSection((LPCRITICAL_SECTION)(b + 0xc));
        }
        free(*p);
        *p = NULL;
    }
}
