// CFLAGS: /O1 /Gd
// FUNCTION: SERVER 0x1001ad32 (was FUNCTION; provided by LIBCMT / library_msvc.h)
#include <windows.h>

/* Game's __flsall override: walks the tracked-block table (0x11766564,
 * 0x11767580 entries), deleting blocks whose state byte has any of
 * bits 0x80/0x02/0x01 set.  mode 1 = delete-all (returns count deleted),
 * mode 0 = delete-pending (returns -1 if any delete failed). */

extern void __cdecl _mlock(int);    /* 0x1001d036 */
extern void __cdecl _munlock(int);  /* 0x1001d097 */
extern void __cdecl fcn_1001bb8f(int, void*);  /* 0x1001bb8f - per-entry lock */
extern void __cdecl fcn_1001bbe1(int, void*);  /* 0x1001bbe1 - per-entry unlock */
extern int __cdecl fcn_1001ac9f(void*);        /* 0x1001ac9f - delete block */

extern int g_11767580;   /* 0x11767580 - tracked-block table count */
extern void* g_11766564; /* 0x11766564 - tracked-block table */

/* RELOC 164/164. mode reads: volatile slot reads in the loop body (keeps the
 * 3-push head and [esp+0x10] compares), plain read in the tail return (emits
 * cmp [esp+0x14] ahead of pop ecx). A plain body homes mode in ebp; a volatile
 * tail reads [esp+0x10] after the pop. */
int __cdecl fcn_1001ad32(int mode)
{
    int i;
    int count = 0;
    int fail = 0;

    _mlock(2);
    i = 0;
    while (i < g_11767580)
    {
        void* p = ((void**)g_11766564)[i];
        if (p != NULL && (*(unsigned char*)((char*)p + 0xc) & 0x83) != 0)
        {
            int flags;

            fcn_1001bb8f(i, p);
            p = ((void**)g_11766564)[i];
            flags = *(int*)((char*)p + 0xc);
            if (flags & 0x83)
            {
                if (*(volatile int*)&mode == 1)
                {
                    if (fcn_1001ac9f(p) != -1)
                        count++;
                }
                else
                {
                    if (*(volatile int*)&mode == 0)
                    {
                        if ((flags & 2) != 0 && fcn_1001ac9f(p) == -1)
                            fail = -1;
                    }
                }
            }
            fcn_1001bbe1(i, ((void**)g_11766564)[i]);
        }
        i++;
    }
    _munlock(2);
    if (mode == 1)
        return count;
    return fail;
}

// CFLAGS: /O1 /Gd
// FUNCTION: SERVER 0x1001ac9f (was FUNCTION; provided by LIBCMT / library_msvc.h)

/* _fclose_lk (game copy): flush, then _commit when the _COMMIT flag (0x4000)
 * is set on the stream.  Returns -1 on flush/commit failure, else 0. */

extern int __cdecl fcn_1001accd(void*);   /* 0x1001accd - _flush */
extern int __cdecl fcn_1001f0ff(int);     /* 0x1001f0ff - _commit */

int __cdecl fcn_1001ac9f(void* stream)
{
    if (fcn_1001accd(stream) != 0)
        return -1;
    if (((unsigned char*)stream)[0xd] & 0x40)
        return fcn_1001f0ff(*(int*)((char*)stream + 0x10)) != 0 ? -1 : 0;
    return 0;
}

// FUNCTION: SERVER 0x1001bb8f (was FUNCTION; provided by LIBCMT / library_msvc.h)

/* _lock_file (game copy): index < 20 locks the global stream lock
 * (index + 0x1c), otherwise the per-stream CRITICAL_SECTION at +0x20. */

void __cdecl fcn_1001bb8f(int index, void* pio)
{
    if (index < 0x14)
        _mlock(index + 0x1c);
    else
        EnterCriticalSection((LPCRITICAL_SECTION)((char*)pio + 0x20));
}

// FUNCTION: SERVER 0x1001bbe1 (was FUNCTION; provided by LIBCMT / library_msvc.h)

/* _unlock_file (game copy): mirror of fcn_1001bb8f. */

void __cdecl fcn_1001bbe1(int index, void* pio)
{
    if (index < 0x14)
        _munlock(index + 0x1c);
    else
        LeaveCriticalSection((LPCRITICAL_SECTION)((char*)pio + 0x20));
}

// FUNCTION: SERVER 0x1001f0ff (was FUNCTION; provided by LIBCMT / library_msvc.h)

/* _commit (game copy): flushes the stream's file handle to disk via the
 * per-stream group table; sets errno=9 (EBADF) on failure. */

extern int g_11766560;   /* 0x11766560 - current stream count */
extern int g_11766460[]; /* 0x11766460 - stream group ptr table */
extern void __cdecl fcn_100203a2(int);   /* 0x100203a2 - lock fd */
extern void* __cdecl fcn_10020360(int);  /* 0x10020360 - get osfhandle */
extern void __cdecl fcn_10020401(int);   /* 0x10020401 - unlock fd */
extern int* __cdecl fcn_1001a7e5(void);  /* 0x1001a7e5 - __errno */
extern int* __cdecl fcn_1001a7ee(void);  /* 0x1001a7ee - __doserrno */

int __cdecl fcn_1001f0ff(int fd)
{
    int result;
    char** slot;
    unsigned int off;

    if ((unsigned int)fd < (unsigned int)g_11766560)
    {
        slot = (char**)&g_11766460[fd >> 5];
        off = (unsigned int)(fd & 0x1f) * 36;
        if (((*slot)[off + 4] & 1) != 0)
        {
            fcn_100203a2(fd);
            if (((*slot)[off + 4] & 1) != 0)
            {
                if (FlushFileBuffers(fcn_10020360(fd)) == 0)
                    result = (int)GetLastError();
                else
                    result = 0;
                if (result != 0)
                {
                    *fcn_1001a7ee() = result;
                    *fcn_1001a7e5() = 9;
                    result = -1;
                }
            }
            else
            {
                *fcn_1001a7e5() = 9;
                result = -1;
            }
            fcn_10020401(fd);
            return result;
        }
    }
    *fcn_1001a7e5() = 9;
    return -1;
}

// FUNCTION: SERVER 0x1001a7e5 (was FUNCTION; provided by LIBCMT / library_msvc.h)

/* __errno: returns &_ptd->_errno (offset 8 in the _ptd block). */

extern void* __cdecl _getptd(void);  /* 0x1001d131 - _getptd */

int* __cdecl fcn_1001a7e5(void)
{
    return (int*)((char*)_getptd() + 8);
}

// FUNCTION: SERVER 0x1001a7ee (was FUNCTION; provided by LIBCMT / library_msvc.h)

/* __doserrno: returns &_ptd->_doserrno (offset 0xc in the _ptd block). */

int* __cdecl fcn_1001a7ee(void)
{
    return (int*)((char*)_getptd() + 0xc);
}
