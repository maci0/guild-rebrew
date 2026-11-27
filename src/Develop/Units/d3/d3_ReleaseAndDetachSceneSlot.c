
// fcn_0050d350 — fcn_0053ee40(a); if([0x6f1c28]) fcn_00458770(a, [0x6f1c28]).

int __cdecl d3_ReleaseSceneSlotById(int);
int __cdecl d3_RemoveSubTreeFromCellTree(int, int);

void __cdecl d3_ReleaseAndDetachSceneSlot(int slotId)
{
	d3_ReleaseSceneSlotById(slotId);
	if (*(int*) 0x6f1c28 != 0) {
		d3_RemoveSubTreeFromCellTree(slotId, *(int*) 0x6f1c28);
	}
}
