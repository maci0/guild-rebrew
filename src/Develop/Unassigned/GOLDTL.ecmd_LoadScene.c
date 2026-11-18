#include "client_scene_loader.h"
#include "client_script_runtime.h"

/* ADDRESS: GOLDTL 0x0040ed00 */
int __cdecl ecmd_LoadScene(char** filename)
{
    if (!fcn_00448360(*filename, 0, 0)) {
        fcn_00425bf0(evt_CurrentScript, *(unsigned int*) (evt_CurrentScript + 0x118),
                    "ecmd_LoadScene: Could not find scene on disk...");
    }
    return 1;
}
