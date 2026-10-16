int __cdecl fcn_0041f7f0(int);
int __cdecl fcn_0041f940(int);

/* ADDRESS: GOLD 0x00422d90 */
void __declspec(naked) __cdecl fcn_00422d90(void)
{
	__asm {
		_emit 0xa1
		_emit 0xa4
		_emit 0x23
		_emit 0x63
		_emit 0x00
		test eax, eax
		jz Lout
	Lgo:
		push eax
		call fcn_0041f7f0
		_emit 0xa1
		_emit 0xa4
		_emit 0x23
		_emit 0x63
		_emit 0x00
		push eax
		call fcn_0041f940
		_emit 0xa1
		_emit 0xa4
		_emit 0x23
		_emit 0x63
		_emit 0x00
		add esp, 8
		test eax, eax
		jnz Lgo
	Lout:
	}
}
