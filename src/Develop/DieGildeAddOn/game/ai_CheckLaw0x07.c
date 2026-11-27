#include "Develop/DieGildeAddOn/game/game_data.h"
typedef struct AI_LAW_ENTITY AI_LAW_ENTITY;
struct AI_LAW_ENTITY { unsigned char pad_000[0xac]; float fac; unsigned char pad_0b0[0xb4]; unsigned char f164; };
typedef struct BUF_490c10 BUF_490c10;
struct BUF_490c10 { char pad_00[0x18]; int idx; char pad_1c[8]; };
int __cdecl gm_MapEntityStatRange(int stat_id);
int __cdecl gm_GetLawEntry(int idx, void* dst);
/* ADDRESS: GOLDTL 0x00490c10 */
int __cdecl ai_CheckLaw0x07(AI_LAW_ENTITY* entity, int unused, int* out)
{
    BUF_490c10 buf;
    int v;
    int t;

    gm_MapEntityStatRange((unsigned char) entity->f164);
    v = (int) ((entity->fac - 2.0f) * 5.0f);
    t = v < 4 ? v : 4;
    t = t < 1 ? 1 : t;
    gm_GetLawEntry(7, &buf);
    if (t != buf.idx) {
        *out = t;
        return 1;
    }
    return 0;
}
