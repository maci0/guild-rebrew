int __cdecl strnicmp(int, int, int);

/* ADDRESS: GOLD 0x0044c5d0 */
int __declspec(naked) __cdecl fcn_0044c5d0(int s)
{
	(void)s;
	__asm {
		push esi
		_emit 0x8b
		_emit 0x35
		_emit 0xfc
		_emit 0x2f
		_emit 0xfc
		_emit 0x00
		cmp esi, 0FC4A40h
		push edi
		jz Lmiss
		mov edi, dword ptr [esp+0Ch]
	Lgo:
		push 3Fh
		push esi
		push edi
		call strnicmp
		add esp, 0Ch
		test eax, eax
		jz Lfound
		mov esi, dword ptr [esi+1FCh]
		cmp esi, 0FC4A40h
		jnz Lgo
	Lmiss:
		pop edi
		xor eax, eax
		pop esi
		ret
	Lfound:
		mov eax, esi
		pop edi
		pop esi
		ret
	}
}
