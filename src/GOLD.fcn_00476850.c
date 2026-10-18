#include "client_sprites.h"
#include "client_scene_resources.h"
#include "Develop/Units/m_alloc/m_alloc.h"

/* ADDRESS: GOLD 0x00476850 */
void __cdecl fcn_00476850(void* node)
{
    int i;
    char* p;
    p = (char*) node;
    for (i = 0; i < 32; i++) {
        if (g_1015ec0[i] == p) {
            g_1015ec0[i] = 0;
            fcn_004481e0(*(SCENE_RESOURCE**) (p + 0x60));
            m_FreeTracked(p);
            return;
        }
    }
}
