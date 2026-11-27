/* fcn_005107f0 — notify the helper while a global handle is live. */

void __cdecl d3_ReleaseSceneSlotById(int);
void __cdecl d3_RemoveSubTreeFromCellTree(int, int);

/* ADDRESS: GOLDTL 0x005107f0 */
void __cdecl d3_DetachEntitySceneSubtree(int a1)
{
	int handle;

	d3_ReleaseSceneSlotById(a1);
	handle = *(int*) 0x773dd8;
	if (handle != 0) {
		d3_RemoveSubTreeFromCellTree(a1, handle);
	}
}
