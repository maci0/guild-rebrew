/* ADDRESS: GOLD 0x004ce130 */
int __declspec(naked) __cdecl fcn_004ce130(int key)
{
	(void)key;
	__asm {
		mov edx, dword ptr [esp+4]
		xor ecx, ecx
		mov eax, 930604h
	Lgo:
		_emit 0x66
		_emit 0x81
		_emit 0x78
		_emit 0xfc
		_emit 0xff
		_emit 0xff
		jz Lnext
		cmp dword ptr [eax], edx
		jz Lfound
	Lnext:
		add eax, 21Ch
		inc ecx
		cmp eax, 934984h
		jl Lgo
		xor eax, eax
		ret
	Lfound:
		lea eax, [ecx+ecx*2]
		lea eax, [eax+eax*4]
		lea eax, [eax+eax*8]
		lea eax, [eax*4+930600h]
		ret
	}
}
