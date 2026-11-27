#include "Develop/DieGildeAddOn/game/ch_motion.h"

#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl d3_SetObjectPosition(int, void*);

void __cdecl ch_UpdateCharacterObjectPositions(void)
{
	void** p;
	void* e;

	p = ch_CharacterSlots;
	do {
		e = *p;
		if (e != 0 && (*(unsigned char*) ((char*) e + 0x8c) & 1) != 0 &&
		    *(int*) ((char*) e + 0x88) == g_67a370) {
			d3_SetObjectPosition(*(int*) ((char*) e + 0x34), (char*) e + 0x54);
		}
		p++;
	} while ((int) p < (int) (ch_CharacterSlots + 0x300));
}
