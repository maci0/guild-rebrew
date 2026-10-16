int __cdecl fcn_004ac1e0(int);

/* ADDRESS: GOLD 0x004ac1a0 */
int __declspec(naked) __cdecl fcn_004ac1a0(int a, int b)
{
	(void)a;
	(void)b;
	__asm {
		push esi
		mov esi, dword ptr [esp+0Ch]
		cmp si, 9
		jc Lsmall
		mov esi, 9
	Lsmall:
		mov eax, dword ptr [esp+8]
		push eax
		call fcn_004ac1e0
		add esp, 4
		test eax, eax
		jz Lfail
		mov ecx, dword ptr [eax+8]
		test ecx, ecx
		jnz Lalt
		lea eax, [esi+1E2Bh]
		pop esi
		ret
	Lalt:
		lea eax, [esi+1E35h]
		pop esi
		ret
	Lfail:
		mov ax, word ptr [esp+0Ch]
		pop esi
		ret
	}
}
