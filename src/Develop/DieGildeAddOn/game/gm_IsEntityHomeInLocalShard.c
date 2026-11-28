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

/* ADDRESS: GOLDTL 0x0047dcf0 */
int __cdecl gm_IsEntityHomeInLocalShard(char* e)
{
	char* o;
	char* p;

	if (e[2] != 0 && e[2] != 1) {
		return 0;
	}
	o = e;
	p = *(char**) (e + 0x16c);
	if (p && *(unsigned short*) (p + 0x27) != 0xffff) {
		o = (char*) &((Ent*)gm_EntitySlotTable)[*(unsigned short*) (p + 0x27)];
	}
	if (nt_ClientSocket != -1 && *(unsigned int*) (o + 4) % gm_PlayerCount != nt_LocalShardIndex) {
		return 0;
	}
	return 1;
}
