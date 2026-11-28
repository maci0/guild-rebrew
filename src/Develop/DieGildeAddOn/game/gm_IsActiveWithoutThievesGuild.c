extern unsigned char* lpGebaeudeINST;
extern unsigned char* lpGebaeudePROT;
#include "Develop/DieGildeAddOn/game/building_prototype.h"

/* ADDRESS: GOLDTL 0x00510170 */
/* ADDRESS: GOLDDE 0x004fae40 */
int __cdecl gm_IsActiveWithoutThievesGuild(char* a)
{
	char* p;
	int i;

	if (a[0x1b1] == 0) {
		return 0;
	}
	p = ((char*)lpGebaeudeINST);
	for (i = 0; i < 0x100; i++) {
		if (*p != 0 && ((char) ((BUILDING_PROTOTYPE *)lpGebaeudePROT)[(unsigned char) *p].category) == 4 &&
		    *(int*) (p + 0x65) == *(int*) (a + 4)) {
			return 0;
		}
		p += 0xa9;
	}
	return 1;
}
