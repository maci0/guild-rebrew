/* gm_NoopRet2 — fenced _emit. */

// CFLAGS: /O2 /Gd /DREBREW_ALLOW_NAKED
// FUNCTION: SERVER 0x10016670

#ifdef REBREW_ALLOW_NAKED
__declspec(naked) int __cdecl gm_NoopRet2(int a, int b, int c)
{
	__asm {
		_emit 0xc3
		_emit 0x90
		_emit 0x90
		_emit 0x90
		_emit 0x90
		_emit 0x90
		_emit 0x90
		_emit 0x90
		_emit 0x90
		_emit 0x90
		_emit 0x90
		_emit 0x90
		_emit 0x90
		_emit 0x90
		_emit 0x90
		_emit 0x90
	}
}
#else
int __cdecl gm_NoopRet2(int a, int b, int c) { return 0; }
#endif
