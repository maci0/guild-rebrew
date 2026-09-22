/* cm_DispatchMoveSlot - proper C */

extern int __cdecl gv_MoveSlotEntry(void*);

/* Dispatch handler: forwards the command payload at offset 0x10 to
 * gv_MoveSlotEntry, which relocates an entity between inventory slots. */

// FUNCTION: SERVER 0x100102f0
// SIZE: 17

int __cdecl cm_DispatchMoveSlot(void* cmd, char* result_buf)
{
	(void) result_buf;

	return gv_MoveSlotEntry((char*) cmd + 0x10);
}
