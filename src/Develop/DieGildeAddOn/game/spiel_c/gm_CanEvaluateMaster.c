typedef struct Ent {
	unsigned short id;
	unsigned char kind;
	char pad3;
	unsigned int seed;
	char pad8[0x21c - 8];
} Ent;
// SIZE 0x21c

extern char gm_EntitySlotTable[];
#include "Develop/DieGildeAddOn/game/game_data.h"
extern unsigned int nt_LocalShardIndex;
extern unsigned char gm_PlayerCount;

/* ADDRESS: GOLDTL 0x0047dd60 */
int __cdecl gm_CanEvaluateMaster(char* e)
{
	char* p;
	unsigned short idx;

	if (e[2] != 1 && e[2] != 2) {
		return 0;
	}
	if (!e[0x164]) {
		return 0;
	}
	p = *(char**) (e + 0x16c);
	if (!p) {
		return 0;
	}
	idx = *(unsigned short*) (p + 0x27);
	if (idx == 0xffff) {
		return 0;
	}
	if (((Ent*)gm_EntitySlotTable)[idx].kind == 7) {
		return 0;
	}
	if (nt_ClientSocket != -1 && ((Ent*)gm_EntitySlotTable)[idx].kind != 6 && ((Ent*)gm_EntitySlotTable)[idx].seed % gm_PlayerCount != nt_LocalShardIndex) {
		return 0;
	}
	return 1;
}
