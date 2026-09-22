// FUNCTION: SERVER 0x1001b9d4
#include <windows.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

/* Game's custom DLL entry point (PE AddressOfEntryPoint) — replaces the
 * CRT's _DllMainCRTStartup.  Runs the __CRT_INIT logic (0x1001b8fb)
 * manually and drives the game's attach/detach bookkeeping.
 * __stdcall per the binary (ret 0xc); the brief suggested __cdecl.
 *
 * Flow (byte-match: RELOC): the reason==1/2 branch calls the user fnptr
 * g_11767588 + __CRT_INIT, then exit_handler (0x10009310, always returns 1)
 * runs for every reason; reason 1 with a non-zero result returns early;
 * reasons 0/3 run the detach/thread-detach __CRT_INIT and then the final
 * fnptr call.
 *
 * The `volatile int* vp` is deliberate: it forces every `return result;`
 * to reload result from its stack slot (the target's store+reload tail),
 * which MSVC6's optimizer would otherwise fold away. */

extern int __stdcall _CRT_INIT(void* hmod, unsigned int reason, void* reserved); /* 0x1001b8fb -> __CRT_INIT@12 */
extern int __stdcall exit_handler(void* a, unsigned int b, void* c);              /* 0x10009310 */

extern int (__stdcall* g_11767588)(void* hmod, unsigned int reason, void* reserved); /* 0x11767588 */

int __stdcall DllMain(void* hMod, unsigned int reason, void* reserved)
{
    int result;
    volatile int* vp = &result;

    if (reason == 0)
    {
        if (__proc_attached == 0)
            return 0;
    }
    else if (reason == 1 || reason == 2)
    {
        if (g_11767588 != NULL && !g_11767588(hMod, reason, reserved))
            return 0;
        if (!_CRT_INIT(hMod, reason, reserved))
            return 0;
    }

    result = exit_handler(hMod, reason, reserved);
    if (reason == 1)
    {
        if (result != 0)
            return *vp;
        _CRT_INIT(hMod, 0, reserved);
    }
    if (reason != 0 && reason != 3)
        return *vp;
    if (!_CRT_INIT(hMod, reason, reserved))
        result = 0;
    if (result == 0 || g_11767588 == NULL)
        return *vp;
    result = g_11767588(hMod, reason, reserved);
    return *vp;
}
