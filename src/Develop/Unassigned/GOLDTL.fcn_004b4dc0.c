void __cdecl gm_SummarizeBuildingOwnership(int, void*);
int __cdecl ai_FilterCandidateLimit(int, int, int);

struct BUILDING_OWNERSHIP_STATS {
	int value;
	int count;
	float ratio;
};
// SIZE 0xc


/* ADDRESS: GOLDTL 0x004b4dc0 */
int __cdecl gm_HasAllCategoryBuildings(int entity, int holder, char* spec)
{
	struct BUILDING_OWNERSHIP_STATS stats;

	gm_SummarizeBuildingOwnership(0xb, &stats);
	if (stats.count > 0 && stats.ratio < 1.0f)
		return ai_FilterCandidateLimit(holder, 0, *(int*) (spec + 0x18));
	gm_SummarizeBuildingOwnership(0xc, &stats);
	if (stats.count > 0 && stats.ratio < 1.0f)
		return ai_FilterCandidateLimit(holder, 0, *(int*) (spec + 0x18));
	gm_SummarizeBuildingOwnership(0xd, &stats);
	if (stats.count > 0 && stats.ratio < 1.0f)
		return ai_FilterCandidateLimit(holder, 0, *(int*) (spec + 0x18));
	return ai_FilterCandidateLimit(holder, *(int*) (spec + 0x14) <= 3, *(int*) (spec + 0x18));
}
