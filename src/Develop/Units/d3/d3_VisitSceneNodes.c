#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_fc52f0, d3_SceneRootSentinelTail, g_fb98f4, g_fb9598;
char __cdecl d3_MatchObjectTypeMask(int, unsigned int);

/* ADDRESS: GOLD 0x00438e60 */
char __cdecl d3_VisitSceneNodes(char* scene, char* node, unsigned int flags, void (__cdecl* callback)(char*))
{
    char* p;
    unsigned int single;

    if (flags == 0)
        return 0;
    if (node != 0) {
        single = flags & 0x200;
        p = node;
        do {
            if (d3_MatchObjectTypeMask(*(int*) (p + 0x218), flags))
                callback(p);
            if (*(char**) (p + 0x1fc) != 0)
                d3_VisitSceneNodes(scene, *(char**) (p + 0x1fc), flags & ~0x200U, callback);
            if (single != 0)
                break;
            p = *(char**) (p + 0x1f0);
            if (p != 0 && (p[0x210] & 1))
                goto fail_1;
        } while (p != 0);
    } else {
        if (scene == g_5fb5b0) {
            *(int*) (scene + 0x80) = g_fc52f0;
            *(int*) (scene + 0x84) = d3_SceneRootSentinelTail;
            *(int*) (scene + 0xa4) = g_fb98f4;
            *(int*) (scene + 0xa8) = g_fb9598;
        }
        p = *(char**) (scene + 0x80);
        while (p != 0 && p != (char*) 0xfc2700) {
            d3_VisitSceneNodes(scene, p, flags, callback);
            p = *(char**) (p + 0x1f0);
        }
    }
    goto fail_1;
fail_1:
	return 1;
}
