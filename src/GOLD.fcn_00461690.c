void __cdecl fcn_004614e0(int, int, int);

/* ADDRESS: GOLD 0x00461690 */
void __declspec(naked) __cdecl fcn_00461690(int a, int b, int c)
{
	(void) a;
	(void) b;
	(void) c;
	__asm {
		mov eax, dword ptr [esp+4]
		cmp byte ptr [eax+6Ch], 0ffh
		jb Lout
		test byte ptr [eax+6Eh], 1
		jnz Lout
		mov ecx, dword ptr [esp+8]
		cmp cl, 0ffh
		jz Lout
		mov edx, dword ptr [esp+0Ch]
		mov dword ptr [esp+8], ecx
		mov dword ptr [esp+0Ch], edx
		mov dword ptr [esp+4], eax
		jmp fcn_004614e0
	Lout:
		ret
	}
}
