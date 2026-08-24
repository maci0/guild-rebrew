/* gm_RandomFloat01 - fenced _emit: rand() call + data constant both reloc in C */

// CFLAGS: /O2 /Gd /DREBREW_ALLOW_NAKED
// FUNCTION: SERVER 0x1001a0f0
// SYMBOL: _gm_RandomFloat01

#ifdef REBREW_ALLOW_NAKED
__declspec(naked) double __cdecl gm_RandomFloat01(void)
{
	__asm {
		/* 0x1001a0f0  push ecx */
		_emit 0x51
		/* 0x1001a0f1  call 0x1001b542 */
		_emit 0xe8
		_emit 0x4c
		_emit 0x14
		_emit 0x00
		_emit 0x00
		/* 0x1001a0f6  mov dword ptr [esp], eax */
		_emit 0x89
		_emit 0x44
		_emit 0x24
		_emit 0x00
		/* 0x1001a0fa  fild dword ptr [esp] */
		_emit 0xdb
		_emit 0x44
		_emit 0x24
		_emit 0x00
		/* 0x1001a0fe  fmul dword ptr [0x10025fbc] */
		_emit 0xd8
		_emit 0x0d
		_emit 0xbc
		_emit 0x5f
		_emit 0x02
		_emit 0x10
		/* 0x1001a104  pop ecx */
		_emit 0x59
		/* 0x1001a105  ret  */
		_emit 0xc3
	}
}
#else
double __cdecl gm_RandomFloat01(void)
{
    /* C fallback */
    return 0.0;
}
#endif
