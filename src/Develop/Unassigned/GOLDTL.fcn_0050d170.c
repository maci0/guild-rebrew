#include "Develop/DieGildeAddOn/game/object_prototype.h"
#include "Develop/DieGildeAddOn/game/building_prototype.h"

extern unsigned char* lpGebaeudePROT;
extern char* lpObjektePROT;

float __cdecl eval_ObjektPreis2Credits(int k, int n);

int __cdecl gm_GetTypeProductValue(int k)
{
	unsigned char* t;
	int total;
	int i;
	unsigned short w;
	int rec;

	t = (unsigned char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[k];
	total = *(int*) (t + 0x249) * 0xf00;
	for (i = 0; i < 0x40; i++) {
		w = ((unsigned short*) (t + 0x23))[i];
		if (w == 0) {
			break;
		}
		rec = (int)&((OBJECT_PROTOTYPE *)(*(int*)&lpObjektePROT))[w & 0x7fff];
		if (w & 0x8000) {
			total = (int) (eval_ObjektPreis2Credits(*(unsigned char*) rec, 100) + total);
		}
	}
	return total;
}
