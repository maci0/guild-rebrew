#include "Develop/DieGildeAddOn/game/game_data.h"
extern char d3_Universes[];

/* ADDRESS: GOLDTL 0x00402ba0 */
int __cdecl ch_CountCharacters(int contextIndexArg, int includeTypeOne)
{
	int count;
	void** p;
	void* e;

	count = 0;
	p = ch_CharacterSlots;
	do {
		e = *p;
		if (e != 0) {
			if (contextIndexArg == -1 ||
			    *(int*) ((char*) e + 0x88) == (int) (d3_Universes + contextIndexArg * 0x3dc)) {
				if (includeTypeOne != 0 ||
				    *(int*) (*(int*) ((char*) e + 0x34) + 0x218) != 1) {
					count++;
				}
			}
		}
		p++;
	} while ((int) p < 0x14d0c20);
	return count;
}
