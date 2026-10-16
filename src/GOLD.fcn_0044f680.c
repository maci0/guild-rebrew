int __cdecl fcn_004011d0(int, int);
int __cdecl m_alloc(int, int);

/* ADDRESS: GOLD 0x0044f680 */
void __declspec(naked) __cdecl fcn_0044f680(int a, int obj)
{
	(void)a;
	(void)obj;
	__asm {
		mov eax, dword ptr [esp+4]
		push esi
		mov esi, dword ptr [esp+0Ch]
		push edi
		lea edi, [esi+14h]
		push edi
		push eax
		call fcn_004011d0
		mov ecx, dword ptr [edi]
		xor eax, eax
		add esp, 8
		cmp ecx, eax
		jng Ldone
		cmp dword ptr [esi+20h], eax
		jnz Ldone
		push 5FC918h
		push 0E0000h
		mov dword ptr [esi+18h], eax
		mov dword ptr [esi+1Ch], eax
		call m_alloc
		add esp, 8
		mov dword ptr [esi+20h], eax
	Ldone:
		pop edi
		pop esi
		ret
	}
}
