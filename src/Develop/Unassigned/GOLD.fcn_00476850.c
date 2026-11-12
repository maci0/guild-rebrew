#include "client_sprites.h"
#include "client_scene_resources.h"

void __cdecl m_FreeTracked(void*);

/* ADDRESS: GOLD 0x00476850 */
void __cdecl fcn_00476850(void* node)
{
    int i;

    for (i = 0; i < 32; i++) {
        if (g_1015ec0[i] == node) {
            g_1015ec0[i] = 0;
            fcn_004481e0(*(SCENE_RESOURCE**)((char*)node + 0x60));
            m_FreeTracked(node);
            return;
        }
    }
}
