/* ADDRESS: GOLD 0x00454500 */
int __declspec(naked) __cdecl fcn_00454500(int a)
{
	(void)a;
	__asm {
		push ebp
		mov ebp, esp
		push ecx
		push ebx
		push edi
		mov dword ptr [ebp-4], 40h
		mov edi, dword ptr [ebp+8]
		mov ebx, dword ptr [ebp-4]
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short Ltail
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	Ltail:
		add ecx, ebx
		rep stosb
		mov eax, dword ptr [ebp+8]
		mov ecx, 3F800000h
		pop edi
		pop ebx
		mov dword ptr [eax+3Ch], ecx
		mov dword ptr [eax+28h], ecx
		mov dword ptr [eax+14h], ecx
		mov dword ptr [eax], ecx
		mov esp, ebp
		pop ebp
		ret
	}
}
