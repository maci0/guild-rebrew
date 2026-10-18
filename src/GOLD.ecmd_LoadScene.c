#include "client_scene_loader.h"
#include "client_script_runtime.h"

/* ADDRESS: GOLD 0x0040ddf0 */
int __cdecl ecmd_LoadScene(char** filename)
{
    if (!fcn_0044be60(*filename, 0, 0)) {
        fcn_00425bf0(g_6b7e98, *(unsigned int*) (g_6b7e98 + 0x118),
                    "ecmd_LoadScene: Could not find scene on disk...");
    }
    return 1;
}
