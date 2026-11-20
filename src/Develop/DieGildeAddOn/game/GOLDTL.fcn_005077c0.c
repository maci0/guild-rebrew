
#include "Develop/DieGildeAddOn/game/entity_record.h"

extern char g_7f4ca0[];
extern int g_7746d4;

#include "Develop/DieGildeAddOn/game/spiel.h"


void __cdecl fcn_005077c0(int id, int nk)
{
	unsigned char* o;
	int a;
	int b;

	if (nk != ((unsigned char*)&((ENTITY_RECORD*)g_7f4ca0)[id])[0x164]) {
		*(int*) ((unsigned char*)&((ENTITY_RECORD*)g_7f4ca0)[id] + 0x174) = 0;
	}
	o = (unsigned char*) gm_GetEntityTableEntry((char*) ((unsigned char*)&((ENTITY_RECORD*)g_7f4ca0)[id]));
	if (o != 0 && (((unsigned char*)&((ENTITY_RECORD*)g_7f4ca0)[id])[2] == 6 || ((unsigned char*)&((ENTITY_RECORD*)g_7f4ca0)[id])[2] == 7 || ((unsigned char*)&((ENTITY_RECORD*)g_7f4ca0)[id])[2] == 5)) {
		a = gm_MapEntityStatRange(((unsigned char*)&((ENTITY_RECORD*)g_7f4ca0)[id])[0x164]);
		o[a + 0x74] = ((unsigned char*)&((ENTITY_RECORD*)g_7f4ca0)[id])[0x164];
		b = gm_MapEntityStatRange(nk);
		if (nk < o[b + 0x74] || o[b + 0x74] == 0) {
			o[b + 0x74] = (unsigned char) nk;
		}
		g_7746d4 = 1;
	}
	((unsigned char*)&((ENTITY_RECORD*)g_7f4ca0)[id])[0x164] = (unsigned char) nk;
}
