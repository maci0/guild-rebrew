int __cdecl fcn_004c4330(int);

/* ADDRESS: GOLD 0x004c60b0 */
void __declspec(naked) __cdecl fcn_004c60b0(int src)
{
	(void)src;
	__asm {
		sub esp, 9Ch
		push esi
		mov esi, dword ptr [esp+0A4h]
		push edi
		mov ecx, 7
		lea edi, [esp+18h]
		mov byte ptr [esp+8], 60h
		rep movsd
		movsw
		lea eax, [esp+8]
		push eax
		movsb
		call fcn_004c4330
		add esp, 4
		pop edi
		pop esi
		add esp, 9Ch
		ret
	}
}
