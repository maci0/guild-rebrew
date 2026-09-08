// CFLAGS: /O1 /Gd
// FUNCTION: SERVER 0x1001bb60 (was FUNCTION; provided by LIBCMT / library_msvc.h)
#include <windows.h>

extern void __cdecl _mlock(int);   /* 0x1001d036 */
extern void __cdecl _munlock(int); /* 0x1001d097 */

/* Dispatch lock wrapper.  Pointers inside the 0x20-strided lock-pointer
 * table 0x100317f8..0x10031a58 map to CRT lock indices 0x1c..0x2e; any
 * other pointer is a CRITICAL_SECTION embedded at (p + 0x20). */

extern char g_lock_stream_table; /* 0x100317f8 */

void __cdecl fcn_1001bb60(void* p)
{
    if ((unsigned int)p >= (unsigned int)&g_lock_stream_table &&
        (unsigned int)p <= 0x10031a58u)
        _mlock((((int)p - (int)&g_lock_stream_table) >> 5) + 0x1c);
    else
        EnterCriticalSection((LPCRITICAL_SECTION)((char*)p + 0x20));
}

// FUNCTION: SERVER 0x1001bbb2 (was FUNCTION; provided by LIBCMT / library_msvc.h)

void __cdecl fcn_1001bbb2(void* p)
{
    if ((unsigned int)p >= (unsigned int)&g_lock_stream_table &&
        (unsigned int)p <= 0x10031a58u)
        _munlock((((int)p - (int)&g_lock_stream_table) >> 5) + 0x1c);
    else
        LeaveCriticalSection((LPCRITICAL_SECTION)((char*)p + 0x20));
}
