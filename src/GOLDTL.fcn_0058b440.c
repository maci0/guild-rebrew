void __cdecl fcn_0058b9c0(void*, void*);
void __cdecl fcn_0058ba20(char*, char*);
int __cdecl fcn_0046fac0(void*, int, void*, int);
void __cdecl fcn_00534160(int, int, int, int);
char* __cdecl fcn_00508e40(int);
int __cdecl fcn_00468df0(int, int, int, int, int);
void __cdecl fcn_00469110(int, int);
void __cdecl fcn_0046c310(int);
void __cdecl fcn_00533f40(int, int, int, int, int, int*, int*, int*);
void __cdecl fcn_00472900(int, int);
int __cdecl fcn_0046f740(int, int, int, int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_0051af00(void*, ...);

/* ADDRESS: GOLDTL 0x0058b440 */
/* Fill and draw the eight trade-goods rows of the market window: compact the
   non-empty entries from the supplier record, build one icon plus five price
   gauges per row, then draw the detail text for the selected entry. */
void __cdecl fcn_0058b440(unsigned int a0, unsigned int* a1, int a2, int a3)
{
    int* v1;
    char v10[4];
    char v11[4];
    char v12[256];
    char v13[256];
    int v14;
    int* v15;
    int v16;
    int v17;
    int v18;
    unsigned int v19;
    unsigned int* v2;
    unsigned int* v3;
    unsigned int* v4;
    unsigned short* v5;
    unsigned int v6;
    int v7;
    int v8;
    char v9[4];

    v2 = a1;
    v16 = 0;
    v19 = 0;
    v1 = (int*) a1[a1[0x4d] * 4 + 0xe];
    v14 = *(int*) (*v1 * 4 + 0x6652f8);
    if (1 <= v14) {
        v7 = 0;
        v4 = &a1[0x51];
        do {
            v3 = v4;
            if (*(int*) (v1[4] + v7) != -1) {
                v4[-1] = (int) (v1[4] + v7);
                v16 += 1;
                v3 = &v4[3];
                v6 = *(unsigned int*) (v7 + v1[4]);
                v4[-2] = 0xffffffff;
                *v4 = v6;
            }
            v7 += 0x44;
            v14 -= 1;
            v4 = v3;
        } while (v14);
    }
    if (v16 <= 7) {
        v14 = 8 - v16;
        v4 = &a1[v16 * 3 + 0x51];
        do {
            v4[-1] = 0;
            *v4 = 0xffffffff;
            v4[-2] = 0xffffffff;
            v4 = &v4[3];
            v14 -= 1;
        } while (v14);
    }
    a1[0x4e] = 0xffffffff;
    if (a2 == (int) a1[0x4d]) {
        v19 = *(unsigned int*) (a1[3] * 0x3cc + 0x1016198);
    }
    fcn_004727a0(*a1, 3);
    fcn_00519190(0x6811b0);
    fcn_004727a0(*v2, 5);
    fcn_00519190(0x6811b0);
    fcn_004727a0(*v2, 7);
    fcn_00519190(0x6811b0);
    fcn_00533f40(0, 0, v2[6], v2[3],
                 *(unsigned int*) (v2[3] * 0x3cc + 0x1015f50), (int*) v11,
                 (int*) v10, (int*) v9);
    fcn_004727a0(*v2, 3);
    v18 = 0;
    if (1 <= v16) {
        v17 = a3 == 0;
        v15 = (int*) &v2[0x50];
        do {
            v14 = v2[3];
            v8 = v14 * 0x3cc;
            v7 = *(int*) (v8 + 0x1015f50);
            v8 = (*(int*) (v8 + 0x1015f4c) -
                  (int) *(short*) (*(int*) 0x772500 + 0x2399c)) / 2;
            v15[-1] = fcn_0046f740(v8, v7 * v18 + 2, 0x6c7, v14);
            v14 = fcn_0046f740(v8 + 2,
                               *(int*) (v2[3] * 0x3cc + 0x1015f50) * v18 + 4,
                               *(unsigned int*) (*v15 + 0x3c), v2[3]);
            v15[-1] = v14;
            *(unsigned int*) (*(int*) 0x1015ea0 + 0x5c + v14 * 0x2f4) = v17;
            *(unsigned int*) (*(int*) 0x1015ea0 + 0x1d0 + v15[-1] * 0x2f4) = 3;
            fcn_0058b9c0((void*) *v15, v12);
            fcn_0058ba20((char*) *v15, v13);
            v7 = *(int*) (v2[3] * 0x3cc + 0x1015f50) * v18;
            v14 = fcn_0046fac0(0, v7 + 0x38, v12, v2[3]);
            *(unsigned int*) (v14 * 0x2f4 + 0x6c + *(int*) 0x1015ea0) = 1;
            *(unsigned int*) (v14 * 0x2f4 + 0x18 + *(int*) 0x1015ea0) =
                *(unsigned int*) (v2[3] * 0x3cc + 0x1015f4c);
            fcn_00472900(v14, 0x54);
            v14 = fcn_0046fac0(0, v7 + 0x45, v13, v2[3]);
            *(unsigned int*) (v14 * 0x2f4 + 0x6c + *(int*) 0x1015ea0) = 1;
            *(unsigned int*) (v14 * 0x2f4 + 0x18 + *(int*) 0x1015ea0) =
                *(unsigned int*) (v2[3] * 0x3cc + 0x1015f4c);
            fcn_00472900(v14, 0x54);
            v7 += 0x57;
            v14 = 0;
            do {
                fcn_0051af00(v12, 0x6a9688, v14 + 0x16b7);
                v8 = fcn_0046fac0((void*) 0x28, v7, v12, v2[3]);
                *(unsigned int*) (*(int*) 0x1015ea0 + 0x18 + v8 * 0x2f4) = 300;
                fcn_00472900(v8, 0x54);
                fcn_00534160(0xa0, v7, *(char*) (*v15 + 0x24 + v14), 0x4df);
                v14 += 1;
                v7 += 0xd;
            } while (v14 < 5);
            v18 += 1;
            v15 = &v15[3];
        } while (v18 < v16);
    }
    *(unsigned int*) (v2[3] * 0x3cc + 0x1016198) = v19;
    fcn_004727a0(*v2, 7);
    fcn_00519190(0x6811b0);
    if (v1[1] != -1) {
        v5 = (unsigned short*) fcn_00508e40(v1[1]);
        v12[0] = 0;
        if (v5) {
            fcn_0051af00(v12, 0x6a9680, *v5);
        } else {
            v14 = 0;
            if (1 <= v16) {
                v4 = &v2[0x50];
                do {
                    if (*(int*) *v4 == v1[1]) {
                        fcn_0058b9c0((void*) v2[v14 * 3 + 0x50], v12);
                        break;
                    }
                    v14 += 1;
                    v4 = &v4[3];
                } while (v14 < v16);
            }
        }
        fcn_00519190((int) 0x6a9668, 0x4101, (int) v12);
        fcn_0051af00(v12, 0x6a9660,
                     *(unsigned short*) ((char*) v1 + 10) + 0x578);
        fcn_00519190((int) 0x6a9668, 0x4102, (int) v12);
        fcn_0051af00(v12, 0x6a9658,
                     (int) (*(unsigned char*) ((char*) v1 + 0xc) *
                            *(float*) 0x662c30 * *(float*) 0x662cf8));
        fcn_00519190((int) 0x6a9668, 0x4103, (int) v12);
        if (a3 == 1) {
            v6 = fcn_00468df0(
                (*(int*) (*(int*) 0x772514 * 0x3cc + 0x1015f4c) - 0xb4) / 2,
                *(int*) (*(int*) 0x772514 * 0x3cc + 0x1015f50) - 0x21, 0xbf,
                *(int*) 0x14b5ee4, *(int*) 0x772514);
            v2[0x4e] = v6;
            fcn_00469110(v6, 0xb4);
        }
    } else {
        v12[0] = 0;
        fcn_0051af00(v12, 0x4100, *(unsigned int*) (*v1 * 4 + 0x665f78));
        fcn_00519190(0x6a2f5c, (int) v12);
    }
    *(unsigned int*) (v2[3] * 0x3cc + 0x1016198) = v19;
    fcn_0046c310(v2[3]);
    return;
}
