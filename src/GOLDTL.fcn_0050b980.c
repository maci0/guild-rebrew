#include <stdio.h>

#pragma pack(push, 1)
typedef struct fcn_0050b980_Rec {
    char type;                  /* +0x00 */
    char pad1[0x20];            /* +0x01 */
    unsigned char sub;          /* +0x21 */
    unsigned int cap;           /* +0x22 */
    unsigned short weight[4];   /* +0x26 */
    unsigned short child[4];    /* +0x2e */
    unsigned short div;         /* +0x36 */
    int cache;                  /* +0x38 */
    char pad3c[5];
} fcn_0050b980_Rec;             /* SIZE 0x41 */
#pragma pack(pop)

extern float g_6628a8;
extern double g_662908;
extern float g_662910;
extern float g_6629b4;
extern float g_662ac8;
extern float g_662acc;
extern double g_665bd8;
extern float g_665be0;
extern float g_665be4;
extern unsigned char* g_entity_type_table; /* 0x868050 */
extern int g_99e0a0[];
extern char* g_99ec10;
extern int g_14a79c0[];

#pragma optimize("l", off)
/* ADDRESS: GOLDTL 0x0050b980 */
float __cdecl fcn_0050b980(int id, int a1)
{
    fcn_0050b980_Rec* r;
    char buf[256];
    float acc;
    float price;
    float q;
    int divisor;
    int v6;
    int i;
    unsigned short child;

    r = &((fcn_0050b980_Rec*) g_99ec10)[id];
    if (r->cache != 0) {
        price = (float) (r->cache << 5) * (a1 & 0xff) * g_662910;
        if (r->sub == 3) {
            return price * g_662acc;
        }
        return price;
    }

    divisor = r->div ? (int) r->div : 1;
    q = (float) r->cap / divisor;
    v6 = g_99e0a0[id];
    if (v6) {
        acc = g_6628a8;
        for (i = 0; i < 2; i++) {
            acc += g_entity_type_table[v6 + v6 * 0x24d + 0x233 + i] *
                   g_665be0 * g_665bd8;
        }
    } else {
        acc = g_662ac8;
    }
    price = q * (acc * g_662908);

    if (r->type == 0x17) {
        return price * g_6629b4;
    }

    for (i = 0; i < 4; i++) {
        child = r->child[i];
        if (child == 0) {
            break;
        }
        if (child != 0xffff) {
            price = fcn_0050b980(child, a1) * r->weight[i] / r->div
                    + price;
        } else {
            sprintf(buf,
                    "eval_ObjektPreis2Credits:Unterobjekt f\x81r"
                    " '%s' nicht vorhanden!!!",
                    g_14a79c0[id * 2]);
        }
    }
    r->cache = (int) (price * g_665be4);
    return (float) (a1 & 0xff) * price * g_662910 * g_6629b4;
}
#pragma optimize("", on)
