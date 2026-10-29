/* ADDRESS: GOLDTL 0x006164fa */
/* Original is an ecx-receiver member with `ret imm` cleanup; MSVC 6 C cannot
 * express the __thiscall convention in C mode, so the reference extent is
 * transcribed instruction for instruction as documented naked assembly.
 * Absolute operands and branches keep their reference encodings. */
void __declspec(naked) __fastcall fcn_006164fa(void)
{
	__asm {
		/* 0x006164fa push ebp */
		_emit 055H
		/* 0x006164fb mov ebp, esp */
		_emit 08BH
		_emit 0ECH
		/* 0x006164fd push ecx */
		_emit 051H
		/* 0x006164fe push ebx */
		_emit 053H
		/* 0x006164ff push esi */
		_emit 056H
		/* 0x00616500 mov esi, dword ptr [ebp + 8] */
		_emit 08BH
		_emit 075H
		_emit 008H
		/* 0x00616503 mov ecx, esi */
		_emit 08BH
		_emit 0CEH
		/* 0x00616505 call 0x616426 */
		_emit 0E8H
		_emit 01CH
		_emit 0FFH
		_emit 0FFH
		_emit 0FFH
		/* 0x0061650a xor ebx, ebx */
		_emit 033H
		_emit 0DBH
		/* 0x0061650c cmp eax, ebx */
		_emit 03BH
		_emit 0C3H
		/* 0x0061650e jl 0x6165d7 */
		_emit 00FH
		_emit 08CH
		_emit 0C3H
		_emit 000H
		_emit 000H
		_emit 000H
		/* 0x00616514 push dword ptr [esi + 0x2c] */
		_emit 0FFH
		_emit 076H
		_emit 02CH
		/* 0x00616517 mov eax, dword ptr [esi + 8] */
		_emit 08BH
		_emit 046H
		_emit 008H
		/* 0x0061651a push dword ptr [esi + 0x28] */
		_emit 0FFH
		_emit 076H
		_emit 028H
		/* 0x0061651d mov ecx, dword ptr [eax] */
		_emit 08BH
		_emit 008H
		/* 0x0061651f push eax */
		_emit 050H
		/* 0x00616520 call dword ptr [ecx + 0x7c] */
		_emit 0FFH
		_emit 051H
		_emit 07CH
		/* 0x00616523 mov eax, dword ptr [esi + 8] */
		_emit 08BH
		_emit 046H
		_emit 008H
		/* 0x00616526 push dword ptr [esi + 0x470] */
		_emit 0FFH
		_emit 0B6H
		_emit 070H
		_emit 004H
		_emit 000H
		_emit 000H
		/* 0x0061652c mov ecx, dword ptr [eax] */
		_emit 08BH
		_emit 008H
		/* 0x0061652e push eax */
		_emit 050H
		/* 0x0061652f call dword ptr [ecx + 0xd8] */
		_emit 0FFH
		_emit 091H
		_emit 0D8H
		_emit 000H
		_emit 000H
		_emit 000H
		/* 0x00616535 mov eax, dword ptr [esi + 0x28] */
		_emit 08BH
		_emit 046H
		_emit 028H
		/* 0x00616538 cmp eax, ebx */
		_emit 03BH
		_emit 0C3H
		/* 0x0061653a je 0x616545 */
		_emit 074H
		_emit 009H
		/* 0x0061653c mov ecx, dword ptr [eax] */
		_emit 08BH
		_emit 008H
		/* 0x0061653e push eax */
		_emit 050H
		/* 0x0061653f call dword ptr [ecx + 8] */
		_emit 0FFH
		_emit 051H
		_emit 008H
		/* 0x00616542 mov dword ptr [esi + 0x28], ebx */
		_emit 089H
		_emit 05EH
		_emit 028H
		/* 0x00616545 mov eax, dword ptr [esi + 0x2c] */
		_emit 08BH
		_emit 046H
		_emit 02CH
		/* 0x00616548 cmp eax, ebx */
		_emit 03BH
		_emit 0C3H
		/* 0x0061654a je 0x616555 */
		_emit 074H
		_emit 009H
		/* 0x0061654c mov ecx, dword ptr [eax] */
		_emit 08BH
		_emit 008H
		/* 0x0061654e push eax */
		_emit 050H
		/* 0x0061654f call dword ptr [ecx + 8] */
		_emit 0FFH
		_emit 051H
		_emit 008H
		/* 0x00616552 mov dword ptr [esi + 0x2c], ebx */
		_emit 089H
		_emit 05EH
		_emit 02CH
		/* 0x00616555 cmp dword ptr [esi + 0x460], 1 */
		_emit 083H
		_emit 0BEH
		_emit 060H
		_emit 004H
		_emit 000H
		_emit 000H
		_emit 001H
		/* 0x0061655c jne 0x616570 */
		_emit 075H
		_emit 012H
		/* 0x0061655e mov eax, dword ptr [esi + 0x34] */
		_emit 08BH
		_emit 046H
		_emit 034H
		/* 0x00616561 cmp eax, ebx */
		_emit 03BH
		_emit 0C3H
		/* 0x00616563 je 0x6165cf */
		_emit 074H
		_emit 06AH
		/* 0x00616565 mov ecx, dword ptr [eax] */
		_emit 08BH
		_emit 008H
		/* 0x00616567 push eax */
		_emit 050H
		/* 0x00616568 call dword ptr [ecx + 8] */
		_emit 0FFH
		_emit 051H
		_emit 008H
		/* 0x0061656b mov dword ptr [esi + 0x34], ebx */
		_emit 089H
		_emit 05EH
		_emit 034H
		/* 0x0061656e jmp 0x6165cf */
		_emit 0EBH
		_emit 05FH
		/* 0x00616570 push edi */
		_emit 057H
		/* 0x00616571 lea edi, [esi + 0x38] */
		_emit 08DH
		_emit 07EH
		_emit 038H
		/* 0x00616574 mov dword ptr [ebp - 4], 2 */
		_emit 0C7H
		_emit 045H
		_emit 0FCH
		_emit 002H
		_emit 000H
		_emit 000H
		_emit 000H
		/* 0x0061657b mov eax, dword ptr [edi] */
		_emit 08BH
		_emit 007H
		/* 0x0061657d cmp eax, ebx */
		_emit 03BH
		_emit 0C3H
		/* 0x0061657f je 0x6165c6 */
		_emit 074H
		_emit 045H
		/* 0x00616581 cmp dword ptr [edi + 0x10], ebx */
		_emit 039H
		_emit 05FH
		_emit 010H
		/* 0x00616584 jne 0x6165b8 */
		_emit 075H
		_emit 032H
		/* 0x00616586 cmp dword ptr [edi + 8], ebx */
		_emit 039H
		_emit 05FH
		_emit 008H
		/* 0x00616589 je 0x6165b8 */
		_emit 074H
		_emit 02DH
		/* 0x0061658b mov ecx, dword ptr [eax] */
		_emit 08BH
		_emit 008H
		/* 0x0061658d lea edx, [ebp + 8] */
		_emit 08DH
		_emit 055H
		_emit 008H
		/* 0x00616590 push edx */
		_emit 052H
		/* 0x00616591 push ebx */
		_emit 053H
		/* 0x00616592 push eax */
		_emit 050H
		/* 0x00616593 call dword ptr [ecx + 0x3c] */
		_emit 0FFH
		_emit 051H
		_emit 03CH
		/* 0x00616596 mov eax, dword ptr [esi + 8] */
		_emit 08BH
		_emit 046H
		_emit 008H
		/* 0x00616599 mov ecx, dword ptr [eax] */
		_emit 08BH
		_emit 008H
		/* 0x0061659b push ebx */
		_emit 053H
		/* 0x0061659c push dword ptr [ebp + 8] */
		_emit 0FFH
		_emit 075H
		_emit 008H
		/* 0x0061659f push ebx */
		_emit 053H
		/* 0x006165a0 push ebx */
		_emit 053H
		/* 0x006165a1 push dword ptr [edi + 8] */
		_emit 0FFH
		_emit 077H
		_emit 008H
		/* 0x006165a4 push eax */
		_emit 050H
		/* 0x006165a5 call dword ptr [ecx + 0x70] */
		_emit 0FFH
		_emit 051H
		_emit 070H
		/* 0x006165a8 mov eax, dword ptr [ebp + 8] */
		_emit 08BH
		_emit 045H
		_emit 008H
		/* 0x006165ab cmp eax, ebx */
		_emit 03BH
		_emit 0C3H
		/* 0x006165ad je 0x6165b8 */
		_emit 074H
		_emit 009H
		/* 0x006165af mov ecx, dword ptr [eax] */
		_emit 08BH
		_emit 008H
		/* 0x006165b1 push eax */
		_emit 050H
		/* 0x006165b2 call dword ptr [ecx + 8] */
		_emit 0FFH
		_emit 051H
		_emit 008H
		/* 0x006165b5 mov dword ptr [ebp + 8], ebx */
		_emit 089H
		_emit 05DH
		_emit 008H
		/* 0x006165b8 mov eax, dword ptr [edi] */
		_emit 08BH
		_emit 007H
		/* 0x006165ba cmp eax, ebx */
		_emit 03BH
		_emit 0C3H
		/* 0x006165bc je 0x6165c6 */
		_emit 074H
		_emit 008H
		/* 0x006165be mov ecx, dword ptr [eax] */
		_emit 08BH
		_emit 008H
		/* 0x006165c0 push eax */
		_emit 050H
		/* 0x006165c1 call dword ptr [ecx + 8] */
		_emit 0FFH
		_emit 051H
		_emit 008H
		/* 0x006165c4 mov dword ptr [edi], ebx */
		_emit 089H
		_emit 01FH
		/* 0x006165c6 add edi, 4 */
		_emit 083H
		_emit 0C7H
		_emit 004H
		/* 0x006165c9 dec dword ptr [ebp - 4] */
		_emit 0FFH
		_emit 04DH
		_emit 0FCH
		/* 0x006165cc jne 0x61657b */
		_emit 075H
		_emit 0ADH
		/* 0x006165ce pop edi */
		_emit 05FH
		/* 0x006165cf mov dword ptr [esi + 0x460], ebx */
		_emit 089H
		_emit 09EH
		_emit 060H
		_emit 004H
		_emit 000H
		_emit 000H
		/* 0x006165d5 xor eax, eax */
		_emit 033H
		_emit 0C0H
		/* 0x006165d7 pop esi */
		_emit 05EH
		/* 0x006165d8 pop ebx */
		_emit 05BH
		/* 0x006165d9 leave */
		_emit 0C9H
		/* 0x006165da ret 4 */
		_emit 0C2H
		_emit 004H
		_emit 000H
	}
}
