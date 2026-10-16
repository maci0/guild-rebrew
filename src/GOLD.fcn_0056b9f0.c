/* ADDRESS: GOLD 0x0056b9f0 */
char __declspec(naked) __cdecl fcn_0056b9f0(int b, char *a)
{
	(void)b; (void)a;
	__asm {
		mov eax, dword ptr [esp+8]
		mov edx, dword ptr [esp+4]
		mov ecx, dword ptr [eax+104h]
		mov dword ptr [eax+ecx*4+4], edx
		mov ecx, dword ptr [eax+104h]
		inc ecx
		mov dword ptr [eax+104h], ecx
		mov eax, ecx
		xor ecx, ecx
		cmp eax, 40h
		setl cl
		mov al, cl
		ret
	}
}
