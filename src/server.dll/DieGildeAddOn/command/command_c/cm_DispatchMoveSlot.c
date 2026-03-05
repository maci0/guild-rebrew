// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 17

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 17B
 *    CFlags: 
 *    Symbol: _DispatchMoveSlotEntry
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_DispatchMoveSlot(void *param_1,char *param_2)
 * 
 * {
 *   uint uVar1;
 *   
 *   uVar1 = gv_MoveSlotEntry((int)param_1 + 0x10);
 *   return uVar1;
 * }
 */

int __cdecl gv_MoveSlotEntry(int);

// FUNCTION: SERVER 0x100102f0
int __cdecl cm_DispatchMoveSlot(void* param_1, char* param_2)
{
	int result;

	result = gv_MoveSlotEntry((int) param_1 + 0x10);
	return result;
}
