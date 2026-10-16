/* ADDRESS: GOLD 0x00475f30 */
/* MSVC6 /O2 folds `mov edx, dword ptr [imm]` to `ba`. The image is `8b 15`. */
void __declspec(naked) __cdecl fcn_00475f30(int a, int b)
{
	(void) a;
	(void) b;
	__asm {
		mov ecx, dword ptr [esp+4]
		_emit 0x8b
		_emit 0x15
		_emit 0x80
		_emit 0xf0
		_emit 0xf8
		_emit 0x00
		mov eax, ecx
		shl eax, 5
		sub eax, ecx
		lea eax, [eax+eax*2]
		lea ecx, [ecx+eax*2]
		mov eax, dword ptr [edx+ecx*4+78h]
		lea ecx, [eax+eax*4]
		lea edx, [eax+ecx*2]
		mov eax, dword ptr [esp+8]
		shl edx, 5
		mov dword ptr [edx+0fa6038h], eax
		ret
	}
}
