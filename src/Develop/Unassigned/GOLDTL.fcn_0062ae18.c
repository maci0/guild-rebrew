/* Whole-function naked transcription of the reference extent. Reference
 * relocations at call sites are not reproduced; the emitted bytes are the
 * reference encodings. */
/* ADDRESS: GOLDTL 0x0062ae18 */
__declspec(naked) void __fastcall fcn_0062ae18(int a0)
{
	__asm {
		/* 0x0062AE18  push esi */
		_emit 0x56
		/* 0x0062AE19  mov esi, ecx */
		_emit 0x8B
		_emit 0xF1
		/* 0x0062AE1B  mov eax, dword ptr [esi + 4] */
		_emit 0x8B
		_emit 0x46
		_emit 0x04
		/* 0x0062AE1E  push edi */
		_emit 0x57
		/* 0x0062AE1F  xor edi, edi */
		_emit 0x33
		_emit 0xFF
		/* 0x0062AE21  cmp eax, edi */
		_emit 0x3B
		_emit 0xC7
		/* 0x0062AE23  je 0x62ae50 */
		_emit 0x74
		_emit 0x2B
		/* 0x0062AE25  mov ecx, dword ptr [esi + 0x64] */
		_emit 0x8B
		_emit 0x4E
		_emit 0x64
		/* 0x0062AE28  cmp ecx, edi */
		_emit 0x3B
		_emit 0xCF
		/* 0x0062AE2A  je 0x62ae39 */
		_emit 0x74
		_emit 0x0D
		/* 0x0062AE2C  mov edx, dword ptr [eax] */
		_emit 0x8B
		_emit 0x10
		/* 0x0062AE2E  push ecx */
		_emit 0x51
		/* 0x0062AE2F  push eax */
		_emit 0x50
		/* 0x0062AE30  call dword ptr [edx + 0xe0] */
		_emit 0xFF
		_emit 0x92
		_emit 0xE0
		_emit 0x00
		_emit 0x00
		_emit 0x00
		/* 0x0062AE36  mov dword ptr [esi + 0x64], edi */
		_emit 0x89
		_emit 0x7E
		_emit 0x64
		/* 0x0062AE39  mov ecx, dword ptr [esi + 0x68] */
		_emit 0x8B
		_emit 0x4E
		_emit 0x68
		/* 0x0062AE3C  cmp ecx, edi */
		_emit 0x3B
		_emit 0xCF
		/* 0x0062AE3E  je 0x62ae50 */
		_emit 0x74
		_emit 0x10
		/* 0x0062AE40  mov eax, dword ptr [esi + 4] */
		_emit 0x8B
		_emit 0x46
		_emit 0x04
		/* 0x0062AE43  mov edx, dword ptr [eax] */
		_emit 0x8B
		_emit 0x10
		/* 0x0062AE45  push ecx */
		_emit 0x51
		/* 0x0062AE46  push eax */
		_emit 0x50
		/* 0x0062AE47  call dword ptr [edx + 0xe0] */
		_emit 0xFF
		_emit 0x92
		_emit 0xE0
		_emit 0x00
		_emit 0x00
		_emit 0x00
		/* 0x0062AE4D  mov dword ptr [esi + 0x68], edi */
		_emit 0x89
		_emit 0x7E
		_emit 0x68
		/* 0x0062AE50  mov eax, dword ptr [esi + 0xc] */
		_emit 0x8B
		_emit 0x46
		_emit 0x0C
		/* 0x0062AE53  cmp eax, edi */
		_emit 0x3B
		_emit 0xC7
		/* 0x0062AE55  je 0x62ae5d */
		_emit 0x74
		_emit 0x06
		/* 0x0062AE57  mov ecx, dword ptr [eax] */
		_emit 0x8B
		_emit 0x08
		/* 0x0062AE59  push eax */
		_emit 0x50
		/* 0x0062AE5A  call dword ptr [ecx + 0x20] */
		_emit 0xFF
		_emit 0x51
		_emit 0x20
		/* 0x0062AE5D  cmp dword ptr [esi + 0x50], edi */
		_emit 0x39
		_emit 0x7E
		_emit 0x50
		/* 0x0062AE60  je 0x62ae8e */
		_emit 0x74
		_emit 0x2C
		/* 0x0062AE62  push ebx */
		_emit 0x53
		/* 0x0062AE63  push 8 */
		_emit 0x6A
		_emit 0x08
		/* 0x0062AE65  add esi, 0x10 */
		_emit 0x83
		_emit 0xC6
		_emit 0x10
		/* 0x0062AE68  pop ebx */
		_emit 0x5B
		/* 0x0062AE69  mov eax, dword ptr [esi + 0x20] */
		_emit 0x8B
		_emit 0x46
		_emit 0x20
		/* 0x0062AE6C  cmp eax, edi */
		_emit 0x3B
		_emit 0xC7
		/* 0x0062AE6E  je 0x62ae79 */
		_emit 0x74
		_emit 0x09
		/* 0x0062AE70  mov ecx, dword ptr [eax] */
		_emit 0x8B
		_emit 0x08
		/* 0x0062AE72  push eax */
		_emit 0x50
		/* 0x0062AE73  call dword ptr [ecx + 8] */
		_emit 0xFF
		_emit 0x51
		_emit 0x08
		/* 0x0062AE76  mov dword ptr [esi + 0x20], edi */
		_emit 0x89
		_emit 0x7E
		_emit 0x20
		/* 0x0062AE79  mov eax, dword ptr [esi] */
		_emit 0x8B
		_emit 0x06
		/* 0x0062AE7B  cmp eax, edi */
		_emit 0x3B
		_emit 0xC7
		/* 0x0062AE7D  je 0x62ae87 */
		_emit 0x74
		_emit 0x08
		/* 0x0062AE7F  mov ecx, dword ptr [eax] */
		_emit 0x8B
		_emit 0x08
		/* 0x0062AE81  push eax */
		_emit 0x50
		/* 0x0062AE82  call dword ptr [ecx + 8] */
		_emit 0xFF
		_emit 0x51
		_emit 0x08
		/* 0x0062AE85  mov dword ptr [esi], edi */
		_emit 0x89
		_emit 0x3E
		/* 0x0062AE87  add esi, 4 */
		_emit 0x83
		_emit 0xC6
		_emit 0x04
		/* 0x0062AE8A  dec ebx */
		_emit 0x4B
		/* 0x0062AE8B  jne 0x62ae69 */
		_emit 0x75
		_emit 0xDC
		/* 0x0062AE8D  pop ebx */
		_emit 0x5B
		/* 0x0062AE8E  pop edi */
		_emit 0x5F
		/* 0x0062AE8F  xor eax, eax */
		_emit 0x33
		_emit 0xC0
		/* 0x0062AE91  pop esi */
		_emit 0x5E
		/* 0x0062AE92  ret  */
		_emit 0xC3
	}
}
