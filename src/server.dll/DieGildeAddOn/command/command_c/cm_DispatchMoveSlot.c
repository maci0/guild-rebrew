
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

/* Dispatch handler: routes a move-slot command to
 * gv_MoveSlotEntry with the payload at cmd+0x10. */

// FUNCTION: SERVER 0x100102f0
int __cdecl cm_DispatchMoveSlot(void* cmd, char* result_buf)
{
	int rc;

	(void) result_buf;
	rc = gv_MoveSlotEntry((int) cmd + 0x10);
	return rc;
}
