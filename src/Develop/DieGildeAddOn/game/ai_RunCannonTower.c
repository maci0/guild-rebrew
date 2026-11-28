#include "Develop/DieGildeAddOn/game/spiel.h"

int __cdecl ai_FireCannonVolley(int a1, int x);

/* ADDRESS: GOLDTL 0x0048e780 */
/* ADDRESS: GOLDDE 0x0047d650 */
int __cdecl ai_RunCannonTower(int a1, char* firstEntry, char* secondEntry)
{
	int firstEntity;
	int secondEntity;

	if (firstEntry[0] != 4 || secondEntry[0] != 4) {
		return 0;
	}
	gm_ResolveEntityById((void**) (&firstEntity), 0, 0, *(int*) (firstEntry + 4));
	if (!firstEntity) {
		return 0;
	}
	gm_ResolveEntityById((void**) (&secondEntity), 0, 0, *(int*) (secondEntry + 4));
	if (!secondEntity) {
		return 0;
	}
	return ai_FireCannonVolley(a1, firstEntity) ? 0x42 : 0;
}
