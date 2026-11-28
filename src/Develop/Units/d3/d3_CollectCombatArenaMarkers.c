void __cdecl d3_SpawnCombatFlagObjects();
extern char d3_ActiveScene[];
extern char g_772f08[];
/* fcn_004d1cf0 — start the worker with the fixed queue geometry. */

void __cdecl d3_VisitSceneObjects(int, int, int, int, int);

/* ADDRESS: GOLDTL 0x004d1cf0 */
/* ADDRESS: GOLDDE 0x004befe0 */
void __cdecl d3_CollectCombatArenaMarkers(void)
{
	int handle;

	handle = *(int*) &d3_ActiveScene;
	*(int*) &g_772f08 = 0;
	d3_VisitSceneObjects(handle, 0, 0x100, (int) d3_SpawnCombatFlagObjects, 0);
}
