

// SIZE 0x70
typedef struct Item {
	char pad[0x54];
	unsigned char flags;
	char pad2[0x1b];
} Item;

#include "Develop/DieGildeAddOn/game/game_data.h"
extern char* d3_TextureBank;
extern unsigned int d3_TextureBankCount;

void __cdecl d3_ResetMemoryCountFlags(unsigned int flags)
{
	char* p;
	Item* it;
	unsigned int i;

	if ((flags & 4) == 0) {
		for (p = g_1042c38; p != g_1042d00; p = *(char**) (p + 0x1f8)) {
			p[0x2a1] &= 0xfe;
		}
	}
	i = 0;
	if ((flags & 0x10) == 0) {
		for (p = g_1042320; p != g_1052a40; p = *(char**) (p + 0x160)) {
			p[0x16a] = 0;
		}
	}
	if ((flags & 0x100) == 0) {
		it = ((Item*)d3_TextureBank);
		for (; i < d3_TextureBankCount; i++) {
			it[i].flags &= 0xbf;
		}
	}
}
