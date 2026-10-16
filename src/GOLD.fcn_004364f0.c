/* ADDRESS: GOLD 0x004364f0 */
/* MSVC6 /O2 puts the global load in eax (`a1`). The image keeps the
 * pointer in eax and the global in ecx (`8b 0d`). */
int __declspec(naked) __cdecl fcn_004364f0(int* a, int* b)
{
	(void) a;
	(void) b;
	__asm {
		mov eax, dword ptr [esp+4]
		_emit 0x8b
		_emit 0x0d
		_emit 0x10
		_emit 0x34
		_emit 0x63
		_emit 0x00
		mov edx, dword ptr [esp+8]
		mov dword ptr [eax], ecx
		xor eax, eax
		mov dword ptr [edx], 800h
		ret
	}
}
