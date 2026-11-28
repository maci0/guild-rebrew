#include "Develop/DieGildeAddOn/game/building_prototype.h"


extern int* d2_TutorialState;
extern unsigned char* lpGebaeudePROT;

int __cdecl d2_CheckTutMsg1aNotCat12Node74(int* m);

/* ADDRESS: GOLDDE 0x005657e0 */
int __cdecl d2_CheckTutCh3Cat0aBuildGate(int* m)
{
	if (d2_TutorialState[14] >= 0 && m[0] == 0x25 && m[3] == 0x155) {
		d2_TutorialState[14] = 1;
		return 1;
	}
	if (d2_TutorialState[14] >= 1 && m[1] != 0 && m[0] == 0x24) {
		if (((char) ((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*(unsigned char*) m[1]].category) == 0xa) {
			d2_TutorialState[14] = 2;
			return 1;
		}
		return 0;
	}
	return d2_CheckTutMsg1aNotCat12Node74(m);
}
