void __cdecl fcn_004241a0(int);

/* ADDRESS: GOLD 0x004c24c0 */
/* MSVC6 /O2 folds `mov eax, dword ptr [imm]` to `b8`. The image is `a1`. */
int __declspec(naked) __cdecl fcn_004c24c0(int a)
{
	(void) a;
	__asm {
		_emit 0xa1
		_emit 0x6c
		_emit 0x0b
		_emit 0x6f
		_emit 0x00
		test eax, eax
		jz done
		mov ecx, dword ptr [esp+4]
		mov dword ptr [esp+4], ecx
		jmp fcn_004241a0
	done:
		ret
	}
}
