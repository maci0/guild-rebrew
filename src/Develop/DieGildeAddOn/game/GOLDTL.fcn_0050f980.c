extern unsigned char* g_entity_ptr;
extern unsigned char* lpGebaeudePROT;
int __cdecl fcn_0050c710(void*, int, int);
int __cdecl fcn_004e8b40(int, void*);
int __cdecl fcn_0050e4a0(int);
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
    unsigned char* v10;
    int v11;
    unsigned int v12;
    float v13;
    float v15;
    int v16;
    unsigned char v17;
    int v3;
    unsigned int v4;
    unsigned int v5;
    char* v6;
    unsigned int qual;
    char q[0x18];
    int v9;

    v15 = 0.0f;
    if (a0 == a1) {
        return *(float*) 0x662cf8;
    }
    if (a0 == 0xffff || a1 == 0xffff) {
        return *(float*) 0x662914;
    }
    v9 = a0 * 0x21c;
    v3 = *(int*) (v9 + 0x7f4e10);
    if (v3) {
        v15 = (float) fcn_0050c710((void*) v3, 4, 1);
    }
    if (*(char*) (v9 + 0x7f4e06)) {
        fcn_004e8b40(*(unsigned char*) (v9 + 0x7f4e06), q);
        v16 = *(int*) (q + 4);
        if (v16 == 4) {
            v3 = fcn_0050e4a0(1);
            if (v3) {
                v15 = (float) fcn_0050c710((void*) v3, 4, 1) + v15;
            }
        }
    }
    if (*(unsigned char*) (v9 + 0x7f4e09) >= 0x1e &&
        *(unsigned char*) (v9 + 0x7f4e09) <= 0x21) {
        v5 = 0;
        switch (*(unsigned char*) (v9 + 0x7f4e09)) {
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
            v15 = (float) fcn_0050c710((void*) v3, 4, 1) + v15;
        }
    }
    v13 = (float) (*(char*) (a0 * 0x300 + 0x869480 + a1) + 0x7f) *
          *(float*) 0x662c30;
    v15 = v13 * *(float*) 0x662cf8 + v15;
    v12 = 0;
    qual = 0;
    v10 = (unsigned char*) (unsigned int) g_entity_ptr;
    do {
        if (*v10 && *(short*) (v10 + 0x27) == *(short*) (v9 + 0x7f4ca0)) {
            v6 = (char*) ((unsigned int) *v10 * 0x24d +
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
        v12 += 1;
        v10 = v10 + 0xa9;
    } while (v12 < 0x100);
    v3 = v9 + 0x7f4ca0;
    v11 = a1 * 0x21c;
    v15 = fcn_004e7990((void*) v3, (void*) (v11 + 0x7f4ca0), qual, a2) + v15;
    if (*(char*) (v11 + 0x7f4e06)) {
        fcn_004e8b40(*(unsigned char*) (v11 + 0x7f4e06), q);
        v17 = *(unsigned char*) (q + 8);
        if (v17 > 0 && v17 < 4) {
            a1 = fcn_005c6270((void*) v3, 0x155);
            v15 = (float) (int) a1 * *(float*) 0x6640cc + v15;
            a1 = fcn_005c6270((void*) v3, 0x15d);
            v15 = (float) (int) a1 * *(float*) 0x6640cc + v15;
        } else if (v17 > 3 && v17 < 8) {
            a1 = fcn_005c6270((void*) v3, 0x157);
            v15 = (float) (int) a1 * *(float*) 0x6640cc + v15;
            a1 = fcn_005c6270((void*) v3, 0x15f);
            v15 = (float) (int) a1 * *(float*) 0x662924 + v15;
        } else if (v17 > 7 && v17 < 10) {
            a1 = fcn_005c6270((void*) v3, 0x159);
            v15 = (float) (int) a1 * *(float*) 0x664170 + v15;
            a1 = fcn_005c6270((void*) v3, 0x165);
            v15 = (float) (int) a1 * *(float*) 0x664170 + v15;
            a1 = fcn_005c6270((void*) v3, 0x166);
            v15 = (float) (int) a1 * *(float*) 0x662938 + v15;
        }
    }
    if (fcn_005c6270((void*) v3, 0x2b6)) {
        if (*(char*) (v11 + 0x7f4e06)) {
            v15 = v15 + *(float*) 0x662a98;
        }
        if (*(unsigned int*) (v11 + 0x7f4e6c) & 0x3e00) {
            v15 = v15 + *(float*) 0x662a98;
        }
    }
    if (*(int*) (v11 + 0x7f4e0c) &&
        *(unsigned short*) (*(int*) (v11 + 0x7f4e0c) + 0x27) == a0) {
        v15 = (float) fcn_005c6270((void*) v3, 0x16b) * *(float*) 0x664170 + v15;
    }
    v4 = *(unsigned int*) (v9 + 0x7f4ccc) >> 0xe & 7;
    if (v4 && *(char*) (v9 + 0x7f4ca9) != *(char*) (v11 + 0x7f4ca9)) {
        v15 = v15 - (float) (v4 * 3);
    }
    v4 = *(unsigned int*) (v9 + 0x7f4ccc) >> 0x17 & 3;
    if (v4) {
        v15 = v15 - (float) (v4 * 3);
    }
    if (v15 < *(float*) 0x662cf8) {
        if (*(float*) 0x6628a8 < v15) {
            return v15;
        }
        return *(float*) 0x6628a8;
    }
    return *(float*) 0x662cf8;
}
