/* ADDRESS: GOLDTL 0x006194de */
/* Original is a __thiscall constructor: receiver in ecx, `and dword ptr [eax+n],0`
 * clears, then the vtable store. C cannot keep the receiver in ecx nor emit the
 * and-with-zero clears, so the reference is transcribed as naked assembly. */
void __declspec(naked) __fastcall fcn_006194de(void)
{
	__asm {
		mov eax, ecx
		and dword ptr [eax + 0CH], 0
		and dword ptr [eax + 8], 0
		mov dword ptr [eax], 6676D4H
		mov dword ptr [eax + 4], 1
		ret
	}
}
