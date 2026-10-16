int __cdecl m_alloc(int, int);

/* ADDRESS: GOLD 0x0045f600 */
void __declspec(naked) __cdecl fcn_0045f600(int a)
{
	(void)a;
	__asm {
		mov eax, dword ptr [esp+4]
		xor ecx, ecx
		cmp eax, ecx
		_emit 0xa3
		_emit 0x80
		_emit 0x90
		_emit 0xfb
		_emit 0x00
		_emit 0x89
		_emit 0x0d
		_emit 0xb4
		_emit 0x91
		_emit 0xfb
		_emit 0x00
		_emit 0x89
		_emit 0x0d
		_emit 0x7c
		_emit 0x90
		_emit 0xfb
		_emit 0x00
		jna Lzero
		lea eax, [eax+eax*4]
		push 5FD0B4h
		shl eax, 2
		push eax
		call m_alloc
		add esp, 8
		_emit 0xa3
		_emit 0x08
		_emit 0x3f
		_emit 0x63
		_emit 0x00
		ret
	Lzero:
		_emit 0x89
		_emit 0x0d
		_emit 0x08
		_emit 0x3f
		_emit 0x63
		_emit 0x00
		ret
	}
}
