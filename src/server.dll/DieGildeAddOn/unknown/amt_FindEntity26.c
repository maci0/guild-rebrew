/* amt_FindEntity26 - fenced _emit (exact bytes) */

// CFLAGS: /O2 /Gd /DREBREW_ALLOW_NAKED
// FUNCTION: SERVER 0x1000b820
// SYMBOL: _amt_FindEntity26
// SIZE: 42

#ifdef REBREW_ALLOW_NAKED
__declspec(naked) int __cdecl amt_FindEntity26(int param_1, char* param_2)
{
	__asm {
		_emit 0xb9
		_emit 0x29
		_emit 0x00
		_emit 0x00
		_emit 0x00
		_emit 0xb8
		_emit 0x80
		_emit 0xe9
		_emit 0x1d
		_emit 0x10
		_emit 0x80
		_emit 0x38
		_emit 0x26
		_emit 0x74
		_emit 0x0c
		_emit 0x83
		_emit 0xe8
		_emit 0x18
		_emit 0x49
		_emit 0x3d
		_emit 0xa8
		_emit 0xe5
		_emit 0x1d
		_emit 0x10
		_emit 0x75
		_emit 0xf0
		_emit 0xc3
		_emit 0x8d
		_emit 0x04
		_emit 0x49
		_emit 0x8b
		_emit 0x4c
		_emit 0x24
		_emit 0x04
		_emit 0x89
		_emit 0x0c
		_emit 0xc5
		_emit 0xa4
		_emit 0xe5
		_emit 0x1d
		_emit 0x10
		_emit 0xc3
	}
}
#else
int __cdecl amt_FindEntity26(int param_1, char* param_2)
{
    return 0;
}
#endif
