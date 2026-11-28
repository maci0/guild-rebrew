#include "Develop/Units/d3/client_lighting.h"

#if defined(REBREW_GOLD)
#include "Develop/DieGildeAddOn/game/ch_motion.h"
char __cdecl d3_VisitSceneObjectsUntilStopped(char*, char*, unsigned int, char (__cdecl *)(char*, void*), void*);
char __cdecl d3_VisitSceneNodes(char*, char*, unsigned int, void (__cdecl *)(char*));
char __cdecl d3_FreeObjectLightNodes(char*, void*);
void __cdecl d3_UpdateObjectLighting(char*);
void __cdecl fcn_00441860(int);
#else
void __cdecl d3_UpdateFloorLighting(int);
#endif

/* The TL build ignores the flag; Gold has native flag-dependent work. */
/* ADDRESS: GOLDTL 0x00450a00 */
void __cdecl UpdateSceneLighting(unsigned char flag)
{
    g_6b86d4++;
#if defined(REBREW_GOLD)
    LightingUpdateCount++;
    if (flag == 0) {
        if (g_633438 == 0) {
            goto update_terrain;
        }
    } else if (flag > 1) {
        d3_VisitSceneNodes((char*)g_67a370, 0, 0x40, d3_UpdateObjectLighting);
        goto update_terrain;
    }
    d3_VisitSceneObjectsUntilStopped((char*)g_67a370, 0, 2, d3_FreeObjectLightNodes, 0);
    d3_LightingUpdatePending = 1;
update_terrain:
#endif
    if (g_6b8300 != 0) {
#if defined(REBREW_GOLD)
        fcn_00441860(g_6b8300);
#else
        d3_UpdateFloorLighting(g_6b8300);
#endif
    }
    g_6b86d4--;
}
