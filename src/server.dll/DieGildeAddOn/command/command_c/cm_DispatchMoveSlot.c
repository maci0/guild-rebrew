/* cm_DispatchMoveSlot - proper C */

extern int __cdecl MoveSlotEntry(void*);

/* Dispatch handler: forwards the command payload at offset 0x10 to
 * MoveSlotEntry, which relocates an entity between inventory slots. */

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x100102f0
// SYMBOL: _cm_DispatchMoveSlot
// SIZE: 17

int __cdecl cm_DispatchMoveSlot(void* cmd, char* result_buf)
{
	(void) result_buf;

	return MoveSlotEntry((char*) cmd + 0x10);
}
