


int __cdecl gm_FindMatchingLawEntry(int);
#include "Develop/DieGildeAddOn/game/spiel.h"
float __cdecl gm_RandomFloat01(void);
void __cdecl gm_TryRecordCrime(int, int, int, int, int);

/* ADDRESS: GOLDDE 0x0055d7b0 */
int __cdecl gm_RecordAssassinEvidence(char* a, char* b, int c)
{
	int k;
	float fa;
	float fb;
	int id;

	k = gm_FindMatchingLawEntry(c);
	if (k >= 0) {
		fa = gm_GetEntitySkill(a, 4);
		fb = gm_GetEntitySkill(b, 4);
		if (gm_RandomFloat01() + (fa - fb * 0.5f) >= 1.0f) {
			if (*(char**) (b + 0x170) != 0) {
				id = *(int*) (*(char**) (b + 0x170) + 1);
			} else if (*(char**) (b + 0x16c) != 0) {
				id = *(int*) (*(char**) (b + 0x16c) + 1);
			} else {
				id = -1;
			}
			gm_TryRecordCrime(k, 1, *(int*) (b + 4), *(int*) (a + 4), id);
			return 1;
		}
	}
	return 0;
}
