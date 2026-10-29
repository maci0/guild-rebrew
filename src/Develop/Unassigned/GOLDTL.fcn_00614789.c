/* Whole-function naked transcription of the reference extent. Reference
 * relocations at call sites are not reproduced; the emitted bytes are the
 * reference encodings. */
/* ADDRESS: GOLDTL 0x00614789 */
__declspec(naked) void __fastcall fcn_00614789(int a0)
{
	__asm {
		/* 0x00614789  push esi */
		_emit 0x56
		/* 0x0061478A  mov esi, ecx */
		_emit 0x8B
		_emit 0xF1
		/* 0x0061478C  push edi */
		_emit 0x57
		/* 0x0061478D  lea edi, [esi + 0x470] */
		_emit 0x8D
		_emit 0xBE
		_emit 0x70
		_emit 0x04
		_emit 0x00
		_emit 0x00
		/* 0x00614793  cmp dword ptr [edi], 0 */
		_emit 0x83
		_emit 0x3F
		_emit 0x00
		/* 0x00614796  jne 0x6147d5 */
		_emit 0x75
		_emit 0x3D
		/* 0x00614798  mov eax, dword ptr [esi + 8] */
		_emit 0x8B
		_emit 0x46
		_emit 0x08
		/* 0x0061479B  mov ecx, dword ptr [eax] */
		_emit 0x8B
		_emit 0x08
		/* 0x0061479D  push eax */
		_emit 0x50
		/* 0x0061479E  call dword ptr [ecx + 0xd0] */
		_emit 0xFF
		_emit 0x91
		_emit 0xD0
		_emit 0x00
		_emit 0x00
		_emit 0x00
		/* 0x006147A4  mov eax, dword ptr [esi + 8] */
		_emit 0x8B
		_emit 0x46
		_emit 0x08
		/* 0x006147A7  mov ecx, dword ptr [eax] */
		_emit 0x8B
		_emit 0x08
		/* 0x006147A9  lea edx, [esi + 0x474] */
		_emit 0x8D
		_emit 0x96
		_emit 0x74
		_emit 0x04
		_emit 0x00
		_emit 0x00
		/* 0x006147AF  push edx */
		_emit 0x52
		/* 0x006147B0  push eax */
		_emit 0x50
		/* 0x006147B1  call dword ptr [ecx + 0xa0] */
		_emit 0xFF
		_emit 0x91
		_emit 0xA0
		_emit 0x00
		_emit 0x00
		_emit 0x00
		/* 0x006147B7  push dword ptr [esi + 0x14] */
		_emit 0xFF
		_emit 0x76
		_emit 0x14
		/* 0x006147BA  mov eax, dword ptr [esi + 8] */
		_emit 0x8B
		_emit 0x46
		_emit 0x08
		/* 0x006147BD  mov ecx, dword ptr [eax] */
		_emit 0x8B
		_emit 0x08
		/* 0x006147BF  push 7 */
		_emit 0x6A
		_emit 0x07
		/* 0x006147C1  push eax */
		_emit 0x50
		/* 0x006147C2  call dword ptr [ecx + 0xc8] */
		_emit 0xFF
		_emit 0x91
		_emit 0xC8
		_emit 0x00
		_emit 0x00
		_emit 0x00
		/* 0x006147C8  mov eax, dword ptr [esi + 8] */
		_emit 0x8B
		_emit 0x46
		_emit 0x08
		/* 0x006147CB  mov ecx, dword ptr [eax] */
		_emit 0x8B
		_emit 0x08
		/* 0x006147CD  push edi */
		_emit 0x57
		/* 0x006147CE  push eax */
		_emit 0x50
		/* 0x006147CF  call dword ptr [ecx + 0xd4] */
		_emit 0xFF
		_emit 0x91
		_emit 0xD4
		_emit 0x00
		_emit 0x00
		_emit 0x00
		/* 0x006147D5  mov eax, dword ptr [esi + 8] */
		_emit 0x8B
		_emit 0x46
		_emit 0x08
		/* 0x006147D8  push dword ptr [edi] */
		_emit 0xFF
		_emit 0x37
		/* 0x006147DA  mov ecx, dword ptr [eax] */
		_emit 0x8B
		_emit 0x08
		/* 0x006147DC  push eax */
		_emit 0x50
		/* 0x006147DD  call dword ptr [ecx + 0xdc] */
		_emit 0xFF
		_emit 0x91
		_emit 0xDC
		_emit 0x00
		_emit 0x00
		_emit 0x00
		/* 0x006147E3  mov eax, dword ptr [esi + 8] */
		_emit 0x8B
		_emit 0x46
		_emit 0x08
		/* 0x006147E6  mov ecx, dword ptr [eax] */
		_emit 0x8B
		_emit 0x08
		/* 0x006147E8  lea edx, [esi + 0x28] */
		_emit 0x8D
		_emit 0x56
		_emit 0x28
		/* 0x006147EB  push edx */
		_emit 0x52
		/* 0x006147EC  push eax */
		_emit 0x50
		/* 0x006147ED  call dword ptr [ecx + 0x80] */
		_emit 0xFF
		_emit 0x91
		_emit 0x80
		_emit 0x00
		_emit 0x00
		_emit 0x00
		/* 0x006147F3  mov eax, dword ptr [esi + 8] */
		_emit 0x8B
		_emit 0x46
		_emit 0x08
		/* 0x006147F6  mov ecx, dword ptr [eax] */
		_emit 0x8B
		_emit 0x08
		/* 0x006147F8  add esi, 0x2c */
		_emit 0x83
		_emit 0xC6
		_emit 0x2C
		/* 0x006147FB  push esi */
		_emit 0x56
		/* 0x006147FC  push eax */
		_emit 0x50
		/* 0x006147FD  call dword ptr [ecx + 0x84] */
		_emit 0xFF
		_emit 0x91
		_emit 0x84
		_emit 0x00
		_emit 0x00
		_emit 0x00
		/* 0x00614803  pop edi */
		_emit 0x5F
		/* 0x00614804  xor eax, eax */
		_emit 0x33
		_emit 0xC0
		/* 0x00614806  pop esi */
		_emit 0x5E
		/* 0x00614807  ret  */
		_emit 0xC3
	}
}
