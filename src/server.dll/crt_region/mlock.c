// CFLAGS: /O1 /Oy- /Gd
// FUNCTION: SERVER 0x1001d036
#include <windows.h>

/* CRT lock table: array of per-lock CRITICAL_SECTION pointers, indexed by
 * locknum.  Lock 0x11 (_LOCK_LOCK) serializes table entry creation. */
extern CRITICAL_SECTION* locktable[]; /* 0x10031aac */

extern void* __cdecl malloc(unsigned int); /* 0x1001a7f7 */
extern void __cdecl free(void*);           /* 0x1001ab81 */
extern void __cdecl _amsg_exit(int);     /* 0x1001ba71 - game _amsg_exit */
extern void __cdecl _mlock(int);
extern void __cdecl _munlock(int);

void __cdecl _mlock(int locknum)
{
    CRITICAL_SECTION* pcs;

    if (locktable[locknum] == NULL)
    {
        pcs = (CRITICAL_SECTION*)malloc(0x18);
        if (pcs == NULL)
            _amsg_exit(0x11);   /* _RT_LOCK: fatal lock allocation error */
        _mlock(0x11);             /* _LOCK_LOCK */
        if (locktable[locknum] == NULL)
        {
            InitializeCriticalSection(pcs);
            locktable[locknum] = pcs;
        }
        else
        {
            free(pcs);
        }
        _munlock(0x11);
    }
    EnterCriticalSection(locktable[locknum]);
}

// FUNCTION: SERVER 0x1001d097

void __cdecl _munlock(int locknum)
{
    LeaveCriticalSection(locktable[locknum]);
}

/* _lock/_unlock: generic lock-table entry/exit used by the LIBCMT stdio
 * objects that the game did not copy.  Provided so those objects bind to
 * the game's lock machinery instead of pulling LIBCMT's mlock.obj (whose
 * fatal path imports FatalAppExitA, which the original binary does not
 * import). */

void __cdecl _lock(int locknum)
{
    _mlock(locknum);
}

void __cdecl _unlock(int locknum)
{
    _munlock(locknum);
}
