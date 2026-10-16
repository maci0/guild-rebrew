/* ADDRESS: GOLD 0x0051ad60 */
/* a == 0 ? -1 : ((unsigned)a - [0x631050]) / 0x194 */
int __declspec(naked) __cdecl fcn_0051ad60(int a)
{
	(void)a;
	__asm {
		mov ecx, dword ptr [esp+4]
		test ecx, ecx
		je null_arg
		_emit 0x8b
		_emit 0x15
		_emit 0x50
		_emit 0x10
		_emit 0x63
		_emit 0x00
		mov eax, 446F8657h
		sub ecx, edx
		mul ecx
		sub ecx, edx
		shr ecx, 1
		add ecx, edx
		shr ecx, 8
		mov eax, ecx
		ret
	null_arg:
		or eax, 0FFFFFFFFh
		ret
	}
}
