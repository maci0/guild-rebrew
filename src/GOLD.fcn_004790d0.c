void __cdecl fcn_0041e740(int);

/* ADDRESS: GOLD 0x004790d0 */
int __declspec(naked) __cdecl fcn_004790d0(int p)
{
	(void)p;
	__asm {
		push esi
		mov esi, dword ptr [esp+8]
		mov eax, dword ptr [esi+34h]
		test eax, eax
		jnz Lhave
		xor eax, eax
		pop esi
		ret
	Lhave:
		mov eax, dword ptr [esi+20h]
		test eax, eax
		jz Lskip
		push eax
		call fcn_0041e740
		add esp, 4
		mov dword ptr [esi+1Ch], 0
	Lskip:
		mov dword ptr [esi+34h], 0
		mov eax, 1
		pop esi
		ret
	}
}
