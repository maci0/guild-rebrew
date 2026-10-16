int __cdecl strstr(int, int);

/* ADDRESS: GOLD 0x005127b0 */
void __declspec(naked) __cdecl fcn_005127b0(int p)
{
	(void)p;
	__asm {
		push esi
		mov esi, dword ptr [esp+8]
		push 623248h
		push esi
		call strstr
		add esp, 8
		test eax, eax
		jz Lno
		mov al, byte ptr [esi+211h]
		mov dword ptr [esi+224h], 1
		and al, 0FEh
		mov byte ptr [esi+211h], al
		pop esi
		ret
	Lno:
		mov dword ptr [esi+224h], 0
		pop esi
		ret
	}
}
