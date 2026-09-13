/* Full local replacement for LIBCMT:mlock.obj so the linker never pulls
 * LIBCMT's copy (which imports FatalAppExitA / IsBadWritePtr). */
#include <windows.h>

#define _TOTAL_LOCKS 44

CRITICAL_SECTION* __locktable[_TOTAL_LOCKS];
/* Game-side copies (tidtable.c) reference locktable[] as CRITICAL_SECTION**. */
CRITICAL_SECTION** locktable = __locktable;

extern void* __cdecl malloc(unsigned int);
extern void __cdecl free(void*);
extern void __cdecl _amsg_exit(int);
extern void __stdcall ExitProcess(UINT);

void __cdecl _mlock(int locknum);
void __cdecl _munlock(int locknum);

void __cdecl _lockerr_exit(char* msg)
{
    (void)msg;
    ExitProcess(1);
}

void __cdecl _mtinitlocks(void)
{
    int i;
    for (i = 0; i < _TOTAL_LOCKS; i++)
        __locktable[i] = NULL;
}

void __cdecl _mtdeletelocks(void)
{
    int i;
    for (i = 0; i < _TOTAL_LOCKS; i++) {
        if (__locktable[i] != NULL) {
            DeleteCriticalSection(__locktable[i]);
            free(__locktable[i]);
            __locktable[i] = NULL;
        }
    }
}

// FUNCTION: SERVER 0x1001d036
// _mlock
void __cdecl _mlock(int locknum)
{
    CRITICAL_SECTION* pcs;

    if (__locktable[locknum] == NULL) {
        pcs = (CRITICAL_SECTION*)malloc(sizeof(CRITICAL_SECTION));
        if (pcs == NULL)
            _amsg_exit(0x11);
        _mlock(0x11);
        if (__locktable[locknum] == NULL) {
            InitializeCriticalSection(pcs);
            __locktable[locknum] = pcs;
        } else {
            free(pcs);
        }
        _munlock(0x11);
    }
    EnterCriticalSection(__locktable[locknum]);
}

// FUNCTION: SERVER 0x1001d097
// _munlock
void __cdecl _munlock(int locknum)
{
    LeaveCriticalSection(__locktable[locknum]);
}

void __cdecl _lock(int locknum)
{
    _mlock(locknum);
}

void __cdecl _unlock(int locknum)
{
    _munlock(locknum);
}
