#include <windows.h>

// CFLAGS: /O1 /Gd
// FUNCTION: SERVER 0x1001ad29
// SIZE: 9

/* Tail helper: heap maintenance entry — runs the tracked-block walk in
 * mode 1 (count). */

extern int __cdecl fcn_1001ad32(int); /* 0x1001ad32 */

int __cdecl fcn_1001ad29(void)
{
    return fcn_1001ad32(1);
}
