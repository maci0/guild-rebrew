extern unsigned char* g_entity_ptr;
extern unsigned char* lpGebaeudePROT;
int __cdecl gm_GetBuildingTechEffect(void*, int, int);
int __cdecl fcn_004e8b40(int, void*);
int __cdecl gm_FindPublicBuilding(int);
void* __cdecl gm_StartFilteredEntitySearch(int, int, int);
float __cdecl fcn_004e7990(void*, void*, int, unsigned int);
int __cdecl fcn_005c6270(void*, int);

/* Effective price of one inventory slot: base value from the object class,
   plus the material/quality modifiers carried by both slots, scaled by the
   GUI percent constant and clamped to 0..100. */
/* ADDRESS: GOLDTL 0x0050f980 */
float __cdecl fcn_0050f980(unsigned int a0, unsigned int a1, unsigned int a2)
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
    if (a0 == a1) {
        return *(float*) 0x662cf8;
    }
    if (a0 == 0xffff || a1 == 0xffff) {
        return *(float*) 0x662914;
    }
    firstOffset = a0 * 0x21c;
    v3 = *(int*) (firstOffset + 0x7f4e10);
    if (v3) {
        score = (float) gm_GetBuildingTechEffect((void*) v3, 4, 1);
    }
    if (*(char*) (firstOffset + 0x7f4e06)) {
        fcn_004e8b40(*(unsigned char*) (firstOffset + 0x7f4e06), q);
        v16 = *(int*) (q + 4);
        if (v16 == 4) {
            v3 = gm_FindPublicBuilding(1);
            if (v3) {
                score = (float) gm_GetBuildingTechEffect((void*) v3, 4, 1) + score;
            }
        }
    }
    if (*(unsigned char*) (firstOffset + 0x7f4e09) >= 0x1e &&
        *(unsigned char*) (firstOffset + 0x7f4e09) <= 0x21) {
        v5 = 0;
        switch (*(unsigned char*) (firstOffset + 0x7f4e09)) {
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
    v13 = (float) (*(char*) (a0 * 0x300 + 0x869480 + a1) + 0x7f) *
          *(float*) 0x662c30;
    score = v13 * *(float*) 0x662cf8 + score;
    entityIndex = 0;
    qual = 0;
    entity = (unsigned char*) (unsigned int) g_entity_ptr;
    do {
        if (*entity && *(short*) (entity + 0x27) == *(short*) (firstOffset + 0x7f4ca0)) {
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
    v3 = firstOffset + 0x7f4ca0;
    secondOffset = a1 * 0x21c;
    score = fcn_004e7990((void*) v3, (void*) (secondOffset + 0x7f4ca0), qual, a2) + score;
    if (*(char*) (secondOffset + 0x7f4e06)) {
        fcn_004e8b40(*(unsigned char*) (secondOffset + 0x7f4e06), q);
        v17 = *(unsigned char*) (q + 8);
        if (v17 > 0 && v17 < 4) {
            a1 = fcn_005c6270((void*) v3, 0x155);
            score = (float) (int) a1 * *(float*) 0x6640cc + score;
            a1 = fcn_005c6270((void*) v3, 0x15d);
            score = (float) (int) a1 * *(float*) 0x6640cc + score;
        } else if (v17 > 3 && v17 < 8) {
            a1 = fcn_005c6270((void*) v3, 0x157);
            score = (float) (int) a1 * *(float*) 0x6640cc + score;
            a1 = fcn_005c6270((void*) v3, 0x15f);
            score = (float) (int) a1 * *(float*) 0x662924 + score;
        } else if (v17 > 7 && v17 < 10) {
            a1 = fcn_005c6270((void*) v3, 0x159);
            score = (float) (int) a1 * *(float*) 0x664170 + score;
            a1 = fcn_005c6270((void*) v3, 0x165);
            score = (float) (int) a1 * *(float*) 0x664170 + score;
            a1 = fcn_005c6270((void*) v3, 0x166);
            score = (float) (int) a1 * *(float*) 0x662938 + score;
        }
    }
    if (fcn_005c6270((void*) v3, 0x2b6)) {
        if (*(char*) (secondOffset + 0x7f4e06)) {
            score = score + *(float*) 0x662a98;
        }
        if (*(unsigned int*) (secondOffset + 0x7f4e6c) & 0x3e00) {
            score = score + *(float*) 0x662a98;
        }
    }
    if (*(int*) (secondOffset + 0x7f4e0c) &&
        *(unsigned short*) (*(int*) (secondOffset + 0x7f4e0c) + 0x27) == a0) {
        score = (float) fcn_005c6270((void*) v3, 0x16b) * *(float*) 0x664170 + score;
    }
    v4 = *(unsigned int*) (firstOffset + 0x7f4ccc) >> 0xe & 7;
    if (v4 && *(char*) (firstOffset + 0x7f4ca9) != *(char*) (secondOffset + 0x7f4ca9)) {
        score = score - (float) (v4 * 3);
    }
    v4 = *(unsigned int*) (firstOffset + 0x7f4ccc) >> 0x17 & 3;
    if (v4) {
        score = score - (float) (v4 * 3);
    }
    if (score < *(float*) 0x662cf8) {
        if (*(float*) 0x6628a8 < score) {
            return score;
        }
        return *(float*) 0x6628a8;
    }
    return *(float*) 0x662cf8;
}
