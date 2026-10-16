int __cdecl fcn_00438d40(int, int, int, int, int);

/* ADDRESS: GOLD 0x004d0ca0 */
void __declspec(naked) __cdecl fcn_004d0ca0(void)
{
	__asm {
		_emit 0xa1
		_emit 0xb0
		_emit 0xb5
		_emit 0x5f
		_emit 0x00
		push 0
		push 4d0a80h
		push 100h
		push 0
		push eax
		_emit 0xc7
		_emit 0x05
		_emit 0x58
		_emit 0x0d
		_emit 0x6f
		_emit 0x00
		_emit 0x00
		_emit 0x00
		_emit 0x00
		_emit 0x00
		call fcn_00438d40
		add esp, 14h
		ret
	}
}
