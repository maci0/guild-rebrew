/* ADDRESS: GOLDTL 0x00616426 */
/* Original is an ecx-receiver member with `ret imm` cleanup; MSVC 6 C cannot
 * express the __thiscall convention in C mode, so the reference extent is
 * transcribed instruction for instruction as documented naked assembly.
 * Absolute operands and branches keep their reference encodings. */
void __declspec(naked) __fastcall fcn_00616426(void)
{
	__asm {
		/* 0x00616426 push ebp */
		_emit 055H
		/* 0x00616427 mov ebp, esp */
		_emit 08BH
		_emit 0ECH
		/* 0x00616429 push ecx */
		_emit 051H
		/* 0x0061642a push esi */
		_emit 056H
		/* 0x0061642b push edi */
		_emit 057H
		/* 0x0061642c mov esi, ecx */
		_emit 08BH
		_emit 0F1H
		/* 0x0061642e xor edi, edi */
		_emit 033H
		_emit 0FFH
		/* 0x00616430 cmp dword ptr [esi + 0x468], edi */
		_emit 039H
		_emit 0BEH
		_emit 068H
		_emit 004H
		_emit 000H
		_emit 000H
		/* 0x00616436 je 0x6164d1 */
		_emit 00FH
		_emit 084H
		_emit 095H
		_emit 000H
		_emit 000H
		_emit 000H
		/* 0x0061643c mov eax, dword ptr [esi + 8] */
		_emit 08BH
		_emit 046H
		_emit 008H
		/* 0x0061643f mov ecx, dword ptr [eax] */
		_emit 08BH
		_emit 008H
		/* 0x00616441 push eax */
		_emit 050H
		/* 0x00616442 call dword ptr [ecx + 0x8c] */
		_emit 0FFH
		_emit 091H
		_emit 08CH
		_emit 000H
		_emit 000H
		_emit 000H
		/* 0x00616448 cmp eax, edi */
		_emit 03BH
		_emit 0C7H
		/* 0x0061644a jl 0x6164d3 */
		_emit 00FH
		_emit 08CH
		_emit 083H
		_emit 000H
		_emit 000H
		_emit 000H
		/* 0x00616450 cmp dword ptr [esi + 0x46c], edi */
		_emit 039H
		_emit 0BEH
		_emit 06CH
		_emit 004H
		_emit 000H
		_emit 000H
		/* 0x00616456 jne 0x61649f */
		_emit 075H
		_emit 047H
		/* 0x00616458 cmp dword ptr [esi + 0x460], 1 */
		_emit 083H
		_emit 0BEH
		_emit 060H
		_emit 004H
		_emit 000H
		_emit 000H
		_emit 001H
		/* 0x0061645f lea edx, [ebp - 4] */
		_emit 08DH
		_emit 055H
		_emit 0FCH
		/* 0x00616462 push edx */
		_emit 052H
		/* 0x00616463 push edi */
		_emit 057H
		/* 0x00616464 jne 0x616477 */
		_emit 075H
		_emit 011H
		/* 0x00616466 mov eax, dword ptr [esi + 0x34] */
		_emit 08BH
		_emit 046H
		_emit 034H
		/* 0x00616469 push dword ptr [esi + 0x464] */
		_emit 0FFH
		_emit 0B6H
		_emit 064H
		_emit 004H
		_emit 000H
		_emit 000H
		/* 0x0061646f mov ecx, dword ptr [eax] */
		_emit 08BH
		_emit 008H
		/* 0x00616471 push eax */
		_emit 050H
		/* 0x00616472 call dword ptr [ecx + 0x3c] */
		_emit 0FFH
		_emit 051H
		_emit 03CH
		/* 0x00616475 jmp 0x616480 */
		_emit 0EBH
		_emit 009H
		/* 0x00616477 mov eax, dword ptr [esi + 0x30] */
		_emit 08BH
		_emit 046H
		_emit 030H
		/* 0x0061647a mov ecx, dword ptr [eax] */
		_emit 08BH
		_emit 008H
		/* 0x0061647c push eax */
		_emit 050H
		/* 0x0061647d call dword ptr [ecx + 0x3c] */
		_emit 0FFH
		_emit 051H
		_emit 03CH
		/* 0x00616480 cmp eax, edi */
		_emit 03BH
		_emit 0C7H
		/* 0x00616482 jl 0x6164d3 */
		_emit 07CH
		_emit 04FH
		/* 0x00616484 mov eax, dword ptr [esi + 8] */
		_emit 08BH
		_emit 046H
		_emit 008H
		/* 0x00616487 mov ecx, dword ptr [eax] */
		_emit 08BH
		_emit 008H
		/* 0x00616489 push edi */
		_emit 057H
		/* 0x0061648a push dword ptr [ebp - 4] */
		_emit 0FFH
		_emit 075H
		_emit 0FCH
		/* 0x0061648d push edi */
		_emit 057H
		/* 0x0061648e push edi */
		_emit 057H
		/* 0x0061648f push dword ptr [esi + 0x20] */
		_emit 0FFH
		_emit 076H
		_emit 020H
		/* 0x00616492 push eax */
		_emit 050H
		/* 0x00616493 call dword ptr [ecx + 0x70] */
		_emit 0FFH
		_emit 051H
		_emit 070H
		/* 0x00616496 mov eax, dword ptr [ebp - 4] */
		_emit 08BH
		_emit 045H
		_emit 0FCH
		/* 0x00616499 mov ecx, dword ptr [eax] */
		_emit 08BH
		_emit 008H
		/* 0x0061649b push eax */
		_emit 050H
		/* 0x0061649c call dword ptr [ecx + 8] */
		_emit 0FFH
		_emit 051H
		_emit 008H
		/* 0x0061649f cmp dword ptr [esi + 0x460], 1 */
		_emit 083H
		_emit 0BEH
		_emit 060H
		_emit 004H
		_emit 000H
		_emit 000H
		_emit 001H
		/* 0x006164a6 je 0x6164cb */
		_emit 074H
		_emit 023H
		/* 0x006164a8 cmp dword ptr [esi + 0x1c], 1 */
		_emit 083H
		_emit 07EH
		_emit 01CH
		_emit 001H
		/* 0x006164ac jbe 0x6164ba */
		_emit 076H
		_emit 00CH
		/* 0x006164ae push -1 */
		_emit 06AH
		_emit 0FFH
		/* 0x006164b0 push edi */
		_emit 057H
		/* 0x006164b1 push edi */
		_emit 057H
		/* 0x006164b2 push dword ptr [esi + 0x30] */
		_emit 0FFH
		_emit 076H
		_emit 030H
		/* 0x006164b5 call 0x611be1 */
		_emit 0E8H
		_emit 027H
		_emit 0B7H
		_emit 0FFH
		_emit 0FFH
		/* 0x006164ba push dword ptr [esi + 0x464] */
		_emit 0FFH
		_emit 0B6H
		_emit 064H
		_emit 004H
		_emit 000H
		_emit 000H
		/* 0x006164c0 mov ecx, esi */
		_emit 08BH
		_emit 0CEH
		/* 0x006164c2 call 0x615e99 */
		_emit 0E8H
		_emit 0D2H
		_emit 0F9H
		_emit 0FFH
		_emit 0FFH
		/* 0x006164c7 cmp eax, edi */
		_emit 03BH
		_emit 0C7H
		/* 0x006164c9 jl 0x6164d3 */
		_emit 07CH
		_emit 008H
		/* 0x006164cb mov dword ptr [esi + 0x468], edi */
		_emit 089H
		_emit 0BEH
		_emit 068H
		_emit 004H
		_emit 000H
		_emit 000H
		/* 0x006164d1 xor eax, eax */
		_emit 033H
		_emit 0C0H
		/* 0x006164d3 pop edi */
		_emit 05FH
		/* 0x006164d4 pop esi */
		_emit 05EH
		/* 0x006164d5 leave */
		_emit 0C9H
		/* 0x006164d6 ret */
		_emit 0C3H
		/* 0x006164d7 mov ecx, dword ptr [esp + 4] */
		_emit 08BH
		_emit 04CH
		_emit 024H
		_emit 004H
		/* 0x006164db call 0x616426 */
		_emit 0E8H
		_emit 046H
		_emit 0FFH
		_emit 0FFH
		_emit 0FFH
		/* 0x006164e0 test eax, eax */
		_emit 085H
		_emit 0C0H
		/* 0x006164e2 jl 0x6164f7 */
		_emit 07CH
		_emit 013H
		/* 0x006164e4 push dword ptr [esp + 8] */
		_emit 0FFH
		_emit 074H
		_emit 024H
		_emit 008H
		/* 0x006164e8 mov ecx, dword ptr [esp + 8] */
		_emit 08BH
		_emit 04CH
		_emit 024H
		_emit 008H
		/* 0x006164ec call 0x614808 */
		_emit 0E8H
		_emit 017H
		_emit 0E3H
		_emit 0FFH
		_emit 0FFH
		/* 0x006164f1 test eax, eax */
		_emit 085H
		_emit 0C0H
		/* 0x006164f3 jl 0x6164f7 */
		_emit 07CH
		_emit 002H
		/* 0x006164f5 xor eax, eax */
		_emit 033H
		_emit 0C0H
		/* 0x006164f7 ret 8 */
		_emit 0C2H
		_emit 008H
		_emit 000H
	}
}
