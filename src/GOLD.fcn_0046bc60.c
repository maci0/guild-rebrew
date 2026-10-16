char* __cdecl strncpy(char* dest, const char* src, unsigned int n);

/* ADDRESS: GOLD 0x0046bc60 */
/* MSVC6 /O2 folds `mov ecx, dword ptr [imm]` to `b9`. The image is `8b 0d`. */
void __declspec(naked) __cdecl fcn_0046bc60(int a, char* b)
{
	(void) a;
	(void) b;
	__asm {
		mov eax, dword ptr [esp+8]
		mov ecx, dword ptr [esp+4]
		push 3Fh
		push eax
		mov eax, ecx
		shl eax, 5
		sub eax, ecx
		lea edx, [eax+eax*2]
		lea eax, [ecx+edx*2]
		_emit 0x8b
		_emit 0x0d
		_emit 0x80
		_emit 0xf0
		_emit 0xf8
		_emit 0x00
		lea edx, [ecx+eax*4+9Ch]
		push edx
		call strncpy
		add esp, 0Ch
		ret
	}
}
