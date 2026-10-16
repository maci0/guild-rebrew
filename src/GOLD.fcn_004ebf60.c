void __cdecl m_FreeTracked(int);

/* ADDRESS: GOLD 0x004ebf60 */
void __declspec(naked) __cdecl fcn_004ebf60(void)
{
	__asm {
		_emit 0xa1
		_emit 0x2c
		_emit 0x0e
		_emit 0x6f
		_emit 0x00
		push esi
		xor esi, esi
		cmp eax, esi
		jz Lsecond
		push eax
		call m_FreeTracked
		add esp, 4
		_emit 0x89
		_emit 0x35
		_emit 0x2c
		_emit 0x0e
		_emit 0x6f
		_emit 0x00
	Lsecond:
		_emit 0xa1
		_emit 0x34
		_emit 0x0e
		_emit 0x6f
		_emit 0x00
		cmp eax, esi
		jz Lstores
		push eax
		call m_FreeTracked
		add esp, 4
		_emit 0x89
		_emit 0x35
		_emit 0x34
		_emit 0x0e
		_emit 0x6f
		_emit 0x00
	Lstores:
		_emit 0x89
		_emit 0x35
		_emit 0x30
		_emit 0x0e
		_emit 0x6f
		_emit 0x00
		_emit 0x89
		_emit 0x35
		_emit 0x28
		_emit 0x0e
		_emit 0x6f
		_emit 0x00
		pop esi
		ret
	}
}
