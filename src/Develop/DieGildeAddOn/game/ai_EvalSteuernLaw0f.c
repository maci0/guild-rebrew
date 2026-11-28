


#include <stdlib.h>
#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned char gm_ActiveTownIndex;

int __cdecl gm_GetLawEntry(int idx, void* dst);
float __cdecl gm_GetBuildingLevelRatio(void);
char* __cdecl gm_GetGuildHall(int k);
char* __cdecl gm_QueryEntities(int, int, int, int, int);
int __cdecl gm_SumQueryEntryValues(int a, char b);
int __cdecl amt_CalcTotalOfficeSalaries(void);

/* ADDRESS: GOLDDE 0x004801f0 */
int __cdecl ai_EvalSteuernLaw0f(char* entity, char* unused, int* out)
{
	int info[9];
	char* p;
	int v;
	int t;
	int lvl;

	if ((*(int*)&gm_GameTime) < 4) {
		return 0;
	}
	gm_GetLawEntry(0xf, info);
	gm_GetBuildingLevelRatio();
	p = gm_GetGuildHall(1);
	p = gm_QueryEntities(*(int*) (p + 0x5d), 2, 6, 0, 0x115);
	v = gm_SumQueryEntryValues(*(int*) (p + 0x14), (*(char*)&gm_ActiveTownIndex));
	t = amt_CalcTotalOfficeSalaries();
	if (v < t * 3) {
		lvl = 4;
	} else if (v > t * 12) {
		lvl = 0;
	} else if (v > t * 8) {
		lvl = 1;
	} else {
		lvl = (v <= t * 6) + 2;
	}
	if (abs(info[6] - lvl) < 2) {
		return 0;
	}
	if (lvl > info[6]) {
		lvl = info[6] + 1;
	} else if (lvl < info[6]) {
		lvl = info[6] - 1;
	}
	*out = max(min(lvl, info[2]), info[1]);
	return 1;
}
