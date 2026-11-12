#include "client_scene_resources.h"

/* ADDRESS: GOLD 0x0045cc80 */
void __cdecl fcn_0045cc80(int* a0)
{
    int* p;

    if (*a0 == 0)
        return;
    p = (int*) a0[2];
    if (p != 0) {
        p[1] = 0;
        p[0] = 0;
        p[3] = 0;
    }
    fcn_0045fbb0((SCENE_RESOURCE*) *a0);
    a0[0] = 0;
    a0[2] = 0;
}
