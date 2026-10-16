int __cdecl fcn_00430bd0(int, int, int, int);
int __cdecl fcn_0044d770(int);
int __cdecl fcn_004011d0(int, int);
void __cdecl fcn_0044eee0(int, int, int, int);

/* ADDRESS: GOLD 0x0044f860 */
void __declspec(naked) __cdecl fcn_0044f860(int a)
{
	(void)a;
	__asm {
		push ecx
		push esi
		mov esi, dword ptr [esp+0Ch]
		push esi
		push 1
		lea eax, [esp+14h]
		push 4
		push eax
		call fcn_00430bd0
		push esi
		call fcn_0044d770
		add esp, 14h
		cmp eax, 2Eh
		jnz Ldone
		lea ecx, [esp+4]
		push ecx
		push esi
		call fcn_004011d0
		mov edx, dword ptr [esp+18h]
		push edx
		push 7
		push 5FC890h
		push esi
		call fcn_0044eee0
		add esp, 18h
	Ldone:
		pop esi
		pop ecx
		ret
	}
}
