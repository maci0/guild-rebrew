/* ADDRESS: GOLD 0x00423720 */
/* The null-head path returns the pre-zeroed ecx. A found node returns the node. */
int __declspec(naked) __cdecl fcn_00423720(int a)
{
	(void) a;
	__asm {
		_emit 0xa1
		_emit 0xa4
		_emit 0x23
		_emit 0x63
		_emit 0x00
		xor ecx, ecx
		test eax, eax
		jz Lzero
		mov ecx, dword ptr [esp+4]
	again:
		cmp dword ptr [eax+8], ecx
		jz Ldone
		mov eax, dword ptr [eax+4]
		test eax, eax
		jnz again
		ret
	Lzero:
		mov eax, ecx
	Ldone:
		ret
	}
}
