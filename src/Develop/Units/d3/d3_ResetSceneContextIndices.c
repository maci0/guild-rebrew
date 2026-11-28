extern char init_SceneContextIndices[];
extern char init_SceneContextIndices[];
extern signed char d3_BuildingCategorySceneIndices[];
extern signed char d3_BuildingCategorySceneIndices[];

/* ADDRESS: GOLD 0x0050d460 */
/* ADDRESS: GOLDTL 0x00510900 */
/* ADDRESS: GOLDDE 0x004fb5d0 */
char __cdecl d3_ResetSceneContextIndices(void)
{
	int i;

	for (i = 0; i < 0xb7; i++) {
		((int*) init_SceneContextIndices)[i] = -1;
	}
	for (i = 0; i < 17; i++) {
		((short*) d3_BuildingCategorySceneIndices)[i] = -1;
	}
	return 0;
}
