#include "client_scene_resources.h"

/* ADDRESS: GOLD 0x0045d9e0 */
void __cdecl fcn_0045d9e0(char* owner, const char* name)
{
    SCENE_RESOURCE* resource;
    fcn_0045fbb0(*(SCENE_RESOURCE**) (owner + 0x1c));
    resource = fcn_004605b0(name, *(unsigned int*) (owner + 0x20), 0, 0);
    *(SCENE_RESOURCE**) (owner + 0x1c) = resource;
    if (resource != 0)
        fcn_00460e40(resource, 0);
}
