#include "Develop/DieGildeAddOn/game/building_prototype.h"


typedef struct {
	int id;
	int pad4[3];
	int h;
	char pad14[0x24];
} TRADE_CART_SLOT;
// SIZE 0x38

extern unsigned char* lpGebaeudePROT;
extern unsigned char g_773d75;
#include "client_types.h"
extern Slot_778da0 g_7796e0[16];
extern Slot_778da0 g_778da0[16];
extern double g_664ef8;
extern int g_774698;

int __cdecl d2_GetControlValue(int);
float __cdecl fcn_0050bb50(int id, unsigned char a);

void __cdecl d2_CalcTradeCartCost(unsigned char* building, int unused, int mode)
{
	float sum;
	BUILDING_PROTOTYPE *rec;
	int kind;
	int i;
	int n;
	float v;

	sum = 0.0f;
	rec = &((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*building];
	if (*building == 0x47) {
		kind = *(int*) (building + 0x65);
	} else {
		kind = g_773d75;
	}
	for (i = 0; i < 8; i++) {
		if (((TRADE_CART_SLOT*)g_7796e0)[i].h != -1 && d2_GetControlValue(((TRADE_CART_SLOT*)g_7796e0)[i].h) != 0) {
			n = d2_GetControlValue(((TRADE_CART_SLOT*)g_7796e0)[i].h);
			if (n != 0) {
				if (rec->category == 10) {
					v = (float) (fcn_0050bb50(((TRADE_CART_SLOT*)g_7796e0)[i].id, (char) kind) * g_664ef8);
				} else {
					v = fcn_0050bb50(((TRADE_CART_SLOT*)g_7796e0)[i].id, (char) kind) * *(float*) (building + 0x49);
				}
				if (mode == 2 || mode == 4) {
					v = fcn_0050bb50(((TRADE_CART_SLOT*)g_7796e0)[i].id, building[0x65]);
				}
				sum += n * v;
			}
		}
	}
	for (i = 0; i < 16; i++) {
		if (((TRADE_CART_SLOT*)g_778da0)[i].h != -1 && d2_GetControlValue(((TRADE_CART_SLOT*)g_778da0)[i].h) != 0) {
			n = d2_GetControlValue(((TRADE_CART_SLOT*)g_778da0)[i].h);
			if (n != 0) {
				if (rec->category == 10) {
					v = (float) (fcn_0050bb50(((TRADE_CART_SLOT*)g_778da0)[i].id, (char) kind) * g_664ef8);
				} else {
					v = fcn_0050bb50(((TRADE_CART_SLOT*)g_778da0)[i].id, (char) kind) * *(float*) (building + 0x49);
				}
				if (mode == 2 || mode == 4) {
					v = fcn_0050bb50(((TRADE_CART_SLOT*)g_778da0)[i].id, building[0x65]);
				}
				sum += n * v;
			}
		}
	}
	g_774698 = (int) -sum;
}
