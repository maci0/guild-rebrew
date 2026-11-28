#include <string.h>

extern char gm_EntitySlotTable[];

int __cdecl gm_CheckEntityAgeLimit(unsigned short id);
#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl amt_CheckZunftTaxLaw(int k);
void __cdecl gm_CollectCityTaxOffers(unsigned short id, int* out, int c);
void __cdecl gm_ApplySteuerLaw0aToSlots(unsigned short id, int* out, int c);
void __cdecl gm_ApplyLaw0x0bTaxSlot(unsigned short id, int* out, int c);
void __cdecl gm_CalcLaw0x0dTaxSlot(unsigned short id, int* out, int c);
void __cdecl gm_CalcLaw0x0cTaxSlot(unsigned short id, int* out, int c);

/* ADDRESS: GOLDTL 0x004fcb50 */
/* ADDRESS: GOLDDE 0x004e8680 */
int __cdecl gm_CalcEntityTaxSlots(unsigned short id, int* out, int flag)
{
	int offset;

	offset = id * 0x21c;
	memset(out, 0, 0xe * sizeof(int));
	if (*(unsigned short*) (gm_EntitySlotTable + offset) == 0xffff) {
		return 0;
	}
	if (*(unsigned char*) (gm_EntitySlotTable + offset + 8) == 0) {
		return 0;
	}
	if (gm_CheckEntityAgeLimit(id) != 0) {
		return 0;
	}
	if (amt_CheckZunftTaxLaw(gm_MapEntityStatRange(*(unsigned char*) (gm_EntitySlotTable + offset + 0x164))) != 0) {
		gm_ApplySteuerLaw0aToSlots(id, out, flag);
	} else {
		gm_CollectCityTaxOffers(id, out, flag);
	}
	gm_ApplyLaw0x0bTaxSlot(id, out, flag);
	if (*(int*) (gm_EntitySlotTable + offset + 0x1a8) > 0) {
		gm_CalcLaw0x0dTaxSlot(id, out, flag);
	}
	gm_CalcLaw0x0cTaxSlot(id, out, flag);
	return 1;
}
