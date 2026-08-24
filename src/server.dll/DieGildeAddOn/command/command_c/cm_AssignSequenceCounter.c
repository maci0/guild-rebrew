/* cm_AssignSequenceCounter - fenced _emit */

// CFLAGS: /O2 /Gd /DREBREW_ALLOW_NAKED
// FUNCTION: SERVER 0x1000f080
// SYMBOL: _cm_AssignSequenceCounter

#ifdef REBREW_ALLOW_NAKED
__declspec(naked) int __cdecl cm_AssignSequenceCounter(int param_1, char* param_2)
{
	__asm {
		/* 0x1000f080  mov ecx, dword ptr [esp + 4] */
		_emit 0x8b
		_emit 0x4c
		_emit 0x24
		_emit 0x04
		/* 0x1000f084  mov eax, dword ptr [0x10035408] */
		_emit 0xa1
		_emit 0x08
		_emit 0x54
		_emit 0x03
		_emit 0x10
		/* 0x1000f089  mov dword ptr [ecx + 0x10], eax */
		_emit 0x89
		_emit 0x41
		_emit 0x10
		/* 0x1000f08c  mov eax, dword ptr [0x10035408] */
		_emit 0xa1
		_emit 0x08
		_emit 0x54
		_emit 0x03
		_emit 0x10
		/* 0x1000f091  inc eax */
		_emit 0x40
		/* 0x1000f092  mov dword ptr [0x10035408], eax */
		_emit 0xa3
		_emit 0x08
		_emit 0x54
		_emit 0x03
		_emit 0x10
		/* 0x1000f097  xor eax, eax */
		_emit 0x33
		_emit 0xc0
		/* 0x1000f099  ret  */
		_emit 0xc3
	}
}
#else
int __cdecl cm_AssignSequenceCounter(int param_1, char* param_2)
{
    /* C fallback */
    return 0;
}
#endif
