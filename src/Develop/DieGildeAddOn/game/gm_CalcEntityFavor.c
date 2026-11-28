extern char gm_EntitySlotTable[];
extern unsigned char* g_entity_ptr;
extern unsigned char* lpGebaeudePROT;
int __cdecl gm_GetBuildingTechEffect(void*, int, int);
int __cdecl amt_GetRoleTemplate(int, void*);
int __cdecl gm_GetGuildHall(int);
void* __cdecl gm_StartFilteredEntitySearch(int, int, int);
float __cdecl amt_CalcOfficeFavor(void*, void*, int, unsigned int);
int __cdecl gm_HasActiveSpecialObject(void*, int);

/* Effective price of one inventory slot: base value from the object class,
   plus the material/quality modifiers carried by both slots, scaled by the
   GUI percent constant and clamped to 0..100. */
/* ADDRESS: GOLDTL 0x0050f980 */
/* ADDRESS: GOLDDE 0x004fa6c0 */
float __cdecl gm_CalcEntityFavor(unsigned int entityId, unsigned int targetId, unsigned int flags)
{
    unsigned int v1;
    unsigned char* entity;
    int secondOffset;
    unsigned int entityIndex;
    float v13;
    float score;
    int v16;
    unsigned char v17;
    int v3;
    unsigned int v4;
    unsigned int v5;
    char* v6;
    unsigned int qual;
    char q[0x18];
    int firstOffset;

    score = 0.0f;
    if (entityId == targetId) {
        return 1e+02f;
    }
    if (entityId == 0xffff || targetId == 0xffff) {
        return 5e+01f;
    }
    firstOffset = entityId * 0x21c;
    v3 = *(int*) (firstOffset + ((int) &gm_EntitySlotTable + 0x170));
    if (v3) {
        score = (float) gm_GetBuildingTechEffect((void*) v3, 4, 1);
    }
    if (*(char*) (firstOffset + ((int) &gm_EntitySlotTable + 0x166))) {
        amt_GetRoleTemplate(*(unsigned char*) (firstOffset + ((int) &gm_EntitySlotTable + 0x166)), q);
        v16 = *(int*) (q + 4);
        if (v16 == 4) {
            v3 = gm_GetGuildHall(1);
            if (v3) {
                score = (float) gm_GetBuildingTechEffect((void*) v3, 4, 1) + score;
            }
        }
    }
    if (*(unsigned char*) (firstOffset + ((int) &gm_EntitySlotTable + 0x169)) >= 0x1e &&
        *(unsigned char*) (firstOffset + ((int) &gm_EntitySlotTable + 0x169)) <= 0x21) {
        v5 = 0;
        switch (*(unsigned char*) (firstOffset + ((int) &gm_EntitySlotTable + 0x169))) {
        case 0x1f:
            v5 = 0x18;
            break;
        case 0x20:
            v5 = 0x19;
            break;
        case 0x21:
            v5 = 0x1a;
            break;
        case 0x1e:
            v5 = 0x17;
            break;
        }
        v3 = (int) gm_StartFilteredEntitySearch(1, 5, v5);
        if (v3 && !(*(unsigned char*) (v3 + 0x5a) & 1)) {
            score = (float) gm_GetBuildingTechEffect((void*) v3, 4, 1) + score;
        }
    }
    v13 = (float) (*(char*) (entityId * 0x300 + ((int) &lpGebaeudePROT + 0x1430) + targetId) + 0x7f) *
          0.003921569f;
    score = v13 * 1e+02f + score;
    entityIndex = 0;
    qual = 0;
    entity = (unsigned char*) (unsigned int) g_entity_ptr;
    do {
        if (*entity && *(short*) (entity + 0x27) == *(short*) (firstOffset + (int) &gm_EntitySlotTable)) {
            v6 = (char*) ((unsigned int) *entity * 0x24d +
                          (unsigned int) lpGebaeudePROT);
            if (*v6 == '!') {
                v1 = (unsigned char) v6[0x247];
                if (v1 > qual) {
                    qual = v1;
                }
            }
            if (3 <= qual) {
                break;
            }
        }
        entityIndex += 1;
        entity = entity + 0xa9;
    } while (entityIndex < 0x100);
    v3 = firstOffset + (int) &gm_EntitySlotTable;
    secondOffset = targetId * 0x21c;
    score = amt_CalcOfficeFavor((void*) v3, (void*) (secondOffset + (int) &gm_EntitySlotTable), qual, flags) + score;
    if (*(char*) (secondOffset + ((int) &gm_EntitySlotTable + 0x166))) {
        amt_GetRoleTemplate(*(unsigned char*) (secondOffset + ((int) &gm_EntitySlotTable + 0x166)), q);
        v17 = *(unsigned char*) (q + 8);
        if (v17 > 0 && v17 < 4) {
            targetId = gm_HasActiveSpecialObject((void*) v3, 0x155);
            score = (float) (int) targetId * 1e+01f + score;
            targetId = gm_HasActiveSpecialObject((void*) v3, 0x15d);
            score = (float) (int) targetId * 1e+01f + score;
        } else if (v17 > 3 && v17 < 8) {
            targetId = gm_HasActiveSpecialObject((void*) v3, 0x157);
            score = (float) (int) targetId * 1e+01f + score;
            targetId = gm_HasActiveSpecialObject((void*) v3, 0x15f);
            score = (float) (int) targetId * 8.0f + score;
        } else if (v17 > 7 && v17 < 10) {
            targetId = gm_HasActiveSpecialObject((void*) v3, 0x159);
            score = (float) (int) targetId * 7.0f + score;
            targetId = gm_HasActiveSpecialObject((void*) v3, 0x165);
            score = (float) (int) targetId * 7.0f + score;
            targetId = gm_HasActiveSpecialObject((void*) v3, 0x166);
            score = (float) (int) targetId * 15.0f + score;
        }
    }
    if (gm_HasActiveSpecialObject((void*) v3, 0x2b6)) {
        if (*(char*) (secondOffset + ((int) &gm_EntitySlotTable + 0x166))) {
            score = score + 5.0f;
        }
        if (*(unsigned int*) (secondOffset + ((int) &gm_EntitySlotTable + 0x1cc)) & 0x3e00) {
            score = score + 5.0f;
        }
    }
    if (*(int*) (secondOffset + ((int) &gm_EntitySlotTable + 0x16c)) &&
        *(unsigned short*) (*(int*) (secondOffset + ((int) &gm_EntitySlotTable + 0x16c)) + 0x27) == entityId) {
        score = (float) gm_HasActiveSpecialObject((void*) v3, 0x16b) * 7.0f + score;
    }
    v4 = *(unsigned int*) (firstOffset + ((int) &gm_EntitySlotTable + 0x2c)) >> 0xe & 7;
    if (v4 && *(char*) (firstOffset + ((int) &gm_EntitySlotTable + 0x9)) != *(char*) (secondOffset + ((int) &gm_EntitySlotTable + 0x9))) {
        score = score - (float) (v4 * 3);
    }
    v4 = *(unsigned int*) (firstOffset + ((int) &gm_EntitySlotTable + 0x2c)) >> 0x17 & 3;
    if (v4) {
        score = score - (float) (v4 * 3);
    }
    if (score < 1e+02f) {
        if (*(float*) 0x6628a8 < score) {
            return score;
        }
        return *(float*) 0x6628a8;
    }
    return 1e+02f;
}
