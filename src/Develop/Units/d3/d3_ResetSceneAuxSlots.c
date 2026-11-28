void __cdecl d3_CleanupObjectAuxSlots();
extern char d3_ActiveScene[];


void __cdecl d3_TraverseSceneObjects(int, int, int, int);

/* ADDRESS: GOLDDE 0x0044c420 */
void __cdecl d3_ResetSceneAuxSlots(void)
{
	d3_TraverseSceneObjects(*(int*) &d3_ActiveScene, 0, 0xc0, (int) d3_CleanupObjectAuxSlots);
}
