#include <stdio.h>
#include "Develop/DieGildeAddOn/game/object_prototype.h"
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

extern float flt_0_0;
extern double g_662908;


extern float flt_4;
extern float g_662acc;
extern double g_665bd8;
extern float g_665be0;

extern unsigned char* g_entity_type_table; /* 0x868050 */
extern int g_99e0a0[];
extern char* lpObjektePROT;
extern int d2_ObjektNameTable[];

#pragma optimize("l", off)
/* ADDRESS: GOLDTL 0x0050b980 */
/* ADDRESS: GOLDDE 0x004f69c0 */
float __cdecl eval_ObjektPreis2Credits(int id, int percent)
{
    OBJECT_PROTOTYPE* r;
    char buf[256];
    float acc;
    float price;
    float q;
    int divisor;
    int buildingType;
    int i;
    unsigned short child;
    char* childp;
    BUILDING_PRICE_ROW* building;

    r = &((OBJECT_PROTOTYPE*) lpObjektePROT)[id];
    if (r->price_cache != 0) {
        price = (float) (r->price_cache << 5) * (percent & 0xff) * 0.01f;
        if (r->subtype == 3) {
            return price * 1.5f;
        }
        return price;
    }

    divisor = (int) r->value_036 + (r->value_036 == 0);
    q = (float) r->value_022 / divisor;
    buildingType = g_99e0a0[id];
    building = (BUILDING_PRICE_ROW*) g_entity_type_table + buildingType;
    if (buildingType) {
        acc = flt_0_0;
        for (i = 0; i < 2; i++) {
            acc += building->unknown233[i] *
                   g_665be0 * g_665bd8;
        }
    } else {
        acc = flt_4;
    }
    price = q * (acc * 0.5);

    if ((*(char *)&r->kind) == 0x17) {
        return price * 2.2f;
    }

    for (i = 0, childp = (char*) r + 0x2e; i < 4; i++, childp += 2) {
        child = *(unsigned short*) childp;
        if (child == 0) {
            break;
        }
        if (child != 0xffff) {
            price = eval_ObjektPreis2Credits(child, percent) * *(unsigned short*) (childp - 8) / r->value_036
                    + price;
        } else {
            sprintf(buf,
                    "eval_ObjektPreis2Credits:Unterobjekt f\xfcr"
                    " '%s' nicht vorhanden!!!",
                    d2_ObjektNameTable[id * 2]);
        }
    }
    r->price_cache = (int) (price * 0.06875f);
    price = (float) (percent & 0xff) * price;
    price *= 0.01f;
    return price * 2.2f;
}
#pragma optimize("", on)
