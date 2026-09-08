// CFLAGS: /O1 /Gd
// FUNCTION: SERVER 0x1001a692 (was FUNCTION; provided by LIBCMT / library_msvc.h)
#include <windows.h>

/* Game's _cexit override: runs exit-time cleanup via the game's _doexit. */

extern void __cdecl fcn_1001a6a1(int, int, int);   /* 0x1001a6a1 - _doexit */

void __cdecl _cexit(void)
{
    fcn_1001a6a1(0, 0, 1);
}
