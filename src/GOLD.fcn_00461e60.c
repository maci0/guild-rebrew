/* ADDRESS: GOLD 0x00461e60 */
void __declspec(naked) __cdecl fcn_00461e60(int a, int v)
{
	(void) a;
	(void) v;
	__asm {
		mov eax, dword ptr [esp+4]
		mov ecx, dword ptr [esp+8]
		push esi
		push edi
		mov esi, dword ptr [eax+8]
		mov edi, dword ptr [eax+14h]
		mov edx, ecx
		shr edx, 8
		mov byte ptr [esi+edi], dl
		mov edx, dword ptr [eax+14h]
		mov esi, dword ptr [eax+8]
		inc edx
		mov dword ptr [eax+14h], edx
		pop edi
		mov byte ptr [edx+esi], cl
		mov ecx, dword ptr [eax+14h]
		inc ecx
		pop esi
		mov dword ptr [eax+14h], ecx
		ret
	}
}
