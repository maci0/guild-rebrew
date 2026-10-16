/* ADDRESS: GOLD 0x00423740 */
int __declspec(naked) __cdecl fcn_00423740(int a)
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
		jz empty
		mov ecx, dword ptr [esp+4]
	walk:
		cmp dword ptr [eax+114h], ecx
		jz found
		mov eax, dword ptr [eax+4]
		test eax, eax
		jnz walk
		ret
	empty:
		mov eax, ecx
	found:
		ret
	}
}
