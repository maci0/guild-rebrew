/* fcn_004d1cf0 — start the worker with the fixed queue geometry. */

void __cdecl d3_VisitSceneObjects(int, int, int, int, int);

/* ADDRESS: GOLDTL 0x004d1cf0 */
void __cdecl d3_CollectCombatArenaMarkers(void)
{
	int handle;

	handle = *(int*) 0x67a370;
	*(int*) 0x772f08 = 0;
	d3_VisitSceneObjects(handle, 0, 0x100, 0x4d1ad0, 0);
}
