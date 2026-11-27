#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_67536c[];



#include <string.h>

int __cdecl m_alloc(int, char*);

void* __cdecl ch_AllocateCharacterSlot(int index)
{
	void* p;

	p = (void*) m_alloc(0x244, g_67536c);
	memset(p, 0, 0x244);
	if (ch_CharacterSlots[index] != 0) {
		return 0;
	}
	ch_CharacterSlots[index] = p;
	*(int*) p = index;
	return p;
}
