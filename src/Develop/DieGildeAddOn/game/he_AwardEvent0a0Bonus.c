#include "Develop/DieGildeAddOn/game/game_data.h"
extern unsigned char gm_ActiveTownIndex;
extern char gm_EntitySlotTable[];

int __cdecl gm_ResolveEntityById(char**, int, int, int);
char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_GetBuildingBonusTier(int);
unsigned short __cdecl gm_RandomMod(int);
float __cdecl gm_CalcEntityFavor(unsigned int, unsigned int, unsigned int);
int __cdecl io_FormatTextBuffer(char*, int, int, int, int);
int __cdecl he_PostEntityMessage(int, int, char*, int, int, char*);
int __cdecl cm_RequestTransferCurrencyNoKill(int, int, unsigned char, int);

/* ADDRESS: GOLDTL 0x0057c9f0 */
/* ADDRESS: GOLDDE 0x00562820 */
void __cdecl he_AwardEvent0a0Bonus(char* action)
{
	char buf[512];
	int handle;
	int bonus;
	float radius;
	unsigned int level;
	int base;
	int kind;
	int count;
	int found;
	unsigned short* ent;
	char* p;

	found = 0;
	gm_ResolveEntityById(&handle, 0, 0, *(int*) (action + 0x10));
	if (handle == 0) {
		return;
	}
	ent = (unsigned short*) gm_LookupEntityRecordById(*(int*) (action + 0xc));
	if (ent == 0) {
		return;
	}
	kind = gm_GetBuildingBonusTier(handle);
	if (kind == 3) {
		level = *(int*) (action + 0xac);
		base = 0;
		bonus = 0;
		if (level < 4) {
			base = 0x14;
			bonus = -0xf;
		}
		else if (level < 7) {
			base = 0xa;
			bonus = -5;
		}
		bonus += 0x19;
		radius = (float) base + 40.0f;
		count = gm_RandomMod(0x18) + 0xf;
	}
	else if (kind == 2) {
		level = *(int*) (action + 0xac);
		base = 0;
		bonus = 0;
		if (level < 4) {
			base = 0xa;
			bonus = -5;
		}
		bonus += 0xf;
		radius = (float) base + 50.0f;
		count = gm_RandomMod(0x10) + 0xc;
	}
	else {
		radius = 70.0f;
		bonus = 0xa;
		count = gm_RandomMod(8) + 0xa;
	}
	count <<= 5;
	for (p = gm_EntitySlotTable; (int) p < (int) (gm_EntitySlotTable + 0x65400); p += 0x21c) {
		if (*(unsigned short*) p != 0xffff && p != (char*) ent
			&& *(unsigned char*) (p + 2) < 0xa) {
			if (radius < gm_CalcEntityFavor(*ent, *(unsigned short*) p, 1)) {
				found++;
			}
		}
	}
	found += bonus;
	bonus = found * count;
	io_FormatTextBuffer(buf, 0x41fa, handle, found, bonus);
	he_PostEntityMessage(*(int*) (ent + 2), -1, buf, 1, 0x5fa, 0);
	cm_RequestTransferCurrencyNoKill(*(int*) (ent + 2), -1, gm_ActiveTownIndex, bonus);
}
