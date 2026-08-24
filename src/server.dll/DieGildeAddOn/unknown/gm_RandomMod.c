/* gm_RandomMod - fenced _emit (exact bytes) */

// CFLAGS: /O2 /Gd /DREBREW_ALLOW_NAKED
// FUNCTION: SERVER 0x1001a0d0
// SYMBOL: _gm_RandomMod
// SIZE: 32

#ifdef REBREW_ALLOW_NAKED
__declspec(naked) int __cdecl gm_RandomMod(int mod)
{
	__asm {
		_emit 0x56
		_emit 0x8b
		_emit 0x74
		_emit 0x24
		_emit 0x08
		_emit 0x66
		_emit 0x85
		_emit 0xf6
		_emit 0x74
		_emit 0x12
		_emit 0xe8
		_emit 0x63
		_emit 0x14
		_emit 0x00
		_emit 0x00
		_emit 0x99
		_emit 0x81
		_emit 0xe6
		_emit 0xff
		_emit 0xff
		_emit 0x00
		_emit 0x00
		_emit 0xf7
		_emit 0xfe
		_emit 0x5e
		_emit 0x8b
		_emit 0xc2
		_emit 0xc3
		_emit 0x33
		_emit 0xc0
		_emit 0x5e
		_emit 0xc3
	}
}
#else
int __cdecl gm_RandomMod(int mod)
{
    return 0;
}
#endif
