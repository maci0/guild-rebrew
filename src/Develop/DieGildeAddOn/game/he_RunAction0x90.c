void __cdecl he_FreeAction(char*);

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;




char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
int __cdecl cm_SendSetHE(int, char*);
void __cdecl he_ApplyBuildingAura(char*, int, int, int);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);

/* ADDRESS: GOLDDE 0x00560bb0 */
void __cdecl he_RunAction0x90(char* o)
{
	pos14_7f4c00* p;
	char* e;

	if (*(int*) (o + 0x70) == -2 || *(int*) (o + 0x70) == -1) {
		he_FreeAction(o);
	}
	if (o[0x78] & 4) {
		return;
	}
	p = (pos14_7f4c00*) (o + 0x52);
	*p = gm_GameTime;
	e = gm_StartFilteredEntitySearch(1, 1, *(int*) (o + 0xac));
	if (e == 0) {
		cm_SendSetHE(-1, o);
		return;
	}
	if (*(int*) (o + 0x70) != 0) {
		return;
	}
	if (*(int*) (o + 0xb8) < 4) {
		he_ApplyBuildingAura(e, *(int*) (o + 0xb0), *(int*) (o + 0xb4), *(int*) (o + 0xb8));
		gm_AddTime(p, 0, 0x1e, 0);
		(*(int*) (o + 0xb8))++;
		cm_SendSetHE(0, o);
	} else {
		*(int*) (o + 0x70) = -1;
		gm_AddTime(p, 0x16, 0, 0);
		cm_SendSetHE(-1, o);
	}
}
