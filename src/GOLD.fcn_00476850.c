void __cdecl fcn_004481e0(int);
void __cdecl m_FreeTracked(int);

/* ADDRESS: GOLD 0x00476850 */
void __declspec(naked) __cdecl fcn_00476850(int p)
{
	(void)p;
	__asm {
		push esi
		mov esi, dword ptr [esp+8]
		xor eax, eax
	Lgo:
		cmp dword ptr [eax*4+0F8F0A0h], esi
		jz Lfound
		inc eax
		cmp eax, 20h
		jl Lgo
		pop esi
		ret
	Lfound:
		mov dword ptr [eax*4+0F8F0A0h], 0
		mov eax, dword ptr [esi+60h]
		push eax
		call fcn_004481e0
		push esi
		call m_FreeTracked
		add esp, 8
		pop esi
		ret
	}
}
