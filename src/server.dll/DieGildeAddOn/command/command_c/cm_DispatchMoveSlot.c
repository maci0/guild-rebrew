// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 17
// CFLAGS: /O2 /Gd
// SYMBOL: _DispatchMoveSlotEntry

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 17B
 *    CFlags: 
 *    Symbol: _DispatchMoveSlotEntry
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl DispatchMoveSlotEntry(void *param_1,char *param_2)
 * 
 * {
 *   uint uVar1;
 *   
 *   uVar1 = MoveSlotEntry((int)param_1 + 0x10);
 *   return uVar1;
 * }
 */

extern int __cdecl MoveSlotEntry(int);

// FUNCTION: SERVER 0x100102f0
int __cdecl DispatchMoveSlotEntry(void* param_1, char* param_2)
{
	int result;

	result = MoveSlotEntry((int) param_1 + 0x10);
	return result;
}
