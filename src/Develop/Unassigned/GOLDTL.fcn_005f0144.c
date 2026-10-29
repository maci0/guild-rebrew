/* ADDRESS: GOLDTL 0x005f0144 */
/* Original is an ecx-receiver member with `ret imm` cleanup; MSVC 6 C cannot
 * express the __thiscall convention in C mode, so the reference extent is
 * transcribed instruction for instruction as documented naked assembly.
 * Absolute operands and branches keep their reference encodings. */
void __declspec(naked) __fastcall fcn_005f0144(void)
{
	__asm {
		/* 0x005f0144 mov eax, ecx */
		_emit 08BH
		_emit 0C1H
		/* 0x005f0146 push ebx */
		_emit 053H
		/* 0x005f0147 mov ebx, dword ptr [esp + 8] */
		_emit 08BH
		_emit 05CH
		_emit 024H
		_emit 008H
		/* 0x005f014b push esi */
		_emit 056H
		/* 0x005f014c mov edx, ebx */
		_emit 08BH
		_emit 0D3H
		/* 0x005f014e push edi */
		_emit 057H
		/* 0x005f014f xor edi, edi */
		_emit 033H
		_emit 0FFH
		/* 0x005f0151 and edx, 0xe */
		_emit 083H
		_emit 0E2H
		_emit 00EH
		/* 0x005f0154 xor ecx, ecx */
		_emit 033H
		_emit 0C9H
		/* 0x005f0156 cmp edx, 2 */
		_emit 083H
		_emit 0FAH
		_emit 002H
		/* 0x005f0159 lea esi, [eax + 0x18] */
		_emit 08DH
		_emit 070H
		_emit 018H
		/* 0x005f015c mov dword ptr [eax], ebx */
		_emit 089H
		_emit 018H
		/* 0x005f015e mov dword ptr [eax + 8], edi */
		_emit 089H
		_emit 078H
		_emit 008H
		/* 0x005f0161 mov dword ptr [eax + 0xc], edi */
		_emit 089H
		_emit 078H
		_emit 00CH
		/* 0x005f0164 mov dword ptr [eax + 0x10], edi */
		_emit 089H
		_emit 078H
		_emit 010H
		/* 0x005f0167 mov dword ptr [eax + 0x14], edi */
		_emit 089H
		_emit 078H
		_emit 014H
		/* 0x005f016a mov dword ptr [eax + 0x38], edi */
		_emit 089H
		_emit 078H
		_emit 038H
		/* 0x005f016d mov dword ptr [eax + 0x3c], edi */
		_emit 089H
		_emit 078H
		_emit 03CH
		/* 0x005f0170 mov dword ptr [esi], edi */
		_emit 089H
		_emit 03EH
		/* 0x005f0172 jne 0x5f0179 */
		_emit 075H
		_emit 005H
		/* 0x005f0174 push 0xc */
		_emit 06AH
		_emit 00CH
		/* 0x005f0176 pop ecx */
		_emit 059H
		/* 0x005f0177 jmp 0x5f0196 */
		_emit 0EBH
		_emit 01DH
		/* 0x005f0179 cmp edx, 4 */
		_emit 083H
		_emit 0FAH
		_emit 004H
		/* 0x005f017c jne 0x5f0182 */
		_emit 075H
		_emit 004H
		/* 0x005f017e push 0x10 */
		_emit 06AH
		_emit 010H
		/* 0x005f0180 jmp 0x5f0176 */
		_emit 0EBH
		_emit 0F4H
		/* 0x005f0182 cmp edx, 6 */
		_emit 083H
		_emit 0FAH
		_emit 006H
		/* 0x005f0185 jb 0x5f0196 */
		_emit 072H
		_emit 00FH
		/* 0x005f0187 shr edx, 1 */
		_emit 0D1H
		_emit 0EAH
		/* 0x005f0189 lea ecx, [edx - 2] */
		_emit 08DH
		_emit 04AH
		_emit 0FEH
		/* 0x005f018c mov dword ptr [eax + 0x38], ecx */
		_emit 089H
		_emit 048H
		_emit 038H
		/* 0x005f018f lea ecx, [ecx*4 + 0xc] */
		_emit 08DH
		_emit 00CH
		_emit 08DH
		_emit 00CH
		_emit 000H
		_emit 000H
		_emit 000H
		/* 0x005f0196 test bl, 0x10 */
		_emit 0F6H
		_emit 0C3H
		_emit 010H
		/* 0x005f0199 je 0x5f01a1 */
		_emit 074H
		_emit 006H
		/* 0x005f019b mov dword ptr [eax + 8], ecx */
		_emit 089H
		_emit 048H
		_emit 008H
		/* 0x005f019e add ecx, 0xc */
		_emit 083H
		_emit 0C1H
		_emit 00CH
		/* 0x005f01a1 test bl, 0x20 */
		_emit 0F6H
		_emit 0C3H
		_emit 020H
		/* 0x005f01a4 je 0x5f01ac */
		_emit 074H
		_emit 006H
		/* 0x005f01a6 mov dword ptr [eax + 0xc], ecx */
		_emit 089H
		_emit 048H
		_emit 00CH
		/* 0x005f01a9 add ecx, 4 */
		_emit 083H
		_emit 0C1H
		_emit 004H
		/* 0x005f01ac test bl, 0x40 */
		_emit 0F6H
		_emit 0C3H
		_emit 040H
		/* 0x005f01af je 0x5f01b7 */
		_emit 074H
		_emit 006H
		/* 0x005f01b1 mov dword ptr [eax + 0x10], ecx */
		_emit 089H
		_emit 048H
		_emit 010H
		/* 0x005f01b4 add ecx, 4 */
		_emit 083H
		_emit 0C1H
		_emit 004H
		/* 0x005f01b7 test bl, bl */
		_emit 084H
		_emit 0DBH
		/* 0x005f01b9 jns 0x5f01c1 */
		_emit 079H
		_emit 006H
		/* 0x005f01bb mov dword ptr [eax + 0x14], ecx */
		_emit 089H
		_emit 048H
		_emit 014H
		/* 0x005f01be add ecx, 4 */
		_emit 083H
		_emit 0C1H
		_emit 004H
		/* 0x005f01c1 test bh, 0xf */
		_emit 0F6H
		_emit 0C7H
		_emit 00FH
		/* 0x005f01c4 je 0x5f0203 */
		_emit 074H
		_emit 03DH
		/* 0x005f01c6 mov edx, ebx */
		_emit 08BH
		_emit 0D3H
		/* 0x005f01c8 shr edx, 8 */
		_emit 0C1H
		_emit 0EAH
		_emit 008H
		/* 0x005f01cb and edx, 0xf */
		_emit 083H
		_emit 0E2H
		_emit 00FH
		/* 0x005f01ce cmp edx, 8 */
		_emit 083H
		_emit 0FAH
		_emit 008H
		/* 0x005f01d1 mov dword ptr [esi], ecx */
		_emit 089H
		_emit 00EH
		/* 0x005f01d3 mov dword ptr [eax + 0x3c], edx */
		_emit 089H
		_emit 050H
		_emit 03CH
		/* 0x005f01d6 jbe 0x5f01df */
		_emit 076H
		_emit 007H
		/* 0x005f01d8 mov dword ptr [eax + 0x3c], 8 */
		_emit 0C7H
		_emit 040H
		_emit 03CH
		_emit 008H
		_emit 000H
		_emit 000H
		_emit 000H
		/* 0x005f01df shr ebx, 0x10 */
		_emit 0C1H
		_emit 0EBH
		_emit 010H
		/* 0x005f01e2 xor edx, edx */
		_emit 033H
		_emit 0D2H
		/* 0x005f01e4 cmp dword ptr [eax + 0x3c], edi */
		_emit 039H
		_emit 078H
		_emit 03CH
		/* 0x005f01e7 jbe 0x5f0203 */
		_emit 076H
		_emit 01AH
		/* 0x005f01e9 mov edi, ebx */
		_emit 08BH
		_emit 0FBH
		/* 0x005f01eb and edi, 3 */
		_emit 083H
		_emit 0E7H
		_emit 003H
		/* 0x005f01ee mov dword ptr [esi], ecx */
		_emit 089H
		_emit 00EH
		/* 0x005f01f0 add ecx, dword ptr [edi*4 + 0x6664e0] */
		_emit 003H
		_emit 00CH
		_emit 0BDH
		_emit 0E0H
		_emit 064H
		_emit 066H
		_emit 000H
		/* 0x005f01f7 shr ebx, 2 */
		_emit 0C1H
		_emit 0EBH
		_emit 002H
		/* 0x005f01fa inc edx */
		_emit 042H
		/* 0x005f01fb add esi, 4 */
		_emit 083H
		_emit 0C6H
		_emit 004H
		/* 0x005f01fe cmp edx, dword ptr [eax + 0x3c] */
		_emit 03BH
		_emit 050H
		_emit 03CH
		/* 0x005f0201 jb 0x5f01e9 */
		_emit 072H
		_emit 0E6H
		/* 0x005f0203 pop edi */
		_emit 05FH
		/* 0x005f0204 pop esi */
		_emit 05EH
		/* 0x005f0205 mov dword ptr [eax + 4], ecx */
		_emit 089H
		_emit 048H
		_emit 004H
		/* 0x005f0208 pop ebx */
		_emit 05BH
		/* 0x005f0209 ret 4 */
		_emit 0C2H
		_emit 004H
		_emit 000H
	}
}
