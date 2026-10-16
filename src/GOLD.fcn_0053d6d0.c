int __cdecl fcn_005de7a2(int, int, int, int);

/* ADDRESS: GOLD 0x0053d6d0 */
void __declspec(naked) __cdecl fcn_0053d6d0(int a)
{
	(void)a;
	__asm {
		mov ecx, dword ptr [esp+4]
		xor eax, eax
		sub esp, 100h
		mov ax, word ptr [ecx+8]
		lea eax, [eax+eax*2]
		lea eax, [eax+eax*4]
		lea eax, [eax+eax*8]
		lea edx, [eax*4+770BB0h]
		xor eax, eax
		mov al, byte ptr [ecx]
		push edx
		push eax
		lea ecx, [esp+8]
		push 6266B8h
		push ecx
		call fcn_005de7a2
		add esp, 110h
		ret
	}
}
