void __cdecl fcn_00454560(int);
int __cdecl fcn_00438e60(int, int, int, int);
int __cdecl fcn_00454c00(int, int, int, int);

/* ADDRESS: GOLD 0x00511870 */
void __declspec(naked) __cdecl fcn_00511870(void)
{
	__asm {
		_emit 0xa1
		_emit 0x28
		_emit 0x1c
		_emit 0x6f
		_emit 0x00
		test eax, eax
		jz Lskip
		push eax
		call fcn_00454560
		add esp, 4
		_emit 0xc7
		_emit 0x05
		_emit 0x28
		_emit 0x1c
		_emit 0x6f
		_emit 0x00
		_emit 0x00
		_emit 0x00
		_emit 0x00
		_emit 0x00
	Lskip:
		_emit 0xa1
		_emit 0xb0
		_emit 0xb5
		_emit 0x5f
		_emit 0x00
		push 511840h
		push 40h
		push 0
		push eax
		call fcn_00438e60
		push 7
		push 8
		push 40h
		push 0
		call fcn_00454c00
		add esp, 20h
		_emit 0xa3
		_emit 0x28
		_emit 0x1c
		_emit 0x6f
		_emit 0x00
		ret
	}
}
