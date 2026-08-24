/* gm_InitEntityIfValid - fenced _emit: cross-TU call is reloc in C */

// CFLAGS: /O2 /Gd /DREBREW_ALLOW_NAKED
// FUNCTION: SERVER 0x10017f90
// SYMBOL: _gm_InitEntityIfValid

#ifdef REBREW_ALLOW_NAKED
__declspec(naked) void __cdecl gm_InitEntityIfValid(short* entity)
{
	__asm {
		/* 0x10017f90  mov eax, dword ptr [esp + 4] */
		_emit 0x8b
		_emit 0x44
		_emit 0x24
		_emit 0x04
		/* 0x10017f94  test eax, eax */
		_emit 0x85
		_emit 0xc0
		/* 0x10017f96  je 0x10017fa6 */
		_emit 0x74
		_emit 0x0e
		/* 0x10017f98  cmp word ptr [eax], 0xffff */
		_emit 0x66
		_emit 0x81
		_emit 0x38
		_emit 0xff
		_emit 0xff
		/* 0x10017f9d  je 0x10017fa6 */
		_emit 0x74
		_emit 0x07
		/* 0x10017f9f  push eax */
		_emit 0x50
		/* 0x10017fa0  call 0x1000b990 */
		_emit 0xe8
		_emit 0xeb
		_emit 0x39
		_emit 0xff
		_emit 0xff
		/* 0x10017fa5  pop ecx */
		_emit 0x59
		/* 0x10017fa6  ret  */
		_emit 0xc3
	}
}
#else
void __cdecl gm_InitEntityIfValid(short* entity)
{
    /* C fallback */
}
#endif
