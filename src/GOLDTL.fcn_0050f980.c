int __cdecl fcn_0050c710(void*, int, int);
int __cdecl fcn_004e8b40(int, void*);
int __cdecl fcn_0050e4a0(int);
void* __cdecl fcn_00503fe0(int, int, int);
float __cdecl fcn_004e7990(void*, void*, int, unsigned int);
int __cdecl fcn_005c6270(void*, int);

/* ADDRESS: GOLDTL 0x0050f980 */
/* Effective price of one inventory slot: base value from the object class,
   plus the material/quality modifiers carried by both slots, scaled by the
   GUI percent constant and clamped to 0..100. */
float __cdecl fcn_0050f980(unsigned int a0, unsigned int a1, unsigned int a2)
{
    unsigned char v1;
    unsigned char* v10;
    int v11;
    unsigned int v12;
    float v13;
    float v14;
    float v15;
    int v16;
    unsigned char v17;
    unsigned int v2;
    int v3;
    unsigned int v4;
    unsigned int v5;
    char* v6;
    unsigned char v7;
    char q[0x14];
    int v9;

    v2 = a1;
    v4 = a0;
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
        fcn_004e8b40(*(char*) (v9 + 0x7f4e06), q);
        v16 = *(int*) (q + 4);
        if (v16 == 4) {
            v3 = fcn_0050e4a0(1);
            if (v3) {
                v15 = (float) fcn_0050c710((void*) v3, 4, 1) + v15;
            }
        }
    }
    v7 = *(unsigned char*) (v9 + 0x7f4e09);
    if (0x1e <= v7 && v7 <= 0x21) {
        v5 = 0;
        switch (v7) {
        case 0x1e:
            v5 = 0x17;
            break;
        case 0x1f:
            v5 = 0x18;
            break;
        case 0x20:
            v5 = 0x19;
            break;
        case 0x21:
            v5 = 0x1a;
            break;
        }
        v3 = (int) fcn_00503fe0(1, 5, v5);
        if (v3 && !(*(unsigned char*) (v3 + 0x5a) & 1)) {
            v15 = (float) fcn_0050c710((void*) v3, 4, 1) + v15;
        }
    }
    v12 = 0;
    v7 = 0;
    v13 = (float) (*(char*) (v4 * 0x300 + 0x869480 + v2) + 0x7f) *
          *(float*) 0x662c30 * *(float*) 0x662cf8;
    v10 = (unsigned char*) *(unsigned int*) 0x90e094;
    do {
        if (*v10 && *(short*) (v10 + 0x27) == *(short*) (v9 + 0x7f4ca0)) {
            v6 = (char*) ((unsigned int) *v10 * 0x24d +
                          *(unsigned int*) 0x868050);
            if (*v6 == '!') {
                v1 = v6[0x247];
                if (v7 < v1) {
                    v7 = v1;
                }
            }
            if (3 <= v7) {
                break;
            }
        }
        v12 += 1;
        v10 = v10 + 0xa9;
    } while (v12 < 0x100);
    v3 = v9 + 0x7f4ca0;
    v11 = a1 * 0x21c;
    v14 = fcn_004e7990((void*) v3, (void*) (v11 + 0x7f4ca0), v7, a2);
    v15 = v14 + (v13 + v15);
    if (*(char*) (v11 + 0x7f4e06)) {
        fcn_004e8b40(*(char*) (v11 + 0x7f4e06), q);
        v17 = *(unsigned char*) (q + 8);
        if (v17 && v17 <= 3) {
            a1 = fcn_005c6270((void*) v3, 0x155);
            v15 = (float) (int) a1 * *(float*) 0x6640cc + v15;
            a1 = fcn_005c6270((void*) v3, 0x15d);
            v13 = (float) (int) a1 * *(float*) 0x6640cc;
        } else if (4 <= v17 && v17 <= 7) {
            a1 = fcn_005c6270((void*) v3, 0x157);
            v15 = (float) (int) a1 * *(float*) 0x6640cc + v15;
            a1 = fcn_005c6270((void*) v3, 0x15f);
            v13 = (float) (int) a1 * *(float*) 0x662924;
        } else if (v17 > 7 && v17 < 10) {
            a1 = fcn_005c6270((void*) v3, 0x159);
            v13 = (float) (int) a1 * *(float*) 0x664170;
            a1 = fcn_005c6270((void*) v3, 0x165);
            v15 = (float) (int) a1 * *(float*) 0x664170 + v13 + v15;
            a1 = fcn_005c6270((void*) v3, 0x166);
            v13 = (float) (int) a1 * *(float*) 0x662938;
        }
        v15 = v13 + v15;
    }
    v14 = v15;
    if (fcn_005c6270((void*) v3, 0x2b6)) {
        if (*(char*) (v11 + 0x7f4e06)) {
            v14 = v14 + *(float*) 0x662a98;
            v15 = v14;
        }
        if (*(unsigned int*) (v11 + 0x7f4e6c) & 0x3e00) {
            v14 = v14 + *(float*) 0x662a98;
            v15 = v14;
        }
    }
    if (*(int*) (v11 + 0x7f4e0c) &&
        *(unsigned short*) (*(int*) (v11 + 0x7f4e0c) + 0x27) == a0) {
        v14 = (float) fcn_005c6270((void*) v3, 0x16b) * *(float*) 0x664170 + v15;
    }
    v4 = *(unsigned int*) (v9 + 0x7f4ccc) >> 0xe & 7;
    if (v4 && *(char*) (v9 + 0x7f4ca9) != *(char*) (v11 + 0x7f4ca9)) {
        v14 = v14 - (float) (v4 * 3);
    }
    v4 = *(unsigned int*) (v9 + 0x7f4ccc) >> 0x17 & 3;
    if (v4) {
        v14 = v14 - (float) (v4 * 3);
    }
    if (v14 < *(float*) 0x662cf8) {
        if (*(float*) 0x6628a8 < v14) {
            return v14;
        }
        return *(float*) 0x6628a8;
    }
    return *(float*) 0x662cf8;
}
