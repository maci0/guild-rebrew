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

typedef struct BUILDING_PRICE_ROW {
    unsigned char unknown000[0x233];
    unsigned char unknown233[2];
    unsigned char unknown235[0x18];
} BUILDING_PRICE_ROW;

extern float g_6628a8;
extern double g_662908;


extern float g_662ac8;
extern float g_662acc;
extern double g_665bd8;
extern float g_665be0;

#include "GOLDTL.fcn_0050b980_gconf.h"
extern int g_99e0a0[];
extern char* lpObjektePROT;
extern int g_14a79c0[];

#pragma optimize("l", off)
/* ADDRESS: GOLDTL 0x0050b980 */
float __cdecl eval_ObjektPreis2Credits(int id, int a1)
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
    char* childp;
    BUILDING_PRICE_ROW* building;

    r = &((fcn_0050b980_Rec*) lpObjektePROT)[id];
    if (r->cache != 0) {
        price = (float) (r->cache << 5) * (a1 & 0xff) * 0.01f;
        if (r->sub == 3) {
            return price * g_662acc;
        }
        return price;
    }

    divisor = (int) r->div + (r->div == 0);
    q = (float) r->cap / divisor;
    v6 = g_99e0a0[id];
    building = (BUILDING_PRICE_ROW*) g_entity_type_table + v6;
    if (v6) {
        acc = g_6628a8;
        for (i = 0; i < 2; i++) {
            acc += building->unknown233[i] *
                   g_665be0 * g_665bd8;
        }
    } else {
        acc = g_662ac8;
    }
    price = q * (acc * g_662908);

    if (r->type == 0x17) {
        return price * 2.2f;
    }

    for (i = 0, childp = (char*) r + 0x2e; i < 4; i++, childp += 2) {
        child = *(unsigned short*) childp;
        if (child == 0) {
            break;
        }
        if (child != 0xffff) {
            price = eval_ObjektPreis2Credits(child, a1) * *(unsigned short*) (childp - 8) / r->div
                    + price;
        } else {
            sprintf(buf,
                    "eval_ObjektPreis2Credits:Unterobjekt f\xfcr"
                    " '%s' nicht vorhanden!!!",
                    g_14a79c0[id * 2]);
        }
    }
    r->cache = (int) (price * 0.06875f);
    price = (float) (a1 & 0xff) * price;
    price *= 0.01f;
    return price * 2.2f;
}
#pragma optimize("", on)
