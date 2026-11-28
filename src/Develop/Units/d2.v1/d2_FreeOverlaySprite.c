#include "Develop/Units/d2.v1/client_sprites.h"
#include "Develop/Units/d3/client_scene_resources.h"

void __cdecl m_FreeTracked(void*);

/* ADDRESS: GOLD 0x00476850 */
void __cdecl d2_FreeOverlaySprite(void* node)
{
    int i;

    for (i = 0; i < 32; i++) {
        if (g_1015ec0[i] == node) {
            g_1015ec0[i] = 0;
            d3_ReleaseSceneResource(*(SCENE_RESOURCE**)((char*)node + 0x60));
            m_FreeTracked(node);
            return;
        }
    }
}
