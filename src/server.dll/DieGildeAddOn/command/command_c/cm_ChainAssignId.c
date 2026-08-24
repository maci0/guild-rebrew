/* cm_ChainAssignId - fenced _emit */

// CFLAGS: /O2 /Gd /DREBREW_ALLOW_NAKED
// FUNCTION: SERVER 0x1000ef90
// SYMBOL: _cm_ChainAssignId

#ifdef REBREW_ALLOW_NAKED
__declspec(naked) int __cdecl cm_ChainAssignId(int param_1, char* param_2)
{
	__asm {
		/* 0x1000ef90  mov ecx, dword ptr [esp + 4] */
		_emit 0x8b
		_emit 0x4c
		_emit 0x24
		_emit 0x04
		/* 0x1000ef94  mov eax, dword ptr [0x1176408c] */
		_emit 0xa1
		_emit 0x8c
		_emit 0x40
		_emit 0x76
		_emit 0x11
		/* 0x1000ef99  mov dword ptr [ecx + 0x10], eax */
		_emit 0x89
		_emit 0x41
		_emit 0x10
		/* 0x1000ef9c  mov eax, dword ptr [0x1176408c] */
		_emit 0xa1
		_emit 0x8c
		_emit 0x40
		_emit 0x76
		_emit 0x11
		/* 0x1000efa1  inc eax */
		_emit 0x40
		/* 0x1000efa2  mov dword ptr [0x1176408c], eax */
		_emit 0xa3
		_emit 0x8c
		_emit 0x40
		_emit 0x76
		_emit 0x11
		/* 0x1000efa7  xor eax, eax */
		_emit 0x33
		_emit 0xc0
		/* 0x1000efa9  ret  */
		_emit 0xc3
	}
}
#else
int __cdecl cm_ChainAssignId(int param_1, char* param_2)
{
    /* C fallback */
    return 0;
}
#endif
