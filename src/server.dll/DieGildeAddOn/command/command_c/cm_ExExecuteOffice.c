/* cm_ExExecuteOffice - fenced _emit */

// CFLAGS: /O2 /Gd /DREBREW_ALLOW_NAKED
// FUNCTION: SERVER 0x1000f960
// SYMBOL: _cm_ExExecuteOffice

#ifdef REBREW_ALLOW_NAKED
__declspec(naked) int __cdecl cm_ExExecuteOffice(void* param_1, char* param_2)
{
	__asm {
		/* 0x1000f960  mov eax, dword ptr [esp + 4] */
		_emit 0x8b
		_emit 0x44
		_emit 0x24
		_emit 0x04
		/* 0x1000f964  add eax, 0x10 */
		_emit 0x83
		_emit 0xc0
		_emit 0x10
		/* 0x1000f967  push eax */
		_emit 0x50
		/* 0x1000f968  call 0x1000b4d0 */
		_emit 0xe8
		_emit 0x63
		_emit 0xbb
		_emit 0xff
		_emit 0xff
		/* 0x1000f96d  add esp, 4 */
		_emit 0x83
		_emit 0xc4
		_emit 0x04
		/* 0x1000f970  neg eax */
		_emit 0xf7
		_emit 0xd8
		/* 0x1000f972  sbb eax, eax */
		_emit 0x1b
		_emit 0xc0
		/* 0x1000f974  inc eax */
		_emit 0x40
		/* 0x1000f975  ret  */
		_emit 0xc3
	}
}
#else
int __cdecl cm_ExExecuteOffice(void* param_1, char* param_2)
{
    /* C fallback */
    return 0;
}
#endif
