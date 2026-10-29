typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

int __cdecl fcn_00449600(int a);
int __cdecl fcn_00448cc0(int a, int* b, int* c, int d);
void __cdecl fcn_00438b40(int a, void* p);
void __cdecl fcn_00438cb0(int a, void* p);
void __cdecl UpdateSceneLighting(int a);
int __cdecl fcn_00448b10(void);

static float flt_abs(float f)
{
    return f < 0.0f ? -f : f;
}

/* ADDRESS: GOLDTL 0x00449630 */
int __cdecl fcn_00449630(void)
{
    int h;
    int handle;
    int dx;
    int dy;
    int d44;
    int d40;
    int d3c;
    int d38;
    int p2c;
    int p28;
    int p24;
    int p20;
    int p1c;
    int p18;
    float f1;
    float f3;
    float f4;
    float g;
    int u;
    int v5;
    char flag;
    char flag2;
    char bflag;
    u8 ok;

    h = *(int*) 0x1041d0c;
    flag = 0;
    flag2 = 0;
    bflag = 0;
    if (h == 0)
        return 0;
    handle = fcn_00449600(*(int*) 0x1041d68);
    f1 = 0.0f;
    g = 0.0f;
    p2c = 0;
    p28 = 0;
    p24 = 0;
    p20 = 0;
    p1c = 0;
    p18 = 0;
    d44 = 0;
    d40 = 0;
    if (*(int*) 0x14ce8d0 != 0) {
        if (*(int*) 0x6b85b8 == 0) {
            *(int*) 0x6b85b0 = (int) *(short*) 0x14ce8c0;
            *(int*) 0x6b85b8 = 1;
            *(int*) 0x6b85b4 = (int) *(short*) 0x14ce8c2;
        } else if (*(int*) (h + 0x218) != 0 && h != *(int*) 0x6b8478 &&
                   h != *(int*) 0x6b847c && h != *(int*) 0x6b8480) {
            if (*(char*) 0x67ab48 == 0)
                dx = 0;
            else
                dx = (int) *(short*) 0x14ce8c0 - *(int*) 0x6b85b0;
            flag2 = *(char*) 0x67ab48 != 0;
            if (*(char*) 0x67ab49 == 0)
                dy = 0;
            else
                dy = (int) *(short*) 0x14ce8c2 - *(int*) 0x6b85b4;
            flag2 = (*(char*) 0x67ab49 != 0) || flag2;
            *(int*) 0x6b85b0 = (int) *(short*) 0x14ce8c0;
            d3c = *(int*) 0x14ce864;
            d38 = 0;
            *(int*) 0x6b85b4 = (int) *(short*) 0x14ce8c2;
            f1 = ((float) dx / (float) *(u32*) 0x14ce860) * 3.141593f;
            d40 = (int) (((float) dy / (float) *(u32*) 0x14ce864) * 3.141593f);
            h = *(int*) 0x1041d0c;
        }
    }
    if (*(int*) 0x14ce8e4 == 0) {
    check_flag:
        if (flag2 == 0)
            goto no_update;
    } else {
        if (*(int*) 0x6b85bc == 0) {
            *(int*) 0x6b85b0 = (int) *(short*) 0x14ce8c0;
            *(int*) 0x6b85b4 = (int) *(short*) 0x14ce8c2;
            *(int*) 0x6b85bc = 1;
            goto check_flag;
        }
        if (*(char*) 0x67ab48 == 0)
            dx = 0;
        else
            dx = (int) *(short*) 0x14ce8c0 - *(int*) 0x6b85b0;
        flag2 = *(char*) 0x67ab48 != 0;
        if (*(char*) 0x67ab49 == 0)
            dy = 0;
        else
            dy = (int) *(short*) 0x14ce8c2 - *(int*) 0x6b85b4;
        v5 = *(char*) 0x67ab49 != 0;
        flag = (char) (v5 != 0 || flag2);
        d38 = 0;
        *(int*) 0x6b85b4 = (int) *(short*) 0x14ce8c2;
        *(int*) 0x6b85b0 = (int) *(short*) 0x14ce8c0;
        d3c = (int) ((float) dy / (float) *(u32*) 0x14ce864);
        f3 = ((flt_abs((float) dx) + 1.0f) * 30.0f) /
             (float) *(u32*) 0x14ce860;
        if (f3 > 3.0f)
            f3 = 3.0f;
        f4 = ((flt_abs((float) dy) + 1.0f) * 30.0f) /
             (float) *(u32*) 0x14ce864;
        if (f4 > 3.0f)
            f4 = 3.0f;
        d44 = (int) (f3 * ((float) dx / (float) *(u32*) 0x14ce860) * 256.0f);
        g = f4 * (float) d3c * -256.0f;
        if (v5 == 0 && flag2 == 0)
            goto check_flag;
    }
    f3 = (float) p2c;
    f4 = (float) p28;
    if (h == *(int*) 0x6b8484) {
        if (*(char*) 0x14cf72a == 0 && *(char*) 0x14cf71d == 0) {
            p2c = d40;
            p28 = (int) f1;
            f1 = (float) p24;
        } else {
            p24 = (int) f1;
            if (*(char*) 0x14cf72a != 0 || *(char*) 0x14cf71d != 0)
                goto alt;
        }
        p24 = (int) f1;
        p20 = d44;
        p1c = (int) g;
    } else {
        f4 = f1;
        if (*(char*) 0x14cf72a == 0 &&
            (*(char*) 0x14cf71d == 0)) {
            f3 = f1;
            f4 = (float) p28;
            goto set_both;
        }
    alt:
        p28 = (int) f4;
        p2c = (int) f3;
        p18 = (int) g;
        goto after;
    set_both:
        p2c = d40;
        p28 = (int) f1;
        p24 = (int) f1;
        p20 = d44;
        p1c = (int) g;
    }
after:
    ok = (u8) fcn_00448cc0(h, &p20, &p2c, handle);
    flag2 = (char) (ok >> 1);
    bflag = (char) (ok & 1);
    if (bflag != 0)
        fcn_00438b40(*(int*) 0x1041d0c, &p18);
    if (flag2 != 0 && *(int*) 0x1041d0c != *(int*) 0x6b8478 &&
        *(int*) 0x1041d0c != *(int*) 0x6b847c &&
        *(int*) 0x1041d0c != *(int*) 0x6b8480)
        fcn_00438cb0(*(int*) 0x1041d0c, &d3c);
no_update:
    if (*(int*) 0x6b85b8 != 0 && *(int*) 0x14ce8cc != 0) {
        *(int*) 0x6b85b8 = 0;
        UpdateSceneLighting(1);
        bflag = 1;
    }
    if (*(int*) 0x6b85bc != 0 && *(int*) 0x14ce8e0 != 0) {
        *(int*) 0x6b85bc = 0;
        UpdateSceneLighting(1);
        bflag = 1;
    }
    u = fcn_00448b10();
    if ((u | bflag) == 0 && flag2 == 0)
        return 0;
    return 1;
}
