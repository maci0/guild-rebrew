#pragma pack(push, 1)
typedef struct Rec {
    char type;
    char pad1[0x21];
    unsigned int cap;
    unsigned short weight[4];
    char pad2e[8];
    unsigned short div;
    char pad38[9];
} Rec;
#pragma pack(pop)
#include "Develop/DieGildeAddOn/game/object_prototype.h"
extern char* lpObjektePROT;

/* ADDRESS: GOLDTL 0x0050b840 */
/* ADDRESS: GOLDDE 0x004f6880 */
float __cdecl gm_CalcGoodBaseValue(int id)
{
	unsigned char* base;
	float acc;
	int i;
	int t;
	OBJECT_PROTOTYPE* r;

	base = *(unsigned char**) 0x868050;
	t = ((int*) 0x99e0a0)[id];
	acc = 0.0f;
	for (i = 0; i < 2; i++) {
		acc += base[t * 0x24d + 0x233 + i] * 896.0f * 0.0013888888888888887;
	}
	r = (OBJECT_PROTOTYPE*) lpObjektePROT + id;
	return acc * r->value_022 / r->value_036;
}
