#include <string.h>

extern char g_7f4ca0[];

int __cdecl gm_CheckEntityAgeLimit(unsigned short id);
#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl fcn_004eb180(int k);
void __cdecl gm_CollectCityTaxOffers(unsigned short id, int* out, int c);
void __cdecl gm_ApplySteuerLaw0aToSlots(unsigned short id, int* out, int c);
void __cdecl gm_ApplyLaw0x0bTaxSlot(unsigned short id, int* out, int c);
void __cdecl gm_CalcLaw0x0dTaxSlot(unsigned short id, int* out, int c);
void __cdecl gm_CalcLaw0x0cTaxSlot(unsigned short id, int* out, int c);

/* ADDRESS: GOLDTL 0x004fcb50 */
int __cdecl fcn_004fcb50(unsigned short id, int* out, int c)
{
	int o;

	o = id * 0x21c;
	memset(out, 0, 0xe * sizeof(int));
	if (*(unsigned short*) (g_7f4ca0 + o) == 0xffff) {
		return 0;
	}
	if (*(unsigned char*) (g_7f4ca0 + o + 8) == 0) {
		return 0;
	}
	if (gm_CheckEntityAgeLimit(id) != 0) {
		return 0;
	}
	if (fcn_004eb180(gm_MapEntityStatRange(*(unsigned char*) (g_7f4ca0 + o + 0x164))) != 0) {
		gm_ApplySteuerLaw0aToSlots(id, out, c);
	} else {
		gm_CollectCityTaxOffers(id, out, c);
	}
	gm_ApplyLaw0x0bTaxSlot(id, out, c);
	if (*(int*) (g_7f4ca0 + o + 0x1a8) > 0) {
		gm_CalcLaw0x0dTaxSlot(id, out, c);
	}
	gm_CalcLaw0x0cTaxSlot(id, out, c);
	return 1;
}
