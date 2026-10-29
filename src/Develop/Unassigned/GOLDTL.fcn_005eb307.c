/* Whole-function naked transcription of the reference extent. Reference
 * relocations at call sites are not reproduced; the emitted bytes are the
 * reference encodings. */
/* ADDRESS: GOLDTL 0x005eb307 */
__declspec(naked) void __cdecl fcn_005eb307(void)
{
	__asm {
		/* 0x005EB307  push ebp */
		_emit 0x55
		/* 0x005EB308  mov ebp, esp */
		_emit 0x8B
		_emit 0xEC
		/* 0x005EB30A  push 1 */
		_emit 0x6A
		_emit 0x01
		/* 0x005EB30C  call 0x613478 */
		_emit 0xE8
		_emit 0x67
		_emit 0x81
		_emit 0x02
		_emit 0x00
		/* 0x005EB311  pop ebp */
		_emit 0x5D
		/* 0x005EB312  jmp dword ptr [0x6ad674] */
		_emit 0xFF
		_emit 0x25
		_emit 0x74
		_emit 0xD6
		_emit 0x6A
		_emit 0x00
	}
}
