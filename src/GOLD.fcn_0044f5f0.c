/* ADDRESS: GOLD 0x0044f5f0 */
void __declspec(naked) __cdecl fcn_0044f5f0(int unused, int *a)
{
	(void)unused; (void)a;
	__asm {
		mov eax, dword ptr [esp+8]
		push esi
		mov ecx, dword ptr [eax+14h]
		mov edx, dword ptr [eax+1Ch]
		mov esi, dword ptr [eax+2Ch]
		add edx, ecx
		mov dword ptr [eax+1Ch], edx
		mov edx, dword ptr [eax+24h]
		add esi, edx
		xor ecx, ecx
		mov dword ptr [eax+2Ch], esi
		mov dword ptr [eax+14h], ecx
		mov dword ptr [eax+24h], ecx
		pop esi
		ret
	}
}
