#include "Develop/Units/d3/client_scene_resources.h"
extern unsigned int g_fb91a8;
void __cdecl d3_ReleaseSceneResourceData(SCENE_RESOURCE*);

/* ADDRESS: GOLD 0x0045fbb0 */
void __cdecl d3_ReleaseSceneResourceRef(SCENE_RESOURCE* p)
{
    SCENE_RESOURCE* q;
    unsigned int i, j;
    int index, replacement;
    if (!p || p->level <= 0)
        return;
    if (*(int*) ((char*) p + 0x70) > 0 && p->byte71 == 0) {
        q = d3_TextureBank;
        for (i = 0; i < d3_TextureBankCount; ++i, ++q) {
            if (q->level > 0 && q->id == p->id && q->byte71 > 0)
                d3_ReleaseSceneResourceRef(q);
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
        index = p - d3_TextureBank;
        q = d3_TextureBank;
        for (i = 0; i < d3_TextureBankCount; ++i, ++q) {
            if (q->level > 0 && (q->flags & 2) && q->alias == index) {
                q->flags &= ~2;
                q->alias = p->alias;
                replacement = q - d3_TextureBank;
                for (j = i + 1, ++q; j < d3_TextureBankCount; ++j, ++q) {
                    if (q->level > 0 && (q->flags & 2) && q->alias == index) {
                        q->alias = replacement;
                    }
                }
                break;
            }
        }
        if (i == d3_TextureBankCount)
            d3_ReleaseSceneResourceData(p);
    }
    p->level = 0;
    --g_fb91a8;
}
