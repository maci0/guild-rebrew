/* cm_ExSimCommand - fenced _emit */

// CFLAGS: /O2 /Gd /DREBREW_ALLOW_NAKED
// FUNCTION: SERVER 0x10010080
// SYMBOL: _cm_ExSimCommand

#ifdef REBREW_ALLOW_NAKED
__declspec(naked) int __cdecl cm_ExSimCommand(void* param_1, char* param_2)
{
	__asm {
		/* 0x10010080  mov eax, dword ptr [esp + 4] */
		_emit 0x8b
		_emit 0x44
		_emit 0x24
		_emit 0x04
		/* 0x10010084  add eax, 0x10 */
		_emit 0x83
		_emit 0xc0
		_emit 0x10
		/* 0x10010087  push eax */
		_emit 0x50
		/* 0x10010088  call 0x1000b880 */
		_emit 0xe8
		_emit 0xf3
		_emit 0xb7
		_emit 0xff
		_emit 0xff
		/* 0x1001008d  add esp, 4 */
		_emit 0x83
		_emit 0xc4
		_emit 0x04
		/* 0x10010090  neg eax */
		_emit 0xf7
		_emit 0xd8
		/* 0x10010092  sbb eax, eax */
		_emit 0x1b
		_emit 0xc0
		/* 0x10010094  inc eax */
		_emit 0x40
		/* 0x10010095  ret  */
		_emit 0xc3
	}
}
#else
int __cdecl cm_ExSimCommand(void* param_1, char* param_2)
{
    /* C fallback */
    return 0;
}
#endif
