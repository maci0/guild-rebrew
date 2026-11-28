


#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d3/client_scene_transform.h"

int __cdecl ch_FindNearbyCharacters(char* self, char** out, float range)
{
	int count;
	char** p;
	char* e;
	char* t;
	char* n;

	count = 0;
	p = ((char**)ch_CharacterSlots);
	do {
		if (count >= 16) {
			break;
		}
		e = *p;
		if (e != 0 && self != e && *(int*) (self + 0x88) == *(int*) (e + 0x88) &&
		    *(int*) (self + 0x2c) == *(int*) (e + 0x2c)) {
			t = *(char**) (e + 0x128);
			if (t == 0 || t[9] != 0x2d) {
				n = *(char**) (e + 0x34);
				if (*(int*) (n + 0x218) != 1 ||
				    (*(char**) (e + 0x22c) != 0 &&
				     *(int*) (*(char**) (e + 0x22c) + 0x218) != 1)) {
					if (CompareVector3WithinTolerance((float*) (*(char**) (self + 0x34) + 0x4c), (float*) (n + 0x4c), range)) {
						out[count] = *p;
						count++;
					}
				}
			}
		}
		p++;
	} while ((int) p < (int) (((char**)ch_CharacterSlots) + 0x300));
	return count;
}
