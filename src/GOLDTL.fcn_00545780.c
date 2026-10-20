extern int g_77e8a0;
extern int g_7749e4;
extern int g_6a4768;
extern char* g_1015ea0;

void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_0046b2b0(int slot);
void __cdecl fcn_00471e30(int h);
void __cdecl fcn_00469c40(int x, int y, int slot);

/* ADDRESS: GOLDTL 0x00545780 */
void __cdecl fcn_00545780(char* a0)
{
    int* v3;
    int* v1;
    int v4;
    int v2;

    if (*(int*) (a0 + 0x74) == 0) {
        return;
    }
    if (*(int*) (*(int*) (a0 + 0x74) + 4) != -1) {
        fcn_004727a0(g_77e8a0, 0);
        fcn_0046b2b0(*(int*) (*(int*) (a0 + 0x74) + 4));
        *(int*) (*(int*) (a0 + 0x74) + 4) = -1;
    } else {
        __asm { int 3 }
    }
    v2 = *(int*) (*(int*) (a0 + 0x74) + 8);
    if (v2 != -1) {
        fcn_00471e30(v2);
        *(int*) (*(int*) (a0 + 0x74) + 8) = -1;
    }
    if (g_7749e4 == *(int*) (a0 + 0x74)) {
        g_7749e4 = 0;
    }
    *(int*) (a0 + 0x74) = 0;
    v4 = 0;
    v3 = (int*) 0x77e8c4;
    do {
        if (*v3 == -1) {
            if (v4 >= 0x10) {
                break;
            }
            v3 = (int*) (v4 * 0xc + 0x77e8d0);
            do {
                if ((int) v3 < 0x77e984) {
                    if (*v3 != -1) {
                        v3[-3] = *v3;
                        v1 = &v3[-4];
                        v3[-2] = v3[1];
                        *v1 = v3[-1];
                        *(int**) (v3[-1] + 0x74) = v1;
                        *v3 = -1;
                        v3[-1] = 0;
                        v3[1] = -1;
                        if (v3[-3] == -1 && *v1 != 0) {
                            __asm { int 3 }
                        }
                    }
                }
                v4 = v3[-3];
                if (v4 != -1) {
                    fcn_00469c40(
                        *(int*) (g_1015ea0 + v4 * 0x2f4 + 0x10) - 0x20,
                        *(int*) (g_1015ea0 + 0x14 + v4 * 0x2f4), v4);
                }
                v3 += 3;
            } while ((int) v3 < 0x77e990);
            break;
        }
        v3 += 3;
        v4++;
    } while ((int) v3 < 0x77e984);
    v4 = 0;
    v3 = (int*) 0x77e8c4;
    do {
        if (*v3 != -1) {
            g_6a4768 = v4;
        }
        v3 += 3;
        v4++;
    } while ((int) v3 < 0x77e984);
}
