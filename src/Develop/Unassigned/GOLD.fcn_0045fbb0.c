#include "client_scene_resources.h"
extern unsigned int g_fb91a8;
void __cdecl fcn_0045fb40(SCENE_RESOURCE*);

/* ADDRESS: GOLD 0x0045fbb0 */
void __cdecl fcn_0045fbb0(SCENE_RESOURCE* p)
{
    SCENE_RESOURCE *q, *r;
    unsigned int i, j, count;
    int index, replacement;
    if (!p || p->level <= 0)
        return;
    if (*(int*) ((char*) p + 0x70) > 0 && p->byte71 == 0) {
        q = g_104049c;
        for (i = 0; i < g_10404a0; ++i, ++q) {
            if (q->level > 0 && q->id == p->id && q->byte71 > 0)
                fcn_0045fbb0(q);
        }
    }
    --p->level;
    if (p->level > 0)
        return;
    if (p->flags & 2) {
        p->com60 = 0;
        p->com64 = 0;
        p->tracked = 0;
    } else {
        q = g_104049c;
        count = g_10404a0;
        index = ((char*) p - (char*) q) >> 7;
        for (i = 0; i < count; ++i, ++q) {
            if (q->level > 0 && (q->flags & 2) && q->alias == index) {
                q->flags &= ~2;
                q->alias = p->alias;
                replacement = ((char*) q - (char*) g_104049c) >> 7;
                count = g_10404a0;
                for (j = i + 1, r = q + 1; j < count; ++j, ++r) {
                    if (r->level > 0 && (r->flags & 2) && r->alias == index) {
                        r->alias = replacement;
                        count = g_10404a0;
                    }
                }
                break;
            }
        }
        if (i == count)
            fcn_0045fb40(p);
    }
    p->level = 0;
    --g_fb91a8;
}
