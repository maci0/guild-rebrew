#include "Develop/Units/d3/client_scene_loader.h"
#include "client_script_runtime.h"

/* ADDRESS: GOLDTL 0x0040ed00 */
/* ADDRESS: GOLDDE 0x0040db00 */
int __cdecl ecmd_LoadScene(char** filename)
{
    if (!d3_LoadScene(*filename, 0, 0)) {
        evt_LogScriptError(evt_CurrentScript, *(unsigned int*) (evt_CurrentScript + 0x118),
                    "ecmd_LoadScene: Could not find scene on disk...");
    }
    return 1;
}
