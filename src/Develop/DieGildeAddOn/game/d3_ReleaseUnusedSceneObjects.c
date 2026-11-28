


int __cdecl d3_CollectUnusedSceneObjects(int, int*);
void __cdecl lc_UpdateBuildingVegetation(int);

/* ADDRESS: GOLDDE 0x0057dcc0 */
void __cdecl d3_ReleaseUnusedSceneObjects(void)
{
	int ids[0x100];
	int n;
	int i;

	n = d3_CollectUnusedSceneObjects(0, ids);
	for (i = 0; i < n; i++) {
		if (ids[i] != 0) {
			lc_UpdateBuildingVegetation(ids[i]);
		}
	}
}
