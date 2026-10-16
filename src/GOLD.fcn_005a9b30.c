int __cdecl gm_RandomMod(int);
void __cdecl fcn_0051af00();
void __cdecl fcn_00545d40();

/* ADDRESS: GOLD 0x005a9b30 */
void __declspec(naked) __cdecl fcn_005a9b30(int a)
{
	(void)a;
	__asm {
		push 3
		call gm_RandomMod
		and eax, 0FFFFh
		add eax, 40A9h
		push eax
		push 40ACh
		push 6F26C8h
		call fcn_0051af00
		mov eax, dword ptr [esp+14h]
		push 62C380h
		push 5FBh
		push 1
		mov ecx, dword ptr [eax+4]
		push 6F26C8h
		push 0FFFFFFFFh
		push ecx
		call fcn_00545d40
		add esp, 28h
		ret
	}
}
