/* ADDRESS: GOLDTL 0x0062af7c */
/* Original is an ecx-receiver member with `ret imm` cleanup; MSVC 6 C cannot
 * express the __thiscall convention in C mode, so the reference extent is
 * transcribed instruction for instruction as documented naked assembly.
 * Absolute operands and branches keep their reference encodings. */
void __declspec(naked) __fastcall fcn_0062af7c(void* self, int ignored, int arg)
{
	__asm {
		/* 0x0062af7c push ebp */
		_emit 055H
		/* 0x0062af7d mov ebp, esp */
		_emit 08BH
		_emit 0ECH
		/* 0x0062af7f sub esp, 0xe4 */
		_emit 081H
		_emit 0ECH
		_emit 0E4H
		_emit 000H
		_emit 000H
		_emit 000H
		/* 0x0062af85 mov eax, dword ptr [0x775f60] */
		_emit 0A1H
		_emit 060H
		_emit 05FH
		_emit 077H
		_emit 000H
		/* 0x0062af8a push esi */
		_emit 056H
		/* 0x0062af8b mov esi, ecx */
		_emit 08BH
		_emit 0F1H
		/* 0x0062af8d mov dword ptr [esi + 0xac], eax */
		_emit 089H
		_emit 086H
		_emit 0ACH
		_emit 000H
		_emit 000H
		_emit 000H
		/* 0x0062af93 mov eax, dword ptr [ebp + 8] */
		_emit 08BH
		_emit 045H
		_emit 008H
		/* 0x0062af96 mov dword ptr [0x775f60], esi */
		_emit 089H
		_emit 035H
		_emit 060H
		_emit 05FH
		_emit 077H
		_emit 000H
		/* 0x0062af9c mov dword ptr [esi + 4], eax */
		_emit 089H
		_emit 046H
		_emit 004H
		/* 0x0062af9f mov ecx, dword ptr [eax] */
		_emit 08BH
		_emit 008H
		/* 0x0062afa1 push eax */
		_emit 050H
		/* 0x0062afa2 call dword ptr [ecx + 4] */
		_emit 0FFH
		_emit 051H
		_emit 004H
		/* 0x0062afa5 mov eax, dword ptr [esi + 4] */
		_emit 08BH
		_emit 046H
		_emit 004H
		/* 0x0062afa8 mov ecx, dword ptr [eax] */
		_emit 08BH
		_emit 008H
		/* 0x0062afaa lea edx, [ebp - 0xe4] */
		_emit 08DH
		_emit 095H
		_emit 01CH
		_emit 0FFH
		_emit 0FFH
		_emit 0FFH
		/* 0x0062afb0 push edx */
		_emit 052H
		/* 0x0062afb1 push eax */
		_emit 050H
		/* 0x0062afb2 call dword ptr [ecx + 0x1c] */
		_emit 0FFH
		_emit 051H
		_emit 01CH
		/* 0x0062afb5 mov eax, dword ptr [esi + 4] */
		_emit 08BH
		_emit 046H
		_emit 004H
		/* 0x0062afb8 mov ecx, dword ptr [eax] */
		_emit 08BH
		_emit 008H
		/* 0x0062afba lea edx, [ebp - 0x10] */
		_emit 08DH
		_emit 055H
		_emit 0F0H
		/* 0x0062afbd push edx */
		_emit 052H
		/* 0x0062afbe push eax */
		_emit 050H
		/* 0x0062afbf call dword ptr [ecx + 0x24] */
		_emit 0FFH
		_emit 051H
		_emit 024H
		/* 0x0062afc2 mov eax, dword ptr [ebp - 0xd8] */
		_emit 08BH
		_emit 085H
		_emit 028H
		_emit 0FFH
		_emit 0FFH
		_emit 0FFH
		/* 0x0062afc8 and eax, 0x20000000 */
		_emit 025H
		_emit 000H
		_emit 000H
		_emit 000H
		_emit 020H
		/* 0x0062afcd mov ecx, esi */
		_emit 08BH
		_emit 0CEH
		/* 0x0062afcf mov dword ptr [esi + 0x50], eax */
		_emit 089H
		_emit 046H
		_emit 050H
		/* 0x0062afd2 mov dword ptr [esi + 0x58], 0x40 */
		_emit 0C7H
		_emit 046H
		_emit 058H
		_emit 040H
		_emit 000H
		_emit 000H
		_emit 000H
		/* 0x0062afd9 mov dword ptr [esi + 0x5c], 0x10 */
		_emit 0C7H
		_emit 046H
		_emit 05CH
		_emit 010H
		_emit 000H
		_emit 000H
		_emit 000H
		/* 0x0062afe0 mov dword ptr [esi + 0x54], 0x15 */
		_emit 0C7H
		_emit 046H
		_emit 054H
		_emit 015H
		_emit 000H
		_emit 000H
		_emit 000H
		/* 0x0062afe7 call 0x62ae93 */
		_emit 0E8H
		_emit 0A7H
		_emit 0FEH
		_emit 0FFH
		_emit 0FFH
		/* 0x0062afec test eax, eax */
		_emit 085H
		_emit 0C0H
		/* 0x0062afee jl 0x62b0b8 */
		_emit 00FH
		_emit 08CH
		_emit 0C4H
		_emit 000H
		_emit 000H
		_emit 000H
		/* 0x0062aff4 lea eax, [esi + 0xc] */
		_emit 08DH
		_emit 046H
		_emit 00CH
		/* 0x0062aff7 push eax */
		_emit 050H
		/* 0x0062aff8 push dword ptr [esi + 4] */
		_emit 0FFH
		_emit 076H
		_emit 004H
		/* 0x0062affb call 0x5ef863 */
		_emit 0E8H
		_emit 063H
		_emit 048H
		_emit 0FCH
		_emit 0FFH
		/* 0x0062b000 test eax, eax */
		_emit 085H
		_emit 0C0H
		/* 0x0062b002 jl 0x62b0b8 */
		_emit 00FH
		_emit 08CH
		_emit 0B0H
		_emit 000H
		_emit 000H
		_emit 000H
		/* 0x0062b008 push ebx */
		_emit 053H
		/* 0x0062b009 push edi */
		_emit 057H
		/* 0x0062b00a push 0xa */
		_emit 06AH
		_emit 00AH
		/* 0x0062b00c lea ebx, [esi + 0x70] */
		_emit 08DH
		_emit 05EH
		_emit 070H
		/* 0x0062b00f pop ecx */
		_emit 059H
		/* 0x0062b010 xor eax, eax */
		_emit 033H
		_emit 0C0H
		/* 0x0062b012 mov edi, ebx */
		_emit 08BH
		_emit 0FBH
		/* 0x0062b014 rep stosd dword ptr es:[edi], eax */
		_emit 0F3H
		_emit 0ABH
		/* 0x0062b016 mov eax, 0x100 */
		_emit 0B8H
		_emit 000H
		_emit 001H
		_emit 000H
		_emit 000H
		/* 0x0062b01b xor edi, edi */
		_emit 033H
		_emit 0FFH
		/* 0x0062b01d push edi */
		_emit 057H
		/* 0x0062b01e mov dword ptr [ebx], 0x28 */
		_emit 0C7H
		_emit 003H
		_emit 028H
		_emit 000H
		_emit 000H
		_emit 000H
		/* 0x0062b024 mov dword ptr [esi + 0x74], eax */
		_emit 089H
		_emit 046H
		_emit 074H
		/* 0x0062b027 mov dword ptr [esi + 0x78], eax */
		_emit 089H
		_emit 046H
		_emit 078H
		/* 0x0062b02a mov word ptr [esi + 0x7c], 1 */
		_emit 066H
		_emit 0C7H
		_emit 046H
		_emit 07CH
		_emit 001H
		_emit 000H
		/* 0x0062b030 mov dword ptr [esi + 0x80], edi */
		_emit 089H
		_emit 0BEH
		_emit 080H
		_emit 000H
		_emit 000H
		_emit 000H
		/* 0x0062b036 mov word ptr [esi + 0x7e], 0x20 */
		_emit 066H
		_emit 0C7H
		_emit 046H
		_emit 07EH
		_emit 020H
		_emit 000H
		/* 0x0062b03c mov dword ptr [esi + 0xa4], 0x15 */
		_emit 0C7H
		_emit 086H
		_emit 0A4H
		_emit 000H
		_emit 000H
		_emit 000H
		_emit 015H
		_emit 000H
		_emit 000H
		_emit 000H
		/* 0x0062b046 call dword ptr [0x66202c] */
		_emit 0FFH
		_emit 015H
		_emit 02CH
		_emit 020H
		_emit 066H
		_emit 000H
		/* 0x0062b04c cmp eax, edi */
		_emit 03BH
		_emit 0C7H
		/* 0x0062b04e mov dword ptr [esi + 0x6c], eax */
		_emit 089H
		_emit 046H
		_emit 06CH
		/* 0x0062b051 jne 0x62b05a */
		_emit 075H
		_emit 007H
		/* 0x0062b053 mov eax, 0x8007000e */
		_emit 0B8H
		_emit 00EH
		_emit 000H
		_emit 007H
		_emit 080H
		/* 0x0062b058 jmp 0x62b0b6 */
		_emit 0EBH
		_emit 05CH
		/* 0x0062b05a neg dword ptr [esi + 0x78] */
		_emit 0F7H
		_emit 05EH
		_emit 078H
		/* 0x0062b05d push edi */
		_emit 057H
		/* 0x0062b05e push edi */
		_emit 057H
		/* 0x0062b05f lea ecx, [esi + 0xa0] */
		_emit 08DH
		_emit 08EH
		_emit 0A0H
		_emit 000H
		_emit 000H
		_emit 000H
		/* 0x0062b065 push ecx */
		_emit 051H
		/* 0x0062b066 push edi */
		_emit 057H
		/* 0x0062b067 push ebx */
		_emit 053H
		/* 0x0062b068 push eax */
		_emit 050H
		/* 0x0062b069 call dword ptr [0x662038] */
		_emit 0FFH
		_emit 015H
		_emit 038H
		_emit 020H
		_emit 066H
		_emit 000H
		/* 0x0062b06f cmp eax, edi */
		_emit 03BH
		_emit 0C7H
		/* 0x0062b071 mov dword ptr [esi + 0x98], eax */
		_emit 089H
		_emit 086H
		_emit 098H
		_emit 000H
		_emit 000H
		_emit 000H
		/* 0x0062b077 je 0x62b053 */
		_emit 074H
		_emit 0DAH
		/* 0x0062b079 neg dword ptr [esi + 0x78] */
		_emit 0F7H
		_emit 05EH
		_emit 078H
		/* 0x0062b07c push 2 */
		_emit 06AH
		_emit 002H
		/* 0x0062b07e push dword ptr [esi + 0x6c] */
		_emit 0FFH
		_emit 076H
		_emit 06CH
		/* 0x0062b081 call dword ptr [0x662030] */
		_emit 0FFH
		_emit 015H
		_emit 030H
		_emit 020H
		_emit 066H
		_emit 000H
		/* 0x0062b087 push edi */
		_emit 057H
		/* 0x0062b088 push dword ptr [esi + 0x6c] */
		_emit 0FFH
		_emit 076H
		_emit 06CH
		/* 0x0062b08b call dword ptr [0x662034] */
		_emit 0FFH
		_emit 015H
		_emit 034H
		_emit 020H
		_emit 066H
		_emit 000H
		/* 0x0062b091 push 0xffffff */
		_emit 068H
		_emit 0FFH
		_emit 0FFH
		_emit 0FFH
		_emit 000H
		/* 0x0062b096 push dword ptr [esi + 0x6c] */
		_emit 0FFH
		_emit 076H
		_emit 06CH
		/* 0x0062b099 call dword ptr [0x662050] */
		_emit 0FFH
		_emit 015H
		_emit 050H
		_emit 020H
		_emit 066H
		_emit 000H
		/* 0x0062b09f push dword ptr [esi + 0x98] */
		_emit 0FFH
		_emit 0B6H
		_emit 098H
		_emit 000H
		_emit 000H
		_emit 000H
		/* 0x0062b0a5 push dword ptr [esi + 0x6c] */
		_emit 0FFH
		_emit 076H
		_emit 06CH
		/* 0x0062b0a8 call dword ptr [0x66204c] */
		_emit 0FFH
		_emit 015H
		_emit 04CH
		_emit 020H
		_emit 066H
		_emit 000H
		/* 0x0062b0ae mov dword ptr [esi + 0x9c], eax */
		_emit 089H
		_emit 086H
		_emit 09CH
		_emit 000H
		_emit 000H
		_emit 000H
		/* 0x0062b0b4 xor eax, eax */
		_emit 033H
		_emit 0C0H
		/* 0x0062b0b6 pop edi */
		_emit 05FH
		/* 0x0062b0b7 pop ebx */
		_emit 05BH
		/* 0x0062b0b8 pop esi */
		_emit 05EH
		/* 0x0062b0b9 leave */
		_emit 0C9H
		/* 0x0062b0ba ret 4 */
		_emit 0C2H
		_emit 004H
		_emit 000H
	}
}
