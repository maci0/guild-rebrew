/* cm_ChkOfficeCandidate - fenced _emit */

// CFLAGS: /O2 /Gd /DREBREW_ALLOW_NAKED
// FUNCTION: SERVER 0x1000d020
// SYMBOL: _cm_ChkOfficeCandidate

#ifdef REBREW_ALLOW_NAKED
__declspec(naked) int __cdecl cm_ChkOfficeCandidate(void* obj)
{
	__asm {
		/* 0x1000d020  mov eax, dword ptr [esp + 4] */
		_emit 0x8b
		_emit 0x44
		_emit 0x24
		_emit 0x04
		/* 0x1000d024  add eax, 0x10 */
		_emit 0x83
		_emit 0xc0
		_emit 0x10
		/* 0x1000d027  push eax */
		_emit 0x50
		/* 0x1000d028  call 0x1000b1c0 */
		_emit 0xe8
		_emit 0x93
		_emit 0xe1
		_emit 0xff
		_emit 0xff
		/* 0x1000d02d  add esp, 4 */
		_emit 0x83
		_emit 0xc4
		_emit 0x04
		/* 0x1000d030  neg eax */
		_emit 0xf7
		_emit 0xd8
		/* 0x1000d032  sbb eax, eax */
		_emit 0x1b
		_emit 0xc0
		/* 0x1000d034  inc eax */
		_emit 0x40
		/* 0x1000d035  ret  */
		_emit 0xc3
	}
}
#else
int __cdecl cm_ChkOfficeCandidate(void* obj)
{
    /* C fallback */
    return 0;
}
#endif
