void __cdecl gm_SummarizeBuildingOwnership(int, float*);


/* ADDRESS: GOLDTL 0x004b4ec0 */
int __cdecl gm_HasMinBuildingOwnershipShare(int unused, char* spec)
{
	float v[3];

	gm_SummarizeBuildingOwnership(0, v);
	if (*(int*) (spec + 0x14) * 0.01f <= v[2])
		return 1;
	return 0;
}
