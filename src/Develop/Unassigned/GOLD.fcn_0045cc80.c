#include "client_scene_resources.h"

/* ADDRESS: GOLD 0x0045cc80 */
void __cdecl fcn_0045cc80(int* holder)
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
    fcn_0045fbb0((SCENE_RESOURCE*) *holder);
    holder[0] = 0;
    holder[2] = 0;
}
