typedef unsigned char u8;
typedef unsigned short u16;

int __cdecl fcn_005a74a0(char*);
void __cdecl fcn_00525ef0(void);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00530510(void);
void __cdecl fcn_005305a0(void);
int __cdecl fcn_004234e0(int, void*, int, int, int, int, int);
int __cdecl fcn_00502cd0(int, int, int, int);
void __cdecl fcn_004c3170(char*);
int __cdecl fcn_00510c90(int);
void __cdecl fcn_0043a9c0(int);
int __cdecl fcn_004432d0(int, int);
void __cdecl fcn_0043aa30(int);
int __cdecl fcn_00437ac0(void*, int, int, void*);
void __cdecl fcn_005166a0(char*);
void __cdecl fcn_005167c0(char*, int);
void __cdecl fcn_00516c50(char*, char*);
void __cdecl fcn_00438b40(void*, void*);
void __cdecl fcn_00438cb0(void*, void*);
int __cdecl fcn_00504bd0(int);
int __cdecl fcn_00451840(void*, void*, float);
void __cdecl fcn_0057e880(int, void*, int, int);
int __cdecl fcn_00426cc0(int);
void __cdecl fcn_00428720(void*);
void __cdecl fcn_005312d0(int);
void __cdecl fcn_00516ed0(char*);
void __cdecl fcn_004c34d0(void);
void __cdecl fcn_00516f60(void);
void __cdecl fcn_00597fd0(void*);
void __cdecl fcn_005a07c0(int, void*);
void __cdecl fcn_0059f6c0(int, void*);
void __cdecl fcn_005a4030(int, void*);
void __cdecl fcn_0059f8b0(int, void*);
void __cdecl fcn_0059f9b0(int, void*);
void __cdecl fcn_005a0250(int, void*);
void __cdecl fcn_005a3820(int, void*);
void __cdecl fcn_0059e430(int, void*);
void __cdecl fcn_0059e5f0(int, void*);
void __cdecl fcn_0059f3e0(int, void*);
void __cdecl fcn_0059f320(int, void*);
void __cdecl fcn_0059f340(int, void*);
void __cdecl fcn_0059f570(int, void*);
void __cdecl fcn_005a7200(int, void*);
void __cdecl fcn_005acc80(int, void*);
void __cdecl fcn_005ace20(int, void*);
void __cdecl fcn_005acf90(int, void*);
void __cdecl fcn_005ad260(int, void*);
void __cdecl fcn_005ad360(int, void*);
void __cdecl fcn_005ae1b0(int, void*);
void __cdecl fcn_005ae3c0(int, void*);
void __cdecl fcn_005ae3e0(int, void*);
void __cdecl fcn_005ae600(int, void*);
void __cdecl fcn_005af140(int, void*);
void __cdecl fcn_005ac250(int, void*);
void __cdecl fcn_0059f190(int, void*);
void __cdecl fcn_005a2db0(int, void*);
void __cdecl fcn_005a2f70(int, void*);
void __cdecl fcn_005a91b0(int, void*);
void __cdecl fcn_005a9c50(int, void*);
void __cdecl fcn_005a9120(int, void*);
void __cdecl fcn_005aad40(int, void*);
void __cdecl fcn_005acb30(int, void*);
void __cdecl fcn_005aaed0(int, void*);
void __cdecl fcn_005aadd0(int, void*);
void __cdecl fcn_005b0010(int, void*);
void __cdecl fcn_005afd20(int, void*);
void __cdecl fcn_005afea0(int, void*);
void __cdecl fcn_0058aad0(int, void*);
void __cdecl fcn_005e51f0(int, void*);
void __cdecl fcn_0058af00(int, void*);
void __cdecl fcn_0058ae60(int, void*);

/* ADDRESS: GOLDTL 0x005a76b0 */
int __cdecl fcn_005a76b0(char* o, int p2)
{
    int r;
    int x;
    int i;
    int t;
    int s0;
    int s1;
    int s2;
    int s3;
    int s4;
    int s5;
    char* msg;
    u8 c;

    r = -1;
    if (fcn_005a74a0(o) == 0) {
        *(int*) 0x7e2700 = 0;
        return 0;
    }
    fcn_00525ef0();
    fcn_005373e0((void*) 0x5a76b0, 0x20007);
    *(int*) 0x6a2520 = 0;
    fcn_00530510();
    fcn_005305a0();
    x = *(int*) 0x6b8010;
    *(int*) 0x7746d0 = 0;
    *(u16*) (o + 0x29) = (u16) p2;
    s0 = *(int*) 0x7e3a40;
    s1 = *(int*) 0x7e3a44;
    s2 = *(int*) 0x7e3a48;
    s3 = *(int*) 0x7e3a50;
    s4 = *(int*) 0x7e3a54;
    s5 = *(int*) 0x7e3a58;
    if (p2 == 0)
        *(int*) 0x7746c4 = 0;
    if (*(u16*) (o + 0x27) == *(u16*) 0x774970)
        fcn_004234e0(*(int*) 0x7747c8, (void*) 0x6aadc8, 1, 0x3f, 0x7f, 0, 0);
    else
        fcn_004234e0(*(int*) 0x7747c8, (void*) 0x6aadac, 1, 0x3f, 0x7f, 0, 0);
    *(int*) 0x6752a8 = *(int*) 0x6aada0;
    *(int*) 0x6752ac = *(int*) 0x6aada4;
    *(u8*) 0x6752b0 = *(u8*) 0x6aada8;
    fcn_00502cd0(*(int*) (o + 0x5d), 1, 0, (int) *(u16*) (o + 0x29));
    fcn_004c3170(o);

    do {
        *(int*) 0x774658 = *(int*) 0x774650 + 1;
        msg = (char*) fcn_00502cd0(*(int*) (o + 0x5d), 1, 0, (int) *(u16*) (o + 0x29));
        if (msg != 0) {
            c = ((u8*) 0x7f3b40)[*(u16*) msg];
            if (c != 0xfe) {
                if (c == 0xff ||
                    *(signed char*) (0x1043695 + 0x3dc * (int) (signed char) c) != 0) {
                    *(int*) 0x7725c8 = 1;
                    fcn_005373e0((void*) 0, 0x603c7);
                    fcn_005373e0((void*) 0, 0x603c7);
                    fcn_00510c90((int) *(u16*) msg);
                    *(int*) 0x7725c8 = 0;
                }
                if (*(int*) 0x6b8010 != 0)
                    fcn_0043a9c0(3);
                *(int*) 0x7746c4 = (int) o;
                *(int*) 0x7746cc = (int) msg;
                *(int*) 0x6791c8 = *(int*) (msg + 2);
                *(int*) 0x67530c = *(int*) (o + 1);
                *(int*) 0x675310 = *(int*) (msg + 2);
                *(u16*) (o + 0x29) = *(u16*) msg;
                fcn_004432d0((int) (signed char) ((u8*) 0x7f3b40)[*(u16*) msg], 0);
                fcn_0043aa30(3);
                fcn_00437ac0((void*) *(int*) 0x67a370, 0, 0xe0, (void*) 0x456df0);
                fcn_005166a0(o);
                t = *(int*) 0x7746c4;
                fcn_005167c0((char*) t, (int) *(u16*) (t + 0x29));
                fcn_00516c50((char*) *(int*) 0x7746c4, (char*) *(int*) 0x7746cc);
                t = *(int*) 0x6b8014;
                fcn_00438b40((void*) t, (char*) t + 0x5c);
                t = *(int*) 0x6b8014;
                fcn_00438cb0((void*) t, (char*) t + 0x90);
                t = *(int*) 0x67a370;
                if (t != 0) {
                    i = *(int*) (t + 0x3c8);
                    if (i != 0) {
                        if (*(int*) (i + 0x210) != 0)
                            ((void (__cdecl*) (int, int, int, int)) *(int*) (i + 0x210))
                                (t, 4, i + 0x214, 0);
                    }
                }
                r = *(int*) 0x6791d0;
                if (*(u16*) (o + 0x27) != *(u16*) 0x774970) {
                    i = fcn_00504bd0((int) *(u8*) o);
                    if (i == 1 || i == 8) {
                        if (fcn_00451840((char*) *(void**) 0x6b8014 + 0x114,
                                         (void*) 0x662d70, 0.1f) == 0) {
                            if (fcn_00451840((char*) *(void**) 0x6b8014 + 0x120,
                                             (void*) 0x662d70, 0.1f) == 0) {
                                t = *(int*) 0x6b8014;
                                fcn_00438b40((void*) t, (char*) t + 0x114);
                                t = *(int*) 0x6b8014;
                                fcn_00438cb0((void*) t, (char*) t + 0x120);
                            }
                        }
                    }
                }
                t = *(int*) 0x6b8014;
                *(int*) 0x7e3a40 = *(int*) (t + 0x4c);
                *(int*) 0x7e3a44 = *(int*) (t + 0x50);
                *(int*) 0x7e3a48 = *(int*) (t + 0x54);
                *(int*) 0x7e3a50 = *(int*) (t + 0x84);
                *(int*) 0x7e3a54 = *(int*) (t + 0x88);
                *(int*) 0x7e3a58 = *(int*) (t + 0x8c);
                *(int*) 0x774688 = 0;
                *(int*) 0x77468c = 0;
            }
            fcn_0057e880(0x19, msg, 0, 0);
            switch (*(u16*) msg) {
    case 0x13:
        fcn_005a07c0(*(int*)0x7746c4, msg);
        break;
    case 0x14:
        fcn_0059f6c0(*(int*)0x7746c4, msg);
        break;
    case 0x16:
        fcn_005a4030(*(int*)0x7746c4, msg);
        break;
    case 0x15:
        fcn_0059f8b0(*(int*)0x7746c4, msg);
        break;
    case 0x17:
        fcn_0059f9b0(*(int*)0x7746c4, msg);
        break;
    case 0x18:
        fcn_005a0250(*(int*)0x7746c4, msg);
        break;
    case 0x1f:
        fcn_005a3820(*(int*)0x7746c4, msg);
        break;
    case 0x74:
        fcn_0059e430(*(int*)0x7746c4, msg);
        break;
    case 0x85:
        fcn_0059e5f0(*(int*)0x7746c4, msg);
        break;
    case 0xcf:
        fcn_0059f3e0(*(int*)0x7746c4, msg);
        break;
    case 0xd6:
        fcn_0059f320(*(int*)0x7746c4, msg);
        break;
    case 0xdd:
        fcn_0059f340(*(int*)0x7746c4, msg);
        break;
    case 0x9b:
        fcn_0059f570(*(int*)0x7746c4, msg);
        break;
    case 0xa5:
        fcn_005a7200(*(int*)0x7746c4, msg);
        break;
    case 0xe5:
    case 0xe6:
        fcn_005acc80(*(int*)0x7746c4, msg);
        break;
    case 0xf0:
        fcn_005ace20(*(int*)0x7746c4, msg);
        break;
    case 0xb7:
        fcn_005acf90(*(int*)0x7746c4, msg);
        break;
    case 0xba:
        fcn_005ad260(*(int*)0x7746c4, msg);
        break;
    case 0xbb:
        fcn_005ad360(*(int*)0x7746c4, msg);
        break;
    case 0x54:
        fcn_005ae1b0(*(int*)0x7746c4, msg);
        break;
    case 0x4d:
        fcn_005ae3c0(*(int*)0x7746c4, msg);
        break;
    case 0x5c:
        fcn_005ae3e0(*(int*)0x7746c4, msg);
        break;
    case 0x60:
        fcn_005ae600(*(int*)0x7746c4, msg);
        break;
    case 0x65:
        fcn_005af140(*(int*)0x7746c4, msg);
        break;
    case 0xf2:
        fcn_005ac250(*(int*)0x7746c4, msg);
        break;
    case 0x118:
        fcn_0059f190(*(int*)0x7746c4, msg);
        break;
    case 0x120:
        fcn_005a2db0(*(int*)0x7746c4, msg);
        break;
    case 0x12e:
        fcn_005a2f70(*(int*)0x7746c4, msg);
        break;
    case 0x10e:
        fcn_005a91b0(*(int*)0x7746c4, msg);
        break;
    case 0x110:
        fcn_005a9c50(*(int*)0x7746c4, msg);
        break;
    case 0x114:
        fcn_005a9120(*(int*)0x7746c4, msg);
        break;
    case 0x137:
        fcn_005aad40(*(int*)0x7746c4, msg);
        break;
    case 0xf7:
        fcn_005acb30(*(int*)0x7746c4, msg);
        break;
    case 0x138:
        fcn_005aaed0(*(int*)0x7746c4, msg);
        break;
    case 0x139:
        fcn_005aadd0(*(int*)0x7746c4, msg);
        break;
    case 0x145:
        fcn_005b0010(*(int*)0x7746c4, msg);
        break;
    case 0x146:
        fcn_005afd20(*(int*)0x7746c4, msg);
        break;
    case 0x14c:
        fcn_005afea0(*(int*)0x7746c4, msg);
        break;
    case 0x24b:
        fcn_0058aad0(*(int*)0x7746c4, msg);
        break;
    case 0x29e:
        fcn_005e51f0(*(int*)0x7746c4, msg);
        break;
    case 0x266:
        fcn_0058af00(*(int*)0x7746c4, msg);
        break;
    case 0x256:
        fcn_0058ae60(*(int*)0x7746c4, msg);
        break;
            default:
                fcn_00597fd0(msg);
                break;
            }
            fcn_0057e880(0x1a, msg, 0, 0);
            *(int*) 0x7746d0 = (int) msg;
            if (r != -1) {
                msg = (char*) fcn_00426cc0(r);
                if (msg != 0) {
                    fcn_00428720(msg);
                    fcn_005312d0(*(int*) (msg + 0x100));
                }
            }
            t = *(int*) 0x67a370;
            if (t != 0) {
                i = *(int*) (t + 0x3c8);
                if (i != 0) {
                    if (*(int*) (i + 0x294) != 0) {
                        ((void (__cdecl*) (int, int, int, int)) *(int*) (i + 0x294))
                            (t, 5, i + 0x298, 0);
                    }
                }
            }
            i = *(int*) 0x6791d0;
            if (i != -1)
                fcn_005312d0(i);
            fcn_00516ed0(o);
            *(int*) 0x774670 = 1;
            if (*(int*) 0x7746c4 == 0) {
                *(int*) 0x774654 = 1;
                fcn_0043a9c0(3);
            }
        }
    } while (fcn_005373e0((void*) 0x5a76b0, 0x67fff) != 0);

    fcn_00530510();
    fcn_005305a0();
    *(int*) 0x7ea360 = 0;
    fcn_004c34d0();
    fcn_004432d0(x, 0);
    *(int*) 0x6791c8 = 0;
    *(int*) 0x67530c = -1;
    *(int*) 0x675310 = -1;
    *(int*) 0x7746c4 = 0;
    *(int*) 0x7746cc = 0;
    fcn_00516f60();
    *(int*) 0x7e3a40 = s0;
    *(int*) 0x7e3a44 = s1;
    *(int*) 0x7e3a48 = s2;
    *(int*) 0x7e3a50 = s3;
    *(int*) 0x7e3a54 = s4;
    *(int*) 0x7e3a58 = s5;
    return fcn_004234e0(*(int*) 0x7747c8, (void*) 0x6aad8c, 1, 0x3f, 0x7f, 0, 0);
}
