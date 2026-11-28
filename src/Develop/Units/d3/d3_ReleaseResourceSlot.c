#include "Develop/Units/d3/client_scene_resources.h"

/* ADDRESS: GOLD 0x0045cc80 */
void __cdecl d3_ReleaseResourceSlot(int* holder)
{
    int* p;

    if (*holder == 0)
        return;
    p = (int*) holder[2];
    if (p != 0) {
        p[1] = 0;
        p[0] = 0;
        p[3] = 0;
    }
    d3_ReleaseSceneResourceRef((SCENE_RESOURCE*) *holder);
    holder[0] = 0;
    holder[2] = 0;
}
