/* ADDRESS: GOLD 0x0041e6d0 */
void __declspec(naked) __cdecl fcn_0041e6d0(int a, int o1, int o2, int o3)
{
	(void)a;
	(void)o1;
	(void)o2;
	(void)o3;
	__asm {
		mov eax, dword ptr [esp+4]
		_emit 0x8a
		_emit 0x0d
		_emit 0x79
		_emit 0x35
		_emit 0x46
		_emit 0x01
		mov edx, eax
		shr edx, cl
		_emit 0x8a
		_emit 0x0d
		_emit 0xe4
		_emit 0x50
		_emit 0x46
		_emit 0x01
		shl dl, cl
		mov ecx, dword ptr [esp+8]
		mov byte ptr [ecx], dl
		_emit 0x8a
		_emit 0x0d
		_emit 0x78
		_emit 0x35
		_emit 0x46
		_emit 0x01
		mov edx, eax
		shr edx, cl
		_emit 0x8a
		_emit 0x0d
		_emit 0x81
		_emit 0x35
		_emit 0x46
		_emit 0x01
		shl dl, cl
		mov ecx, dword ptr [esp+0Ch]
		mov byte ptr [ecx], dl
		_emit 0x8a
		_emit 0x0d
		_emit 0xbc
		_emit 0x4f
		_emit 0x46
		_emit 0x01
		mov edx, dword ptr [esp+10h]
		shr eax, cl
		_emit 0x8a
		_emit 0x0d
		_emit 0xc4
		_emit 0x4f
		_emit 0x46
		_emit 0x01
		shl al, cl
		mov byte ptr [edx], al
		ret
	}
}
