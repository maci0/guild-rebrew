/* Whole-function naked transcription of the reference extent. Reference
 * relocations at call sites are not reproduced; the emitted bytes are the
 * reference encodings. */
/* ADDRESS: GOLDTL 0x005edcfa */
__declspec(naked) void __cdecl fcn_005edcfa(void)
{
	__asm {
		/* 0x005EDCFA  push ebp */
		_emit 0x55
		/* 0x005EDCFB  mov ebp, esp */
		_emit 0x8B
		_emit 0xEC
		/* 0x005EDCFD  push 1 */
		_emit 0x6A
		_emit 0x01
		/* 0x005EDCFF  call 0x613478 */
		_emit 0xE8
		_emit 0x74
		_emit 0x57
		_emit 0x02
		_emit 0x00
		/* 0x005EDD04  pop ebp */
		_emit 0x5D
		/* 0x005EDD05  jmp dword ptr [0x6ad6ec] */
		_emit 0xFF
		_emit 0x25
		_emit 0xEC
		_emit 0xD6
		_emit 0x6A
		_emit 0x00
		/* 0x005EDD0B  jmp dword ptr [0x6ad6ec] */
		_emit 0xFF
		_emit 0x25
		_emit 0xEC
		_emit 0xD6
		_emit 0x6A
		_emit 0x00
	}
}
