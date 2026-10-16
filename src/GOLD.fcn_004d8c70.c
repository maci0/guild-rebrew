void __cdecl fcn_004731c0(int, int, int, int);

/* ADDRESS: GOLD 0x004d8c70 */
/* mov cx leaves the high half of ecx live. C clears it. */
void __declspec(naked) __cdecl fcn_004d8c70(int unused, int obj)
{
	(void)unused;
	(void)obj;
	__asm {
		push esi
		mov esi, dword ptr [esp+0Ch]
		_emit 0xa1
		_emit 0x38
		_emit 0xd9
		_emit 0x6e
		_emit 0x00
		mov edx, 44h
		mov cx, word ptr [esi+2Ch]
		push eax
		imul cx, cx, 0Ah
		sub edx, ecx
		push 4DFh
		push edx
		push 8Ch
		call fcn_004731c0
		mov eax, dword ptr [esi+2Ch]
		add esp, 10h
		inc eax
		mov dword ptr [esi+2Ch], eax
		pop esi
		ret
	}
}
