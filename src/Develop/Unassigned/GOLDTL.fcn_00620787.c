/* Whole-function naked transcription of the reference extent. Reference
 * relocations at call sites are not reproduced; the emitted bytes are the
 * reference encodings. */
/* ADDRESS: GOLDTL 0x00620787 */
__declspec(naked) void __fastcall fcn_00620787(int a0)
{
	__asm {
		/* 0x00620787  push esi */
		_emit 0x56
		/* 0x00620788  mov esi, ecx */
		_emit 0x8B
		_emit 0xF1
		/* 0x0062078A  mov ecx, dword ptr [esi + 4] */
		_emit 0x8B
		_emit 0x4E
		_emit 0x04
		/* 0x0062078D  test ecx, ecx */
		_emit 0x85
		_emit 0xC9
		/* 0x0062078F  je 0x620797 */
		_emit 0x74
		_emit 0x06
		/* 0x00620791  mov eax, dword ptr [ecx] */
		_emit 0x8B
		_emit 0x01
		/* 0x00620793  push 1 */
		_emit 0x6A
		_emit 0x01
		/* 0x00620795  call dword ptr [eax] */
		_emit 0xFF
		_emit 0x10
		/* 0x00620797  mov ecx, dword ptr [esi] */
		_emit 0x8B
		_emit 0x0E
		/* 0x00620799  test ecx, ecx */
		_emit 0x85
		_emit 0xC9
		/* 0x0062079B  pop esi */
		_emit 0x5E
		/* 0x0062079C  je 0x6207a4 */
		_emit 0x74
		_emit 0x06
		/* 0x0062079E  mov eax, dword ptr [ecx] */
		_emit 0x8B
		_emit 0x01
		/* 0x006207A0  push 1 */
		_emit 0x6A
		_emit 0x01
		/* 0x006207A2  call dword ptr [eax] */
		_emit 0xFF
		_emit 0x10
		/* 0x006207A4  ret  */
		_emit 0xC3
		/* 0x006207A5  fld dword ptr [esp + 4] */
		_emit 0xD9
		_emit 0x44
		_emit 0x24
		_emit 0x04
		/* 0x006207A9  push ecx */
		_emit 0x51
		/* 0x006207AA  push ecx */
		_emit 0x51
		/* 0x006207AB  fstp qword ptr [esp] */
		_emit 0xDD
		_emit 0x1C
		_emit 0x24
		/* 0x006207AE  call 0x64fbd8 */
		_emit 0xE8
		_emit 0x25
		_emit 0xF4
		_emit 0x02
		_emit 0x00
		/* 0x006207B3  pop ecx */
		_emit 0x59
		/* 0x006207B4  pop ecx */
		_emit 0x59
		/* 0x006207B5  ret  */
		_emit 0xC3
		/* 0x006207B6  mov eax, ecx */
		_emit 0x8B
		_emit 0xC1
		/* 0x006207B8  xor ecx, ecx */
		_emit 0x33
		_emit 0xC9
		/* 0x006207BA  mov dword ptr [eax], ecx */
		_emit 0x89
		_emit 0x08
		/* 0x006207BC  mov dword ptr [eax + 4], ecx */
		_emit 0x89
		_emit 0x48
		_emit 0x04
		/* 0x006207BF  mov dword ptr [eax + 8], ecx */
		_emit 0x89
		_emit 0x48
		_emit 0x08
		/* 0x006207C2  ret  */
		_emit 0xC3
		/* 0x006207C3  push dword ptr [ecx] */
		_emit 0xFF
		_emit 0x31
		/* 0x006207C5  call 0x6508a3 */
		_emit 0xE8
		_emit 0xD9
		_emit 0x00
		_emit 0x03
		_emit 0x00
		/* 0x006207CA  pop ecx */
		_emit 0x59
		/* 0x006207CB  ret  */
		_emit 0xC3
	}
}
