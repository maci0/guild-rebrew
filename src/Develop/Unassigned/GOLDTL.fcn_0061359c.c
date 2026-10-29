/* ADDRESS: GOLDTL 0x0061359c */
/* Original is an ecx-receiver member with `ret imm` cleanup; MSVC 6 C cannot
 * express the __thiscall convention in C mode, so the reference extent is
 * transcribed instruction for instruction as documented naked assembly.
 * Absolute operands and branches keep their reference encodings. */
void __declspec(naked) __fastcall fcn_0061359c(void)
{
	__asm {
		/* 0x0061359c push esi */
		_emit 056H
		/* 0x0061359d push edi */
		_emit 057H
		/* 0x0061359e mov edi, dword ptr [esp + 0xc] */
		_emit 08BH
		_emit 07CH
		_emit 024H
		_emit 00CH
		/* 0x006135a2 test edi, edi */
		_emit 085H
		_emit 0FFH
		/* 0x006135a4 mov esi, ecx */
		_emit 08BH
		_emit 0F1H
		/* 0x006135a6 je 0x6135f0 */
		_emit 074H
		_emit 048H
		/* 0x006135a8 cmp dword ptr [esp + 0x10], 0 */
		_emit 083H
		_emit 07CH
		_emit 024H
		_emit 010H
		_emit 000H
		/* 0x006135ad je 0x6135f0 */
		_emit 074H
		_emit 041H
		/* 0x006135af lea eax, [esi + 0x48] */
		_emit 08DH
		_emit 046H
		_emit 048H
		/* 0x006135b2 push eax */
		_emit 050H
		/* 0x006135b3 push edi */
		_emit 057H
		/* 0x006135b4 call 0x62b5d0 */
		_emit 0E8H
		_emit 017H
		_emit 080H
		_emit 001H
		_emit 000H
		/* 0x006135b9 test eax, eax */
		_emit 085H
		_emit 0C0H
		/* 0x006135bb pop ecx */
		_emit 059H
		/* 0x006135bc pop ecx */
		_emit 059H
		/* 0x006135bd jl 0x6135f5 */
		_emit 07CH
		_emit 036H
		/* 0x006135bf push dword ptr [esp + 0x10] */
		_emit 0FFH
		_emit 074H
		_emit 024H
		_emit 010H
		/* 0x006135c3 call dword ptr [0x662044] */
		_emit 0FFH
		_emit 015H
		_emit 044H
		_emit 020H
		_emit 066H
		_emit 000H
		/* 0x006135c9 test eax, eax */
		_emit 085H
		_emit 0C0H
		/* 0x006135cb mov dword ptr [esi + 8], eax */
		_emit 089H
		_emit 046H
		_emit 008H
		/* 0x006135ce jne 0x6135d7 */
		_emit 075H
		_emit 007H
		/* 0x006135d0 mov eax, 0x8007000e */
		_emit 0B8H
		_emit 00EH
		_emit 000H
		_emit 007H
		_emit 080H
		/* 0x006135d5 jmp 0x6135f5 */
		_emit 0EBH
		_emit 01EH
		/* 0x006135d7 mov dword ptr [esi + 0x4c], edi */
		_emit 089H
		_emit 07EH
		_emit 04CH
		/* 0x006135da mov eax, dword ptr [edi] */
		_emit 08BH
		_emit 007H
		/* 0x006135dc push edi */
		_emit 057H
		/* 0x006135dd call dword ptr [eax + 4] */
		_emit 0FFH
		_emit 050H
		_emit 004H
		/* 0x006135e0 lea edi, [esi + 0xc] */
		_emit 08DH
		_emit 07EH
		_emit 00CH
		/* 0x006135e3 mov esi, dword ptr [esp + 0x10] */
		_emit 08BH
		_emit 074H
		_emit 024H
		_emit 010H
		/* 0x006135e7 push 0xf */
		_emit 06AH
		_emit 00FH
		/* 0x006135e9 pop ecx */
		_emit 059H
		/* 0x006135ea rep movsd dword ptr es:[edi], dword ptr [esi] */
		_emit 0F3H
		_emit 0A5H
		/* 0x006135ec xor eax, eax */
		_emit 033H
		_emit 0C0H
		/* 0x006135ee jmp 0x6135f5 */
		_emit 0EBH
		_emit 005H
		/* 0x006135f0 mov eax, 0x8876086c */
		_emit 0B8H
		_emit 06CH
		_emit 008H
		_emit 076H
		_emit 088H
		/* 0x006135f5 pop edi */
		_emit 05FH
		/* 0x006135f6 pop esi */
		_emit 05EH
		/* 0x006135f7 ret 8 */
		_emit 0C2H
		_emit 008H
		_emit 000H
		/* 0x006135fa push esi */
		_emit 056H
		/* 0x006135fb mov esi, dword ptr [esp + 8] */
		_emit 08BH
		_emit 074H
		_emit 024H
		_emit 008H
		/* 0x006135ff push edi */
		_emit 057H
		/* 0x00613600 mov edi, dword ptr [esp + 0x10] */
		_emit 08BH
		_emit 07CH
		_emit 024H
		_emit 010H
		/* 0x00613604 push 4 */
		_emit 06AH
		_emit 004H
		/* 0x00613606 pop ecx */
		_emit 059H
		/* 0x00613607 xor eax, eax */
		_emit 033H
		_emit 0C0H
		/* 0x00613609 repe cmpsd dword ptr [esi], dword ptr es:[edi] */
		_emit 0F3H
		_emit 0A7H
		/* 0x0061360b pop edi */
		_emit 05FH
		/* 0x0061360c sete al */
		_emit 00FH
		_emit 094H
		_emit 0C0H
		/* 0x0061360f pop esi */
		_emit 05EH
		/* 0x00613610 ret */
		_emit 0C3H
		/* 0x00613611 mov ecx, dword ptr [esp + 8] */
		_emit 08BH
		_emit 04CH
		_emit 024H
		_emit 008H
		/* 0x00613615 test ecx, ecx */
		_emit 085H
		_emit 0C9H
		/* 0x00613617 jne 0x613620 */
		_emit 075H
		_emit 007H
		/* 0x00613619 mov eax, 0x8876086c */
		_emit 0B8H
		_emit 06CH
		_emit 008H
		_emit 076H
		_emit 088H
		/* 0x0061361e jmp 0x613634 */
		_emit 0EBH
		_emit 014H
		/* 0x00613620 mov eax, dword ptr [esp + 4] */
		_emit 08BH
		_emit 044H
		_emit 024H
		_emit 004H
		/* 0x00613624 mov edx, dword ptr [eax + 0x4c] */
		_emit 08BH
		_emit 050H
		_emit 04CH
		/* 0x00613627 mov dword ptr [ecx], edx */
		_emit 089H
		_emit 011H
		/* 0x00613629 mov eax, dword ptr [eax + 0x4c] */
		_emit 08BH
		_emit 040H
		_emit 04CH
		/* 0x0061362c mov ecx, dword ptr [eax] */
		_emit 08BH
		_emit 008H
		/* 0x0061362e push eax */
		_emit 050H
		/* 0x0061362f call dword ptr [ecx + 4] */
		_emit 0FFH
		_emit 051H
		_emit 004H
		/* 0x00613632 xor eax, eax */
		_emit 033H
		_emit 0C0H
		/* 0x00613634 ret 8 */
		_emit 0C2H
		_emit 008H
		_emit 000H
		/* 0x00613637 push edi */
		_emit 057H
		/* 0x00613638 mov edi, dword ptr [esp + 0xc] */
		_emit 08BH
		_emit 07CH
		_emit 024H
		_emit 00CH
		/* 0x0061363c test edi, edi */
		_emit 085H
		_emit 0FFH
		/* 0x0061363e jne 0x613647 */
		_emit 075H
		_emit 007H
		/* 0x00613640 mov eax, 0x8876086c */
		_emit 0B8H
		_emit 06CH
		_emit 008H
		_emit 076H
		_emit 088H
		/* 0x00613645 jmp 0x613657 */
		_emit 0EBH
		_emit 010H
		/* 0x00613647 push esi */
		_emit 056H
		/* 0x00613648 mov esi, dword ptr [esp + 0xc] */
		_emit 08BH
		_emit 074H
		_emit 024H
		_emit 00CH
		/* 0x0061364c push 0xf */
		_emit 06AH
		_emit 00FH
		/* 0x0061364e add esi, 0xc */
		_emit 083H
		_emit 0C6H
		_emit 00CH
		/* 0x00613651 pop ecx */
		_emit 059H
		/* 0x00613652 rep movsd dword ptr es:[edi], dword ptr [esi] */
		_emit 0F3H
		_emit 0A5H
		/* 0x00613654 xor eax, eax */
		_emit 033H
		_emit 0C0H
		/* 0x00613656 pop esi */
		_emit 05EH
		/* 0x00613657 pop edi */
		_emit 05FH
		/* 0x00613658 ret 8 */
		_emit 0C2H
		_emit 008H
		_emit 000H
		/* 0x0061365b mov eax, dword ptr [esp + 4] */
		_emit 08BH
		_emit 044H
		_emit 024H
		_emit 004H
		/* 0x0061365f mov ecx, dword ptr [eax + 0x48] */
		_emit 08BH
		_emit 048H
		_emit 048H
		/* 0x00613662 call 0x62ad5b */
		_emit 0E8H
		_emit 0F4H
		_emit 076H
		_emit 001H
		_emit 000H
		/* 0x00613667 ret 4 */
		_emit 0C2H
		_emit 004H
		_emit 000H
		/* 0x0061366a mov eax, dword ptr [esp + 4] */
		_emit 08BH
		_emit 044H
		_emit 024H
		_emit 004H
		/* 0x0061366e mov ecx, dword ptr [eax + 0x48] */
		_emit 08BH
		_emit 048H
		_emit 048H
		/* 0x00613671 call 0x62ade8 */
		_emit 0E8H
		_emit 072H
		_emit 077H
		_emit 001H
		_emit 000H
		/* 0x00613676 ret 4 */
		_emit 0C2H
		_emit 004H
		_emit 000H
	}
}
