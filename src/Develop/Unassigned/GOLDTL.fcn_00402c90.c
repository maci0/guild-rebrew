#include "Develop/DieGildeAddOn/game/game_data.h"

/* ADDRESS: GOLDTL 0x00402c90 */
int __cdecl ch_CountActiveCharacters(int context, int includeHidden)
{
	int count;
	void** p;
	void* e;

	count = 0;
	p = ch_CharacterSlots;
	do {
		e = *p;
		if (e != 0 && *(int*) ((char*) e + 0x124) != 0) {
			if (context == -1 || context == d3_CurrentContextIndex) {
				if (includeHidden != 0 ||
				    *(int*) (*(int*) ((char*) e + 0x34) + 0x218) != 1 ||
				    *(int*) ((char*) e + 0x128) != 0) {
					count++;
				}
			}
		}
		p++;
	} while ((int) p < 0x14d0c20);
	return count;
}
