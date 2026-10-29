/* Whole-function naked transcription of the reference extent. Reference
 * relocations at call sites are not reproduced; the emitted bytes are the
 * reference encodings. */
/* ADDRESS: GOLDTL 0x005ef2e0 */
__declspec(naked) void __cdecl fcn_005ef2e0(void)
{
	__asm {
		/* 0x005EF2E0  push ebp */
		_emit 0x55
		/* 0x005EF2E1  mov ebp, esp */
		_emit 0x8B
		_emit 0xEC
		/* 0x005EF2E3  sub esp, 0x3fc */
		_emit 0x81
		_emit 0xEC
		_emit 0xFC
		_emit 0x03
		_emit 0x00
		_emit 0x00
		/* 0x005EF2E9  push ebx */
		_emit 0x53
		/* 0x005EF2EA  push esi */
		_emit 0x56
		/* 0x005EF2EB  push edi */
		_emit 0x57
		/* 0x005EF2EC  lea ecx, [ebp - 0x14] */
		_emit 0x8D
		_emit 0x4D
		_emit 0xEC
		/* 0x005EF2EF  call 0x6165dd */
		_emit 0xE8
		_emit 0xE9
		_emit 0x72
		_emit 0x02
		_emit 0x00
		/* 0x005EF2F4  lea ecx, [ebp - 0x3fc] */
		_emit 0x8D
		_emit 0x8D
		_emit 0x04
		_emit 0xFC
		_emit 0xFF
		_emit 0xFF
		/* 4 trailing extent bytes, not decoded as instructions */
		_emit 0xE8
		_emit 0x16
		_emit 0x75
		_emit 0x02
	}
}
