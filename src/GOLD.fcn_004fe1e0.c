/* ADDRESS: GOLD 0x004fe1e0 */
void __declspec(naked) __cdecl fcn_004fe1e0(char *a, char b, int c, int d)
{
	(void)a; (void)b; (void)c; (void)d;
	__asm {
		mov ecx, dword ptr [esp+10h]
		mov eax, dword ptr [esp+4]
		movzx dx, byte ptr [esp+8]
		and ecx, 0FFh
		mov word ptr [eax+4], dx
		mov dword ptr [eax+0Ah], ecx
		mov ecx, dword ptr [esp+0Ch]
		and ecx, 0FFh
		mov dword ptr [eax+6], ecx
		ret
	}
}
