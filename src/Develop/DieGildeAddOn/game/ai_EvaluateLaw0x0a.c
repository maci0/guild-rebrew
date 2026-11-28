extern int gm_GameTime;
extern char gm_ActiveTownIndex;
extern float g_664188, g_664160, g_66417c, g_664178;
extern double g_664180;

int __cdecl gm_MapEntityStatRange(int);
int __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl gm_GetLawEntry(int, int*);
float __cdecl gm_GetBuildingLevelRatio(void);
int __cdecl gm_GetGuildHall(int);
int __cdecl gm_QueryEntities(int, int, int, int, int);
int __cdecl gm_SumQueryEntryValues(int, char);
int __cdecl amt_CalcTotalOfficeSalaries(void);
int __cdecl gm_RandomMod(int n);

/* ADDRESS: GOLDTL 0x00490e20 */
/* ADDRESS: GOLDDE 0x0047fcd0 */
int __cdecl ai_EvaluateLaw0x0a(char* actor, int unused, int* outValue)
{
	int lawInfo[9];
	int mode;
	int cnt;
	int r;
	int cur;
	int p;
	float f;
	int d;
	int owner;

	mode = gm_MapEntityStatRange(*(unsigned char*) (actor + 0x164));
	cnt = 0;
	if (gm_GameTime >= 10) {
		if (gm_StartFilteredEntitySearch(1, 5, 0x17)) { cnt = 1; }
		if (gm_StartFilteredEntitySearch(1, 5, 0x18)) {
			cnt++;
		}
		if (gm_StartFilteredEntitySearch(1, 5, 0x19)) {
			cnt++;
		}
		if (gm_StartFilteredEntitySearch(1, 5, 0x1a)) {
			cnt++;
		}
		if (cnt != 0) {
			gm_GetLawEntry(10, lawInfo);
			f = gm_GetBuildingLevelRatio();
			d = lawInfo[2] - lawInfo[1];
			if (f < g_664188) {
				r = (int) ((float) d * g_664160 + lawInfo[1]);
			} else if (f < g_664180) {
				r = (int) ((float) d * g_66417c + lawInfo[1]);
			} else {
				r = (int) ((float) d * g_664178 + lawInfo[1]);
			}
			if (mode == 1 || mode == 2 || mode == 3 || mode == 5) {
				r--;
			}
			owner = gm_GetGuildHall(1);
			p = gm_QueryEntities(*(int*) ((char*) owner + 0x5d), 2, 6, 0, 0x115);
			cur = gm_SumQueryEntryValues(*(int*) ((char*) p + 0x14), gm_ActiveTownIndex);
			if (cur < amt_CalcTotalOfficeSalaries() * 3) {
				r = r + 1 + (gm_RandomMod(3) & 0xffff);
			}
			if (lawInfo[6] - 3 > r) {
				*outValue = lawInfo[6] - (gm_RandomMod(2) & 0xffff) - 1;
				*outValue = lawInfo[1] > *outValue ? lawInfo[1] : *outValue;
				return 1;
			}
			if (lawInfo[6] + 3 < r) {
				*outValue = (gm_RandomMod(2) & 0xffff) + lawInfo[6] + 1;
				*outValue = lawInfo[2] < *outValue ? lawInfo[2] : *outValue;
				return 1;
			}
		}
	}
	return 0;
}
