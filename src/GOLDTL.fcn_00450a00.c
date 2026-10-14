#include "client_lighting.h"

#if defined(REBREW_GOLD)
#include "Develop/DieGildeAddOn/game/ch_motion.h"
char __cdecl fcn_00438d40(char*, char*, unsigned int, char (__cdecl *)(char*, void*), void*);
char __cdecl fcn_00438e60(char*, char*, unsigned int, void (__cdecl *)(char*));
char __cdecl fcn_00452e30(char*, void*);
void __cdecl fcn_00453270(char*);
void __cdecl fcn_00441860(int);
#else
void __cdecl fcn_0043ef20(int);
#endif

/* The TL build ignores the flag; Gold has native flag-dependent work. */
/* ADDRESS: GOLDTL 0x00450a00 */
/* ADDRESS: GOLD 0x00453890 */
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
        fcn_00438e60((char*)g_67a370, 0, 0x40, fcn_00453270);
        goto update_terrain;
    }
    fcn_00438d40((char*)g_67a370, 0, 2, fcn_00452e30, 0);
    LightingUpdatePending = 1;
update_terrain:
#endif
    if (g_6b8300 != 0) {
#if defined(REBREW_GOLD)
        fcn_00441860(g_6b8300);
#else
        fcn_0043ef20(g_6b8300);
#endif
    }
    g_6b86d4--;
}
