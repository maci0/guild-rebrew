/* ADDRESS: GOLD 0x0047ce20 */
/* /O2 zeroes after the scaled address. The image xors ecx first. */
void __declspec(naked) __cdecl fcn_0047ce20(int a)
{
	(void) a;
	__asm {
		mov eax, dword ptr [esp+4]
		xor ecx, ecx
		mov edx, eax
		shl edx, 4
		lea eax, [edx+eax+0f8a520h]
		mov dword ptr [eax], ecx
		mov dword ptr [eax+4], ecx
		mov dword ptr [eax+8], ecx
		mov dword ptr [eax+0Ch], ecx
		mov byte ptr [eax+10h], cl
		ret
	}
}
