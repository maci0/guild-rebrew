void __cdecl fcn_004fe140(int, int, int, int);

/* ADDRESS: GOLD 0x00552290 */
void __declspec(naked) __cdecl fcn_00552290(int obj)
{
	(void)obj;
	__asm {
		_emit 0x8b
		_emit 0x15
		_emit 0xe0
		_emit 0x0a
		_emit 0x77
		_emit 0x00
		push esi
		mov esi, dword ptr [esp+8]
		push 0
		push 0
		push 2
		lea eax, [esi+52h]
		mov ecx, eax
		push eax
		mov dword ptr [ecx], edx
		_emit 0x8b
		_emit 0x15
		_emit 0xe4
		_emit 0x0a
		_emit 0x77
		_emit 0x00
		mov dword ptr [ecx+4], edx
		_emit 0x8b
		_emit 0x15
		_emit 0xe8
		_emit 0x0a
		_emit 0x77
		_emit 0x00
		mov dword ptr [ecx+8], edx
		_emit 0x66
		_emit 0x8b
		_emit 0x15
		_emit 0xec
		_emit 0x0a
		_emit 0x77
		_emit 0x00
		_emit 0x66
		_emit 0x89
		_emit 0x51
		_emit 0x0c
		call fcn_004fe140
		add esp, 10h
		mov dword ptr [esi+70h], 0
		pop esi
		ret
	}
}
