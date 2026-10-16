/* ADDRESS: GOLD 0x00475fe0 */
int __declspec(naked) __cdecl fcn_00475fe0(int a, int b)
{
	(void)a;
	(void)b;
	__asm {
		mov eax, dword ptr [esp+4]
		push esi
		lea ecx, [eax+eax*8]
		lea ecx, [eax+ecx*2]
		lea edx, [ecx+ecx*8]
		mov ecx, dword ptr [esp+0Ch]
		mov esi, dword ptr [edx*4+0FB11A4h]
		cmp ecx, esi
		pop esi
		jg Lbad
		test ecx, ecx
		jl Lbad
		lea edx, [eax+eax*8]
		lea eax, [eax+edx*2]
		lea ecx, [ecx+eax*8]
		add eax, ecx
		mov eax, dword ptr [eax*4+0FB1024h]
		ret
	Lbad:
		or eax, 0FFFFFFFFh
		ret
	}
}
