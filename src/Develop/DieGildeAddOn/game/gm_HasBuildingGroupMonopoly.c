void __cdecl gm_SummarizeBuildingOwnership(int, void*);

struct BUILDING_OWNERSHIP_SUMMARY {
	int value;
	int count;
	float ratio;
};
// SIZE 0xc


/* ADDRESS: GOLDTL 0x004b4c60 */
/* ADDRESS: GOLDDE 0x004a2f50 */
int __cdecl gm_HasBuildingGroupMonopoly(int unused_id, char* thr)
{
	struct BUILDING_OWNERSHIP_SUMMARY s;
	int sum;

	gm_SummarizeBuildingOwnership(0x15, &s);
	if (s.count > 0 && s.ratio < 1.0f)
		return 0;
	sum = s.value;
	gm_SummarizeBuildingOwnership(0x14, &s);
	if (s.count > 0 && s.ratio < 1.0f)
		return 0;
	sum += s.value;
	gm_SummarizeBuildingOwnership(0x12, &s);
	if (s.count > 0 && s.ratio < 1.0f)
		return 0;
	sum += s.value;
	gm_SummarizeBuildingOwnership(0x16, &s);
	if (s.count > 0 && s.ratio < 1.0f)
		return 0;
	sum += s.value;
	gm_SummarizeBuildingOwnership(8, &s);
	if (s.count > 0 && s.ratio < 1.0f)
		return 0;
	sum += s.value;
	gm_SummarizeBuildingOwnership(9, &s);
	if (s.count > 0 && s.ratio < 1.0f)
		return 0;
	sum += s.value;
	return sum >= *(int*) (thr + 0x14);
}
