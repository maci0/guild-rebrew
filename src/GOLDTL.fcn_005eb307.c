/* Native body is a lock-wrapped tail thunk with a frame:
 *   push ebp / mov ebp, esp / push 1 / call 0x00613478 / pop ebp /
 *   jmp dword ptr [0x006ad674]
 * Its 17-byte extent ends at the jmp; the remaining 81 stored bytes are five
 * further routines that the inventory merged into this SIZE. */
void __stdcall fcn_00613478(int);

#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x005eb307 */
int __stdcall fcn_005eb307(int unused)
{
	fcn_00613478(1);
	return (*(int (__stdcall**)(void)) 0x6ad674)();
}
