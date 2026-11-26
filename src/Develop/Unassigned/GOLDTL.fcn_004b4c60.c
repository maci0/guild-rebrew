void __cdecl gm_SummarizeBuildingOwnership(int, void*);

struct stat_4b4c60 {
	int value;
	int count;
	float ratio;
};
// SIZE 0xc


/* ADDRESS: GOLDTL 0x004b4c60 */
int __cdecl fcn_004b4c60(int a1, char* a2)
{
	struct stat_4b4c60 s;
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
	return sum >= *(int*) (a2 + 0x14);
}
