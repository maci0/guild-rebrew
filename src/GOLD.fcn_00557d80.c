void __cdecl fcn_004fe140(int, int, int, int);

/* ADDRESS: GOLD 0x00557d80 */
void __declspec(naked) __cdecl fcn_00557d80(int a)
{
	(void)a;
	__asm {
		mov ecx, dword ptr [esp+4]
		push esi
		push 0
		push 0
		lea eax, [ecx+52h]
		add ecx, 44h
		mov edx, eax
		push 2
		mov esi, dword ptr [ecx]
		push eax
		mov dword ptr [edx], esi
		mov esi, dword ptr [ecx+4]
		mov dword ptr [edx+4], esi
		mov esi, dword ptr [ecx+8]
		mov dword ptr [edx+8], esi
		mov cx, word ptr [ecx+0Ch]
		mov word ptr [edx+0Ch], cx
		call fcn_004fe140
		add esp, 10h
		pop esi
		ret
	}
}
