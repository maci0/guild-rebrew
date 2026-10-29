/* Whole-function naked transcription of the reference extent. Reference
 * relocations at call sites are not reproduced; the emitted bytes are the
 * reference encodings. */
/* ADDRESS: GOLDTL 0x005f6d83 */
__declspec(naked) void __cdecl fcn_005f6d83(void)
{
	__asm {
		/* 0x005F6D83  push ebp */
		_emit 0x55
		/* 0x005F6D84  mov ebp, esp */
		_emit 0x8B
		_emit 0xEC
		/* 0x005F6D86  push esi */
		_emit 0x56
		/* 0x005F6D87  mov esi, dword ptr [ebp + 8] */
		_emit 0x8B
		_emit 0x75
		_emit 0x08
		/* 0x005F6D8A  xor edx, edx */
		_emit 0x33
		_emit 0xD2
		/* 0x005F6D8C  mov eax, esi */
		_emit 0x8B
		_emit 0xC6
		/* 0x005F6D8E  div dword ptr [ebp + 0x18] */
		_emit 0xF7
		_emit 0x75
		_emit 0x18
		/* 0x005F6D91  mov eax, dword ptr [ebp + 0x14] */
		_emit 0x8B
		_emit 0x45
		_emit 0x14
		/* 0x005F6D94  lea ecx, [eax + edx*4] */
		_emit 0x8D
		_emit 0x0C
		_emit 0x90
		/* 0x005F6D97  mov eax, dword ptr [ecx] */
		_emit 0x8B
		_emit 0x01
		/* 0x005F6D99  xor edx, edx */
		_emit 0x33
		_emit 0xD2
		/* 0x005F6D9B  test eax, eax */
		_emit 0x85
		_emit 0xC0
		/* 0x005F6D9D  je 0x5f6dce */
		_emit 0x74
		_emit 0x2F
		/* 0x005F6D9F  push edi */
		_emit 0x57
		/* 0x005F6DA0  mov edi, dword ptr [eax + 0xc] */
		_emit 0x8B
		_emit 0x78
		_emit 0x0C
		/* 0x005F6DA3  cmp edi, dword ptr [ebp + 0x10] */
		_emit 0x3B
		_emit 0x7D
		_emit 0x10
		/* 0x005F6DA6  jne 0x5f6db4 */
		_emit 0x75
		_emit 0x0C
		/* 0x005F6DA8  mov edi, dword ptr [eax + 4] */
		_emit 0x8B
		_emit 0x78
		_emit 0x04
		/* 0x005F6DAB  cmp edi, dword ptr [ebp + 0xc] */
		_emit 0x3B
		_emit 0x7D
		_emit 0x0C
		/* 0x005F6DAE  jne 0x5f6db4 */
		_emit 0x75
		_emit 0x04
		/* 0x005F6DB0  cmp dword ptr [eax], esi */
		_emit 0x39
		_emit 0x30
		/* 0x005F6DB2  je 0x5f6dbf */
		_emit 0x74
		_emit 0x0B
		/* 0x005F6DB4  mov edx, eax */
		_emit 0x8B
		_emit 0xD0
		/* 0x005F6DB6  mov eax, dword ptr [eax + 0x10] */
		_emit 0x8B
		_emit 0x40
		_emit 0x10
		/* 0x005F6DB9  test eax, eax */
		_emit 0x85
		_emit 0xC0
		/* 0x005F6DBB  jne 0x5f6da0 */
		_emit 0x75
		_emit 0xE3
		/* 0x005F6DBD  jmp 0x5f6dcd */
		_emit 0xEB
		_emit 0x0E
		/* 0x005F6DBF  test edx, edx */
		_emit 0x85
		_emit 0xD2
		/* 0x005F6DC1  mov eax, dword ptr [eax + 0x10] */
		_emit 0x8B
		_emit 0x40
		_emit 0x10
		/* 0x005F6DC4  je 0x5f6dcb */
		_emit 0x74
		_emit 0x05
		/* 0x005F6DC6  mov dword ptr [edx + 0x10], eax */
		_emit 0x89
		_emit 0x42
		_emit 0x10
		/* 0x005F6DC9  jmp 0x5f6dcd */
		_emit 0xEB
		_emit 0x02
		/* 0x005F6DCB  mov dword ptr [ecx], eax */
		_emit 0x89
		_emit 0x01
		/* 0x005F6DCD  pop edi */
		_emit 0x5F
		/* 0x005F6DCE  pop esi */
		_emit 0x5E
		/* 0x005F6DCF  pop ebp */
		_emit 0x5D
		/* 0x005F6DD0  ret  */
		_emit 0xC3
	}
}
