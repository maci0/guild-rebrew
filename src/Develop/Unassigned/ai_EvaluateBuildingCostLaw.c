int __cdecl gm_GetLawEntry(int idx, void* dst);


/* ADDRESS: GOLDTL 0x00490bb0 */
int __cdecl ai_EvaluateBuildingCostLaw(char* e, int unused, int* out)
{
	int info[9];
	int n;
	int level;

	n = (int) ((*(float*) (e + 0xac) - 2.0f) * 5.0f);
	if (n < 4)
		level = n;
	else
		level = 4;
	gm_GetLawEntry(6, info);
	if (level != info[6]) {
		*out = level;
		return 1;
	}
	return 0;
}
