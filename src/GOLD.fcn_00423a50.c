int __cdecl fcn_0042a0e0(int, int);

/* ADDRESS: GOLD 0x00423a50 */
void __declspec(naked) __cdecl fcn_00423a50(int a)
{
	(void)a;
	__asm {
		_emit 0xa1
		_emit 0xc8
		_emit 0x25
		_emit 0x63
		_emit 0x00
		test eax, eax
		jz done
		push esi
		push 14613E0h
		_emit 0xff
		_emit 0x15
		_emit 0x64
		_emit 0xb0
		_emit 0x5e
		_emit 0x00
		mov esi, dword ptr [esp+8]
		_emit 0xa1
		_emit 0xc8
		_emit 0x25
		_emit 0x63
		_emit 0x00
		push esi
		push eax
		call fcn_0042a0e0
		add esp, 8
		_emit 0x89
		_emit 0x35
		_emit 0xbc
		_emit 0x74
		_emit 0x5f
		_emit 0x00
		push 14613E0h
		_emit 0xff
		_emit 0x15
		_emit 0x60
		_emit 0xb0
		_emit 0x5e
		_emit 0x00
		pop esi
	done:
		ret
	}
}
