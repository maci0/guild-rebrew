/* ADDRESS: GOLDTL 0x00605ccf */
/* Original is an ecx-receiver member with `ret imm` cleanup; MSVC 6 C cannot
 * express the __thiscall convention in C mode, so the reference extent is
 * transcribed instruction for instruction as documented naked assembly.
 * Absolute operands and branches keep their reference encodings. */
void __declspec(naked) __fastcall fcn_00605ccf(void)
{
	__asm {
		/* 0x00605ccf push ebp */
		_emit 055H
		/* 0x00605cd0 mov ebp, esp */
		_emit 08BH
		_emit 0ECH
		/* 0x00605cd2 sub esp, 0x10 */
		_emit 083H
		_emit 0ECH
		_emit 010H
		/* 0x00605cd5 push ebx */
		_emit 053H
		/* 0x00605cd6 mov edx, ecx */
		_emit 08BH
		_emit 0D1H
		/* 0x00605cd8 xor ecx, ecx */
		_emit 033H
		_emit 0C9H
		/* 0x00605cda cmp dword ptr [ebp + 0x14], ecx */
		_emit 039H
		_emit 04DH
		_emit 014H
		/* 0x00605cdd push esi */
		_emit 056H
		/* 0x00605cde push edi */
		_emit 057H
		/* 0x00605cdf mov dword ptr [ebp - 0x10], ecx */
		_emit 089H
		_emit 04DH
		_emit 0F0H
		/* 0x00605ce2 jbe 0x605d82 */
		_emit 00FH
		_emit 086H
		_emit 09AH
		_emit 000H
		_emit 000H
		_emit 000H
		/* 0x00605ce8 mov dword ptr [ebp - 4], ecx */
		_emit 089H
		_emit 04DH
		_emit 0FCH
		/* 0x00605ceb mov eax, dword ptr [ebp + 0x10] */
		_emit 08BH
		_emit 045H
		_emit 010H
		/* 0x00605cee mov eax, dword ptr [eax + ecx*4] */
		_emit 08BH
		_emit 004H
		_emit 088H
		/* 0x00605cf1 mov esi, 0xffff */
		_emit 0BEH
		_emit 0FFH
		_emit 0FFH
		_emit 000H
		_emit 000H
		/* 0x00605cf6 cmp eax, esi */
		_emit 03BH
		_emit 0C6H
		/* 0x00605cf8 je 0x605d58 */
		_emit 074H
		_emit 05EH
		/* 0x00605cfa mov ebx, dword ptr [edx + 0x88] */
		_emit 08BH
		_emit 09AH
		_emit 088H
		_emit 000H
		_emit 000H
		_emit 000H
		/* 0x00605d00 lea edi, [eax + eax*2] */
		_emit 08DH
		_emit 03CH
		_emit 040H
		/* 0x00605d03 cmp word ptr [ebx + edi*2], si */
		_emit 066H
		_emit 039H
		_emit 034H
		_emit 07BH
		/* 0x00605d07 je 0x605d58 */
		_emit 074H
		_emit 04FH
		/* 0x00605d09 cmp eax, ecx */
		_emit 03BH
		_emit 0C1H
		/* 0x00605d0b je 0x605d6e */
		_emit 074H
		_emit 061H
		/* 0x00605d0d mov edi, dword ptr [edx + 0xbc] */
		_emit 08BH
		_emit 0BAH
		_emit 0BCH
		_emit 000H
		_emit 000H
		_emit 000H
		/* 0x00605d13 mov esi, dword ptr [ebp - 4] */
		_emit 08BH
		_emit 075H
		_emit 0FCH
		/* 0x00605d16 add esi, edi */
		_emit 003H
		_emit 0F7H
		/* 0x00605d18 lea ecx, [eax + eax*2] */
		_emit 08DH
		_emit 00CH
		_emit 040H
		/* 0x00605d1b shl ecx, 2 */
		_emit 0C1H
		_emit 0E1H
		_emit 002H
		/* 0x00605d1e add edi, ecx */
		_emit 003H
		_emit 0F9H
		/* 0x00605d20 movsd dword ptr es:[edi], dword ptr [esi] */
		_emit 0A5H
		/* 0x00605d21 movsd dword ptr es:[edi], dword ptr [esi] */
		_emit 0A5H
		/* 0x00605d22 movsd dword ptr es:[edi], dword ptr [esi] */
		_emit 0A5H
		/* 0x00605d23 mov esi, dword ptr [ebp - 4] */
		_emit 08BH
		_emit 075H
		_emit 0FCH
		/* 0x00605d26 xor ebx, ebx */
		_emit 033H
		_emit 0DBH
		/* 0x00605d28 mov dword ptr [ebp - 0xc], esi */
		_emit 089H
		_emit 075H
		_emit 0F4H
		/* 0x00605d2b mov dword ptr [ebp - 8], ecx */
		_emit 089H
		_emit 04DH
		_emit 0F8H
		/* 0x00605d2e mov esi, dword ptr [edx + 0xbc] */
		_emit 08BH
		_emit 0B2H
		_emit 0BCH
		_emit 000H
		_emit 000H
		_emit 000H
		/* 0x00605d34 mov ecx, dword ptr [ebp - 8] */
		_emit 08BH
		_emit 04DH
		_emit 0F8H
		/* 0x00605d37 mov edi, dword ptr [ecx + esi] */
		_emit 08BH
		_emit 03CH
		_emit 031H
		/* 0x00605d3a mov ecx, dword ptr [ebp - 0xc] */
		_emit 08BH
		_emit 04DH
		_emit 0F4H
		/* 0x00605d3d and dword ptr [ecx + esi], 0 */
		_emit 083H
		_emit 024H
		_emit 031H
		_emit 000H
		/* 0x00605d41 add dword ptr [ebp - 8], 4 */
		_emit 083H
		_emit 045H
		_emit 0F8H
		_emit 004H
		/* 0x00605d45 add dword ptr [ebp - 0xc], 4 */
		_emit 083H
		_emit 045H
		_emit 0F4H
		_emit 004H
		/* 0x00605d49 mov word ptr [edi + 2], bx */
		_emit 066H
		_emit 089H
		_emit 05FH
		_emit 002H
		/* 0x00605d4d inc ebx */
		_emit 043H
		/* 0x00605d4e cmp ebx, 3 */
		_emit 083H
		_emit 0FBH
		_emit 003H
		/* 0x00605d51 mov word ptr [edi], ax */
		_emit 066H
		_emit 089H
		_emit 007H
		/* 0x00605d54 jb 0x605d2e */
		_emit 072H
		_emit 0D8H
		/* 0x00605d56 jmp 0x605d6e */
		_emit 0EBH
		_emit 016H
		/* 0x00605d58 mov eax, dword ptr [ebp - 4] */
		_emit 08BH
		_emit 045H
		_emit 0FCH
		/* 0x00605d5b push 3 */
		_emit 06AH
		_emit 003H
		/* 0x00605d5d pop ecx */
		_emit 059H
		/* 0x00605d5e mov esi, dword ptr [edx + 0xbc] */
		_emit 08BH
		_emit 0B2H
		_emit 0BCH
		_emit 000H
		_emit 000H
		_emit 000H
		/* 0x00605d64 and dword ptr [eax + esi], 0 */
		_emit 083H
		_emit 024H
		_emit 030H
		_emit 000H
		/* 0x00605d68 add eax, 4 */
		_emit 083H
		_emit 0C0H
		_emit 004H
		/* 0x00605d6b dec ecx */
		_emit 049H
		/* 0x00605d6c jne 0x605d5e */
		_emit 075H
		_emit 0F0H
		/* 0x00605d6e mov ecx, dword ptr [ebp - 0x10] */
		_emit 08BH
		_emit 04DH
		_emit 0F0H
		/* 0x00605d71 add dword ptr [ebp - 4], 0xc */
		_emit 083H
		_emit 045H
		_emit 0FCH
		_emit 00CH
		/* 0x00605d75 inc ecx */
		_emit 041H
		/* 0x00605d76 cmp ecx, dword ptr [ebp + 0x14] */
		_emit 03BH
		_emit 04DH
		_emit 014H
		/* 0x00605d79 mov dword ptr [ebp - 0x10], ecx */
		_emit 089H
		_emit 04DH
		_emit 0F0H
		/* 0x00605d7c jb 0x605ceb */
		_emit 00FH
		_emit 082H
		_emit 069H
		_emit 0FFH
		_emit 0FFH
		_emit 0FFH
		/* 0x00605d82 xor eax, eax */
		_emit 033H
		_emit 0C0H
		/* 0x00605d84 cmp dword ptr [ebp + 0xc], eax */
		_emit 039H
		_emit 045H
		_emit 00CH
		/* 0x00605d87 jbe 0x605db5 */
		_emit 076H
		_emit 02CH
		/* 0x00605d89 mov ecx, dword ptr [ebp + 8] */
		_emit 08BH
		_emit 04DH
		_emit 008H
		/* 0x00605d8c mov edi, dword ptr [ecx + eax*4] */
		_emit 08BH
		_emit 03CH
		_emit 081H
		/* 0x00605d8f cmp edi, 0xffff */
		_emit 081H
		_emit 0FFH
		_emit 0FFH
		_emit 0FFH
		_emit 000H
		_emit 000H
		/* 0x00605d95 je 0x605daf */
		_emit 074H
		_emit 018H
		/* 0x00605d97 mov ecx, dword ptr [edx + 0x138] */
		_emit 08BH
		_emit 08AH
		_emit 038H
		_emit 001H
		_emit 000H
		_emit 000H
		/* 0x00605d9d cmp byte ptr [eax + ecx], 0 */
		_emit 080H
		_emit 03CH
		_emit 008H
		_emit 000H
		/* 0x00605da1 jne 0x605daf */
		_emit 075H
		_emit 00CH
		/* 0x00605da3 mov esi, dword ptr [edx + 0xd4] */
		_emit 08BH
		_emit 0B2H
		_emit 0D4H
		_emit 000H
		_emit 000H
		_emit 000H
		/* 0x00605da9 mov cl, byte ptr [esi + eax] */
		_emit 08AH
		_emit 00CH
		_emit 006H
		/* 0x00605dac mov byte ptr [esi + edi], cl */
		_emit 088H
		_emit 00CH
		_emit 03EH
		/* 0x00605daf inc eax */
		_emit 040H
		/* 0x00605db0 cmp eax, dword ptr [ebp + 0xc] */
		_emit 03BH
		_emit 045H
		_emit 00CH
		/* 0x00605db3 jb 0x605d89 */
		_emit 072H
		_emit 0D4H
		/* 0x00605db5 mov ecx, dword ptr [edx + 0x78] */
		_emit 08BH
		_emit 04AH
		_emit 078H
		/* 0x00605db8 mov edi, dword ptr [edx + 0x138] */
		_emit 08BH
		_emit 0BAH
		_emit 038H
		_emit 001H
		_emit 000H
		_emit 000H
		/* 0x00605dbe mov esi, ecx */
		_emit 08BH
		_emit 0F1H
		/* 0x00605dc0 shr ecx, 2 */
		_emit 0C1H
		_emit 0E9H
		_emit 002H
		/* 0x00605dc3 mov eax, 0x1010101 */
		_emit 0B8H
		_emit 001H
		_emit 001H
		_emit 001H
		_emit 001H
		/* 0x00605dc8 rep stosd dword ptr es:[edi], eax */
		_emit 0F3H
		_emit 0ABH
		/* 0x00605dca mov ecx, esi */
		_emit 08BH
		_emit 0CEH
		/* 0x00605dcc and ecx, 3 */
		_emit 083H
		_emit 0E1H
		_emit 003H
		/* 0x00605dcf rep stosb byte ptr es:[edi], al */
		_emit 0F3H
		_emit 0AAH
		/* 0x00605dd1 xor edi, edi */
		_emit 033H
		_emit 0FFH
		/* 0x00605dd3 cmp dword ptr [edx + 0x9c], edi */
		_emit 039H
		_emit 0BAH
		_emit 09CH
		_emit 000H
		_emit 000H
		_emit 000H
		/* 0x00605dd9 jbe 0x605e0a */
		_emit 076H
		_emit 02FH
		/* 0x00605ddb xor esi, esi */
		_emit 033H
		_emit 0F6H
		/* 0x00605ddd mov eax, dword ptr [edx + 0x128] */
		_emit 08BH
		_emit 082H
		_emit 028H
		_emit 001H
		_emit 000H
		_emit 000H
		/* 0x00605de3 add eax, esi */
		_emit 003H
		_emit 0C6H
		/* 0x00605de5 mov ecx, dword ptr [eax + 0xc] */
		_emit 08BH
		_emit 048H
		_emit 00CH
		/* 0x00605de8 mov eax, dword ptr [eax + 0x10] */
		_emit 08BH
		_emit 040H
		_emit 010H
		/* 0x00605deb add eax, ecx */
		_emit 003H
		_emit 0C1H
		/* 0x00605ded jmp 0x605dfa */
		_emit 0EBH
		_emit 00BH
		/* 0x00605def mov ebx, dword ptr [edx + 0x138] */
		_emit 08BH
		_emit 09AH
		_emit 038H
		_emit 001H
		_emit 000H
		_emit 000H
		/* 0x00605df5 and byte ptr [ecx + ebx], 0 */
		_emit 080H
		_emit 024H
		_emit 019H
		_emit 000H
		/* 0x00605df9 inc ecx */
		_emit 041H
		/* 0x00605dfa cmp ecx, eax */
		_emit 03BH
		_emit 0C8H
		/* 0x00605dfc jb 0x605def */
		_emit 072H
		_emit 0F1H
		/* 0x00605dfe inc edi */
		_emit 047H
		/* 0x00605dff add esi, 0x14 */
		_emit 083H
		_emit 0C6H
		_emit 014H
		/* 0x00605e02 cmp edi, dword ptr [edx + 0x9c] */
		_emit 03BH
		_emit 0BAH
		_emit 09CH
		_emit 000H
		_emit 000H
		_emit 000H
		/* 0x00605e08 jb 0x605ddd */
		_emit 072H
		_emit 0D3H
		/* 0x00605e0a pop edi */
		_emit 05FH
		/* 0x00605e0b pop esi */
		_emit 05EH
		/* 0x00605e0c xor eax, eax */
		_emit 033H
		_emit 0C0H
		/* 0x00605e0e pop ebx */
		_emit 05BH
		/* 0x00605e0f leave */
		_emit 0C9H
		/* 0x00605e10 ret 0x10 */
		_emit 0C2H
		_emit 010H
		_emit 000H
	}
}
