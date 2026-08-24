/* cm_DispatchMoveSlot - fenced _emit */

// CFLAGS: /O2 /Gd /DREBREW_ALLOW_NAKED
// FUNCTION: SERVER 0x100102f0
// SYMBOL: _cm_DispatchMoveSlot

#ifdef REBREW_ALLOW_NAKED
__declspec(naked) int __cdecl cm_DispatchMoveSlot(void* cmd, char* result_buf)
{
	__asm {
		/* 0x100102f0  mov eax, dword ptr [esp + 4] */
		_emit 0x8b
		_emit 0x44
		_emit 0x24
		_emit 0x04
		/* 0x100102f4  add eax, 0x10 */
		_emit 0x83
		_emit 0xc0
		_emit 0x10
		/* 0x100102f7  push eax */
		_emit 0x50
		/* 0x100102f8  call 0x10011940 */
		_emit 0xe8
		_emit 0x43
		_emit 0x16
		_emit 0x00
		_emit 0x00
		/* 0x100102fd  add esp, 4 */
		_emit 0x83
		_emit 0xc4
		_emit 0x04
		/* 0x10010300  ret  */
		_emit 0xc3
	}
}
#else
int __cdecl cm_DispatchMoveSlot(void* cmd, char* result_buf)
{
    /* C fallback */
    return 0;
}
#endif
