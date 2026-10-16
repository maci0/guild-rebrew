/* ADDRESS: GOLD 0x00465c80 */
int __declspec(naked) __cdecl fcn_00465c80(int* a, int* b, int* c, int* d)
{
	(void) a;
	(void) b;
	(void) c;
	(void) d;
	__asm {
		mov eax, dword ptr [esp+4]
		_emit 0x8b
		_emit 0x0d
		_emit 0xf8
		_emit 0xd2
		_emit 0x5f
		_emit 0x00
		mov edx, dword ptr [esp+8]
		mov dword ptr [eax], ecx
		_emit 0xa1
		_emit 0xfc
		_emit 0xd2
		_emit 0x5f
		_emit 0x00
		mov ecx, dword ptr [esp+0Ch]
		mov dword ptr [edx], eax
		mov edx, dword ptr [esp+10h]
		xor eax, eax
		mov dword ptr [ecx], 5fd300h
		mov dword ptr [edx], 5fe300h
		ret
	}
}
