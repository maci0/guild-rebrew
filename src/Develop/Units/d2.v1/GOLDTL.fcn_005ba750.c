#include "Develop/DieGildeAddOn/game/building_prototype.h"


typedef struct {
	int id;
	int pad4[3];
	int h;
	char pad14[0x24];
} Slot5ba7;
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

void __cdecl fcn_005af160(unsigned char* p, int unused, int mode)
{
	float sum;
	BUILDING_PROTOTYPE *rec;
	int kind;
	int i;
	int n;
	float v;

	sum = 0.0f;
	rec = &((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*p];
	if (*p == 0x47) {
		kind = *(int*) (p + 0x65);
	} else {
		kind = g_773d75;
	}
	for (i = 0; i < 8; i++) {
		if (((Slot5ba7*)g_7796e0)[i].h != -1 && d2_GetControlValue(((Slot5ba7*)g_7796e0)[i].h) != 0) {
			n = d2_GetControlValue(((Slot5ba7*)g_7796e0)[i].h);
			if (n != 0) {
				if (rec->category == 10) {
					v = (float) (fcn_0050bb50(((Slot5ba7*)g_7796e0)[i].id, (char) kind) * g_664ef8);
				} else {
					v = fcn_0050bb50(((Slot5ba7*)g_7796e0)[i].id, (char) kind) * *(float*) (p + 0x49);
				}
				if (mode == 2 || mode == 4) {
					v = fcn_0050bb50(((Slot5ba7*)g_7796e0)[i].id, p[0x65]);
				}
				sum += n * v;
			}
		}
	}
	for (i = 0; i < 16; i++) {
		if (((Slot5ba7*)g_778da0)[i].h != -1 && d2_GetControlValue(((Slot5ba7*)g_778da0)[i].h) != 0) {
			n = d2_GetControlValue(((Slot5ba7*)g_778da0)[i].h);
			if (n != 0) {
				if (rec->category == 10) {
					v = (float) (fcn_0050bb50(((Slot5ba7*)g_778da0)[i].id, (char) kind) * g_664ef8);
				} else {
					v = fcn_0050bb50(((Slot5ba7*)g_778da0)[i].id, (char) kind) * *(float*) (p + 0x49);
				}
				if (mode == 2 || mode == 4) {
					v = fcn_0050bb50(((Slot5ba7*)g_778da0)[i].id, p[0x65]);
				}
				sum += n * v;
			}
		}
	}
	g_774698 = (int) -sum;
}
