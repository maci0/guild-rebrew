void __cdecl fcn_004fe1e0(int, int, int, int);

/* ADDRESS: GOLD 0x004b3ca0 */
void __declspec(naked) __cdecl fcn_004b3ca0(int a, int b)
{
	(void)a;
	(void)b;
	__asm {
		_emit 0x80
		_emit 0x3d
		_emit 0x88
		_emit 0x45
		_emit 0x62
		_emit 0x00
		_emit 0x05
		_emit 0x75
		_emit 0x3d
		mov eax, dword ptr [esp+8]
		mov ecx, dword ptr [esp+4]
		push 0
		push 0
		push 0
		push 0F82328h
		_emit 0xa3
		_emit 0x20
		_emit 0x23
		_emit 0xf8
		_emit 0x00
		_emit 0x89
		_emit 0x0d
		_emit 0x24
		_emit 0x23
		_emit 0xf8
		_emit 0x00
		_emit 0xc7
		_emit 0x05
		_emit 0x28
		_emit 0x23
		_emit 0xf8
		_emit 0x00
		_emit 0x00
		_emit 0x00
		_emit 0x00
		_emit 0x00
		call fcn_004fe1e0
		add esp, 10h
		_emit 0xc6
		_emit 0x05
		_emit 0x40
		_emit 0x23
		_emit 0xf8
		_emit 0x00
		_emit 0x00
	}
}
