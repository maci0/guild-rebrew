extern int gm_GameTime;
extern char gm_ActiveTownIndex;

int __cdecl gm_MapEntityStatRange(int);
void __cdecl gm_GetLawEntry(int, int*);
float __cdecl gm_GetBuildingLevelRatio(void);
int __cdecl gm_GetGuildHall(int);
int __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl gm_SumQueryEntryValues(int, char);
int __cdecl amt_CalcTotalOfficeSalaries(void);
int __cdecl gm_RandomMod(int);

/* ADDRESS: GOLDTL 0x00490c90 */
int __cdecl ai_EvaluateLaw0x09(char* entity, int unused, int* outResult)
{
	int v5[9];
	int mode;
	int targetVal;
	int guildItem;
	int treasuryStock;
	int proposed;
	float levelRatio;
	float scaledVal;
	int rangeSpan;

	mode = gm_MapEntityStatRange(*(unsigned char*) (entity + 0x164));
	if (gm_GameTime >= 4) {
		gm_GetLawEntry(9, v5);
		levelRatio = gm_GetBuildingLevelRatio();
		rangeSpan = v5[2] - v5[1];
		if (levelRatio < *(float*) 0x664188) {
			scaledVal = (float) rangeSpan * *(float*) 0x664160 + v5[1];
		} else if (levelRatio < *(double*) 0x664180) {
			scaledVal = (float) rangeSpan * *(float*) 0x66417c + v5[1];
		} else {
			scaledVal = (float) rangeSpan * *(float*) 0x664178 + v5[1];
		}
		targetVal = (int) scaledVal;
		if (mode != 1 && mode != 2 && mode != 3 && mode != 5) {
			targetVal--;
		}
		guildItem = gm_GetGuildHall(1);
		guildItem = fcn_00502cd0(*(int*) ((char*) guildItem + 0x5d), 2, 6, 0, 0x115);
		treasuryStock = gm_SumQueryEntryValues(*(int*) ((char*) guildItem + 0x14), gm_ActiveTownIndex);
		if (treasuryStock < 3 * (int) ((float) amt_CalcTotalOfficeSalaries() * 0.25f)) {
			targetVal = targetVal + 1 + (gm_RandomMod(3) & 0xffff);
		}
		if (v5[6] - 3 > targetVal) {
			proposed = gm_RandomMod(3) & 0xffff; proposed = v5[6] - proposed;
			*outResult = proposed - 1;
			*outResult = v5[1] > proposed - 1 ? v5[1] : proposed - 1;
			return 1;
		}
		if (v5[6] + 3 < targetVal) {
			proposed = (gm_RandomMod(3) & 0xffff) + v5[6] + 1;
			*outResult = proposed;
			*outResult = v5[2] < proposed ? v5[2] : proposed;
			return 1;
		}
	}
	return 0;
}
