#include <string.h>

typedef struct COMBAT_WORLD {
    char pad00[0x80];
    int listA[16]; /* +0x80 */
    int listB[16]; /* +0xc0 */
} COMBAT_WORLD;

typedef struct CUTSCENE_ENTITY_SLOT {
    int id;
    int f4;
    char pad8[0x24];
} CUTSCENE_ENTITY_SLOT; /* SIZE 0x2c */

extern int cut_CombatCancelledEntity;               /* 0x772ea4 */
extern unsigned short* g_772e98;   /* 0x772e98, entity pointer */
extern unsigned short* cut_CombatDefenderEntity;   /* 0x772e9c, entity pointer */
extern char* g_772eb4;             /* 0x772eb4, player table */
extern int g_772f08;               /* 0x772f08, object count */
extern char* d3_CombatFlagObjects[];           /* 0x9b9e40, object pointer table */
extern char cut_ParticipantSlots[];            /* 0x9b0e20, 0x35c-byte player records */

int __cdecl gm_LookupEntityRecordIn32SlotTable(int search_id);
void* __cdecl gm_FindOrCreateEntitySlot(void* rec, char* entity);
void __cdecl d3_TransformPoint(char* object, float* in, float* out);
void __cdecl cm_SendUpdateCutsceneEntitySlot(int a1, void* a2);

/* ADDRESS: GOLDTL 0x004d4f30 */
/* ADDRESS: GOLDDE 0x004c1e80 */
char* __cdecl cut_ResolveCombatWinner(COMBAT_WORLD* world)
{
    int countA;
    int nB;
    int countB;
    int countC;
    char* result;
    int i;
    int n;
    int* p;
    char* rec;
    char* obj;
    CUTSCENE_ENTITY_SLOT slot;
    CUTSCENE_ENTITY_SLOT* src;
    float out[4];

    result = 0;
    countC = 0;
    countB = 0;
    if (cut_CombatCancelledEntity != 0) {
        return (char*) cut_CombatCancelledEntity;
    }

    countA = 0;
    for (i = 0; i < 0x10; i++) {
        if (world->listA[i] != -1) {
            rec = (char*) gm_LookupEntityRecordIn32SlotTable(world->listA[i]);
            if (*(char*) (rec + 8) != 0 && *(char*) (rec + 8) != 4 &&
                *(int*) (*(int*) (*(int*) (rec + 0x184) + 0x34) + 0x218) != 1) {
                countA++;
            }
        }
    }

    nB = 0;
    for (i = 0; i < 0x10; i++) {
        if (world->listB[i] != -1) {
            rec = (char*) gm_LookupEntityRecordIn32SlotTable(world->listB[i]);
            if (*(char*) (rec + 8) != 0 && *(char*) (rec + 8) != 4 &&
                *(int*) (*(int*) (*(int*) (rec + 0x184) + 0x34) + 0x218) != 1) {
                nB++;
            }
        }
    }

    if (nB <= 0) {
        result = (char*) cut_CombatDefenderEntity;
    } else if (countA <= 0) {
        result = (char*) g_772e98;
    }

    i = 0;
    if (g_772f08 > 0) {
        do {
            if (strstr(d3_CombatFlagObjects[i], "sp_CONQUER") != 0) {
                d3_TransformPoint(d3_CombatFlagObjects[i],
                             (float*) (d3_CombatFlagObjects[i] + 0x4c), out);
                countB++;
                rec = *(char**) (d3_CombatFlagObjects[i] + 0x204);
                if (rec != 0 &&
                    *(int*) (rec + 0x16c) == *(int*) &cut_CombatDefenderEntity) {
                    countC++;
                }
            }
            i++;
        } while (i < g_772f08);
        if (countB != 0 && countC == countB) {
            result = (char*) g_772e98;
        }
    }

    if (result != 0) {
        i = 0;
        i = 0;
        n = *(unsigned char*) (g_772eb4 + 0x30);
        if (n > 0) {
            p = (int*) (g_772eb4 + 0x34);
            do {
                if (*p != -1) {
                    break;
                }
                i++;
                p++;
            } while (i < n);
        }
        src = (CUTSCENE_ENTITY_SLOT*) gm_FindOrCreateEntitySlot(cut_ParticipantSlots + i * 0x35c,
                                                result);
        slot = *src;
        slot.id = *(int*) (result + 4);
        slot.f4 = 5;
        cm_SendUpdateCutsceneEntitySlot(*(int*) (cut_ParticipantSlots + i * 0x35c + 0x10), &slot);
    }
    return result;
}
