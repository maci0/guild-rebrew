/* Whole-function naked transcription of the reference extent. Reference
 * relocations at call sites are not reproduced; the emitted bytes are the
 * reference encodings. */
/* ADDRESS: GOLDTL 0x005f0eb0 */
__declspec(naked) void __cdecl fcn_005f0eb0(void)
{
	__asm {
		/* 0x005F0EB0  mov edx, dword ptr [esp + 8] */
		_emit 0x8B
		_emit 0x54
		_emit 0x24
		_emit 0x08
		/* 0x005F0EB4  mov eax, dword ptr [ecx + 0x28] */
		_emit 0x8B
		_emit 0x41
		_emit 0x28
		/* 0x005F0EB7  mov ecx, dword ptr [eax] */
		_emit 0x8B
		_emit 0x08
		/* 0x005F0EB9  or edx, 0x800 */
		_emit 0x81
		_emit 0xCA
		_emit 0x00
		_emit 0x08
		_emit 0x00
		_emit 0x00
		/* 0x005F0EBF  push edx */
		_emit 0x52
		/* 0x005F0EC0  push dword ptr [esp + 8] */
		_emit 0xFF
		_emit 0x74
		_emit 0x24
		_emit 0x08
		/* 0x005F0EC4  push 0 */
		_emit 0x6A
		_emit 0x00
		/* 0x005F0EC6  push 0 */
		_emit 0x6A
		_emit 0x00
		/* 0x005F0EC8  push eax */
		_emit 0x50
		/* 0x005F0EC9  call dword ptr [ecx + 0x2c] */
		_emit 0xFF
		_emit 0x51
		_emit 0x2C
		/* 0x005F0ECC  ret 8 */
		_emit 0xC2
		_emit 0x08
		_emit 0x00
	}
}
