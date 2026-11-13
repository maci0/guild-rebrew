#include <stdio.h>
extern char* g_item_def_table;
extern char* g_entity_type_table;

#pragma pack(push, 1)
typedef struct GOLD_PRICE_RECORD {
    unsigned char kind;
    char unknown01[0x20];
    unsigned char subtype;
    unsigned int capacity;
    unsigned short weights[4];
    unsigned short children[4];
    unsigned short divisor;
    int cache;
    char unknown3c[5];
} GOLD_PRICE_RECORD;
#pragma pack(pop)
extern char* g_143c860[];
typedef struct GOLD_PRICE_PROTO { unsigned char unknown00[0x233]; unsigned char costs[2]; char unknown235[0x18]; } GOLD_PRICE_PROTO;

/* ADDRESS: GOLD 0x00508820 */
float __cdecl fcn_00508820(int id, int percentage)
{
    GOLD_PRICE_RECORD* record;
    GOLD_PRICE_PROTO* prototype;
    char error[256];
    double quotient;
    double total;
    float price;
    int building;
    int divisor;
    int i;
    unsigned short child;
    unsigned short* children;

    record = &((GOLD_PRICE_RECORD*) g_item_def_table)[id];
    if (record->cache != 0) {
        double cached = (double) (record->cache << 5) * (percentage & 0xff) * 0.01f;
        if (record->subtype == 3) {
            return cached * 1.5f;
        }
        return cached;
    }
    divisor = record->divisor + (record->divisor == 0);
    quotient = (double) record->capacity / divisor;
    building = ((int*) 0x919f80)[id];
    prototype = &((GOLD_PRICE_PROTO*) g_entity_type_table)[building];
    if (building != 0) {
        total = 0.0f;
        for (i = 0; i < 2; i++) {
            total += (unsigned char) prototype->costs[i] *
                896.0f * 0.0013888888888888887;
        }
    } else {
        total = 4.0f;
    }
    price = (float) (quotient * (total * 0.5));
    if (record->kind == 0x17) {
        return price * 2.2f;
    }
    for (i = 0, children = record->children; i < 4; i++, children++) {
        child = *children;
        if (child == 0) {
            break;
        }
        if (child != 0xffff) {
            price = fcn_00508820(child, percentage) * children[-4] /
                record->divisor + price;
        } else {
            sprintf(error, "eval_ObjektPreis2Credits:Unterobjekt f\xfcr '%s' nicht vorhanden!!!",
                g_143c860[id * 2]);
        }
    }
    record->cache = (int) (price * 0.06875f);
    return (float) (percentage & 0xff) * price * 0.01f * 2.2f;
}
