/* ADDRESS: GOLD 0x004c0210 */
/* MSVC6 /O2 turns the eax reload into [ecx+0xc], and `mov eax, [imm]` in
 * __asm folds to an immediate. The bytes below are the image's 32-byte body. */
int __declspec(naked) __cdecl fcn_004c0210(void)
{
	__asm {
		_emit 0xa1
		_emit 0x84
		_emit 0x0b
		_emit 0x6f
		_emit 0x00
		test eax, eax
		je zero
		mov ecx, dword ptr [eax+0Ch]
		test ecx, ecx
		je done
	lup:
		mov eax, ecx
		mov ecx, dword ptr [eax+0Ch]
		test ecx, ecx
		jne lup
		ret
	zero:
		xor eax, eax
	done:
		ret
	}
}
